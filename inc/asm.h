#ifndef ASM_H
# define ASM_H

# include <SDL2/SDL.h>

# define MAXIMUM_CODE_SIZE 4096
# define MAXIMUM_STACK_SIZE 256

//simplification: only 3 types exists: double, uint64_t, int64_t
//stack/memory is aligned on 8 bytes at all times
//code is not aligned

typedef enum	e_asm_type
{
	AT_SIGNED = 1 << 0,
	AT_UNSIGNED = 1 << 1,
	AT_FLOAT = 1 << 2,
	AT_MASK = 7,
	AL_IMMEDIATE = 1 << 3,
	AL_REGISTER = 1 << 4,
	AL_MEMORY = 1 << 5,
	AL_MODIFIABLE = 3 << 4,
	AL_MASK = 7 << 3
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
	ARI_RETURN,
	ARI_FLAGS,
	ARI_STACK_PTR,
	ARI_STACK_SIZE,
	ARI_STACK_HEAD,
	ARI_INST_PTR
}				t_asm_register_id;

typedef union	u_data
{
	uint64_t	u;
	int64_t		i;
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
	AOI_JMP, AOI_RJMP, AOI_JMPZ, AOI_RJMPZ,
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
	RF_UNDERFLOW = 0b10,
	RF_OVERFLOW = 0b100,
	RF_FAIL = 0b1000
}				t_result_flags;

typedef enum	s_process_state
{
	PS_FREE,
	PS_WAIT,
	PS_PAUSE,
	PS_RUNNING
}				t_process_state;

typedef struct	s_process
{
	size_t			code_size;
	t_process_state	state;
	t_data			registers[17];
	t_typed_data	op_args[5];
	t_data			voider[5]; //imediate values are stored there to have a valid address
	t_data			stack[MAXIMUM_STACK_SIZE];
	uint8_t			code[MAXIMUM_CODE_SIZE];
}				t_process;

typedef struct	s_asm_op_table_entry
{
	char		label[7];
	uint8_t		nb_args;
	uint8_t		arg_type[5];
	int			(*func)(t_process *p);
}				t_asm_op_table_entry;

t_asm_op_table_entry	g_op_table[41];

int				init_process(t_process *p, t_data param[3], uint8_t *code,
	size_t code_size);
int				run_process(t_process *p);
int				do_op(t_process *p);
int				process_load_op_args(t_process *p, uint8_t nb_args);

int				op_cmp(t_process *p);
int				op_inc(t_process *p);

#endif
