#ifndef ASM_H
# define ASM_H

# include <SDL2/SDL.h>

# define MAXIMUM_CODE_SIZE 4096
# define MAXIMUM_STACK_SIZE 256 //per process, mostly affect the recursion
# define MAXIMUM_LABEL_COUNT 255
# define MAXIMUM_LABEL_LENGTH 16

typedef uint8_t		t_byte;
typedef uint64_t	t_word;
typedef int64_t		t_s_word;

//simplification: only 3 types exists: double, uint64_t, int64_t
//stack/memory is aligned on 8 bytes at all times
//code is not aligned

typedef enum		e_asm_type
{
	AT_SIGNED = 1 << 0,
	AT_UNSIGNED = 1 << 1,
	AT_FLOAT = 1 << 2,
	AT_MASK = 7,
	AL_IMMEDIATE = 1 << 3,
	AL_REGISTER = 1 << 4,
	AL_MEMORY = 1 << 5,
	AL_MODIFIABLE = 3 << 4,
	AL_MASK = 7 << 3,
	AL_SYMBOL = 1 << 7 //reserved for compilation/load, this flag will be replaced by a normal direct value once successfully loaded (usually an address of arrival of a jump or address of imported function)
}				t_asm_type;

typedef enum	e_asm_register_id
{
	ARI_COMMON_0,
	ARI_COMMON_1,
	ARI_COMMON_2,
	ARI_COMMON_3,
	ARI_COMMON_4,
	ARI_COMMON_5,
	ARI_COMMON_6,
	ARI_COMMON_7,
	ARI_PARAM_0,
	ARI_PARAM_1,
	ARI_PARAM_2,
	ARI_STACK_PTR,
	ARI_STACK_SIZE,
	ARI_STACK_HEAD,
	ARI_INST_PTR,
	ARI_RETURN,
	ARI_FLAGS,
	REGISTER_MAX
}				t_asm_register_id;

typedef union	u_data
{
	t_word		u;
	t_s_word	i;
	double		f;
	void		*ptr;
}				t_data;

typedef struct	s_typed_data
{
	t_asm_type	type;
	t_data		*data;
}				t_typed_data;

typedef enum	e_asm_op_id
{
	AOI_NOOP = 0,
	AOI_ABS, AOI_ADD, AOI_AND, AOI_ANDL,
	AOI_CALL, AOI_CASTF, AOI_FCAST,AOI_CMP,
	AOI_COS,
	AOI_DEC, AOI_DIV,
	AOI_HLT,
	AOI_INC, AOI_INT,
	AOI_JMP, AOI_JMPZ,
	AOI_LOAD,
	AOI_MOV, AOI_MOVR, AOI_MUL,
	AOI_NEG, AOI_NOT,
	AOI_OR, AOI_ORL,
	AOI_PI, AOI_POP, AOI_POW, AOI_PUSH,
	AOI_RAND, AOI_FRAND, AOI_RET,
	AOI_SHL, AOI_SHR, AOI_SIN, AOI_SNAP, AOI_SQRT, AOI_SUB,
	AOI_WAIT,
	AOI_XOR
}				t_asm_op_id;

typedef enum	e_result_flags
{
	RF_ZERO = 0b1,
//	RF_UNDERFLOW = 0b10,
//	RF_OVERFLOW = 0b100,
	RF_FAIL = 0b1000,
	RF_SIGN = 0b10000
}				t_result_flags;

typedef enum	s_process_state
{
	PS_FREE,
	PS_WAIT,
	PS_PAUSE,
	PS_RUNNING
}				t_process_state;

typedef enum	s_label_type
{
	LT_LOCAL,
	LT_C
}				t_label_type;

typedef struct	s_asm_file
{
	t_byte		nb_labels;
	t_word		expected_stack_size;
	t_word		code_size;
	t_byte		label_type[MAXIMUM_LABEL_COUNT]; //local, other file, imported from C
	char		labels[MAXIMUM_LABEL_COUNT][MAXIMUM_LABEL_LENGTH];
	t_word		label_deltas[MAXIMUM_LABEL_COUNT];
	t_byte		code[];
}				t_asm_file;

typedef struct	s_asmc
{
	t_word		initial_stack_size;
	t_word		code_size;
	t_byte		code[MAXIMUM_CODE_SIZE];
	t_byte		nb_labels;
	t_byte		label_type[MAXIMUM_LABEL_COUNT];
	char		labels[MAXIMUM_LABEL_COUNT][MAXIMUM_LABEL_LENGTH];
	t_byte		*label_address[MAXIMUM_LABEL_COUNT];
}				t_asmc;

typedef struct	s_process
{
	t_process_state	state; //activity state of this process
	t_data			registers[17];
	t_typed_data	op_args[5]; //temporary variables to store pointer to arguments of currently processed operator
	t_data			voider[5]; //imediate values are stored there to have a valid address
	t_asmc			*asmc;
	t_data			stack[];
}				t_process;

typedef struct	s_asm_op_table_entry
{
	char		label[7];
	t_byte		nb_args;
	t_byte		arg_type[5];
	int			(*func)(t_process *p);
}				t_asm_op_table_entry;

typedef union	u_asm_code_cast
{
	t_byte		*byte;
	t_word		*word;
}				t_asm_code_cast;

t_asm_op_table_entry	g_op_table[41];


int				asmc_init(t_asmc *asmc);
//add_exposed_functions must be called before adding code referencing those functions
//the label will be preceded by C_ to avoid conflicts avec asm labels (camel case)
int				asmc_add_exposed_function(t_asmc *asmc, const char label[MAXIMUM_LABEL_LENGTH - 2], int (*func)(t_process*));
//code might be added after or while a process is running without harm
int				asmc_add_code(t_asmc *asmc, t_asm_file *file);

t_word			entry_point_from_label(t_asmc *asmc, const char label[MAXIMUM_LABEL_LENGTH]);

//allocate a process with an initial stack size described in asmc
t_process		*create_process(t_asmc *asmc, t_word entry_point, t_data param[3]);
//read instructions and execute them until a wait/pause/exit/error occures
int				run_process(t_process *p);
//inner function of run_process, execute a single operation
int				do_op(t_process *p);
//read the arguments of an operator from the code/registers/stack/memory
int				process_load_op_args(t_process *p, t_byte nb_args);

//set the zero flag if v == 0
void			test_zero(t_process *p, t_word v);
//set the sign flag if d is negative
void			test_sign(t_process *p, t_typed_data d);

/*
** operators:
** except for call, load, snap, movr and cast, this set of instruction is
** similar to the usual intel instructions
*/

int				op_noop(t_process *p);
int				op_add(t_process *p);
int				op_and(t_process *p);
int				op_andl(t_process *p);
int				op_call(t_process *p);
int				op_castf(t_process *p);
int				op_fcast(t_process *p);
int				op_cmp(t_process *p);
int				op_cos(t_process *p);
int				op_dec(t_process *p);
int				op_div(t_process *p);
int				op_hlt(t_process *p);
int				op_inc(t_process *p);
int				op_int(t_process *p);
int				op_jmp(t_process *p);
int				op_rjmp(t_process *p);
int				op_jmpz(t_process *p);
int				op_rjmpz(t_process *p);
int				op_load(t_process *p);
int				op_mov(t_process *p);
int				op_movr(t_process *p);
int				op_mul(t_process *p);
int				op_neg(t_process *p);
int				op_not(t_process *p);
int				op_or(t_process *p);
int				op_orl(t_process *p);
int				op_pi(t_process *p);
int				op_pop(t_process *p);
int				op_pow(t_process *p);
int				op_push(t_process *p);
int				op_rand(t_process *p);
int				op_frand(t_process *p);
int				op_ret(t_process *p);
int				op_shl(t_process *p);
int				op_shr(t_process *p);
int				op_sin(t_process *p);
int				op_snap(t_process *p);
int				op_sqrt(t_process *p);
int				op_sub(t_process *p);
int				op_wait(t_process *p);
int				op_xor(t_process *p);

#endif
