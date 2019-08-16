#ifndef ASM_H
# define ASM_H

# include <SDL2/SDL.h>

//simplification: only 4 types exists: double, uint64_t, int64_t, char*
//memory is aligned on 8 bytes at all times

typedef enum	e_asm_type
{
	AT_SIZE_1 =     0b00000001,
	AT_SIZE_2 =     0b00000010,
	AT_SIZE_4 =     0b00000100,
	AT_SIZE_8 =     0b00001000,
	AT_SIZE_MASK =  0b00001111,
	AT_UNSIGNED =   0b00000000,
	AT_SIGNED =     0b00010000,
	AT_SIGN_MASK =  0b00010000,
	AT_ALL_FLOAT =  0b00011100,
	AT_MASK =       0b00011111,
	AL_IMMEDIATE =  0b00100000,
	AL_REGISTER =   0b01000000,
	AL_MEMORY =     0b10000000,
	AL_MODIFIABLE = 0b11000000,
	AL_MASK =       0b11100000
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
	ARI_PARAM_3,
	ARI_RETURN,
	ARI_FLAGS,
	ARI_STACK_PTR,
	ARI_STACK_SIZE,
	ARI_STACK_HEAD,
	ARI_INST_PTR
}				t_asm_register_id;

typedef union	u_data
{
	uint8_t		u8;
	uint16_t	u16;
	uint32_t	u32;
	uint64_t	u64;
	int8_t		i8;
	int16_t		i16;
	int32_t		i32;
	int64_t		i64;
	float		f;
	double		d;
	void		*ptr;
}				t_data;

typedef struct	s_cpu
{
	t_data	ret;
	t_data	param[4];
	t_data	stack_ptr;
	t_data	stack_size;
	t_data	stack_head;
	t_data	instruction_ptr;
	t_data	flags;
	t_data	registers[8];
}				t_cpu;

typedef struct	s_typed_data
{
	t_asm_type	type;
	t_data		*data;
}				t_typed_data;

typedef enum	e_asm_op_id
{
	AOI_NOOP = 0,
	AOI_FABS, AOI_ADD, AOI_FADD, AOI_AND, AOI_ANDL,
	AOI_CALL, AOI_CAST, AOI_CASTF, AOI_FCAST, AOI_FCASTF, AOI_CMP, AOI_FCMP,
	AOI_FCOS,
	AOI_DEC, AOI_FDEC, AOI_DIV, AOI_FDIV,
	AOI_HLT,
	AOI_INC, AOI_FINC, AOI_INT,
	AOI_JMP, AOI_RJMP, AOI_JMPZ, AOI_RJMPZ,
	AOI_LOAD,
	AOI_MOV, AOI_MOVR, AOI_MUL, AOI_FMUL,
	AOI_NEG, AOI_FNEG, AOI_NOT,
	AOI_OR, AOI_ORL,
	AOI_FPI, AOI_POP, AOI_FPOW, AOI_PUSH,
	AOI_RAND, AOI_FRAND, AOI_RET,
	AOI_SHL, AOI_SHR, AOI_FSIN, AOI_SNAP, AOI_FSQRT, AOI_SUB, AOI_FSUB,
	AOI_WAIT,
	AOI_XOR
}				t_asm_op_id;

typedef struct	s_asm_op_table_entry
{
	char		label[7];
	uint8_t		nb_args;
	uint8_t		arg_type[6];
	t_asm_op_id	op;
}				t_asm_op_table_entry;

t_asm_op_table_entry	g_op_table[52] = {
	{"NOOP", 0, {}, AOI_NOOP},
	{"FABS", 2, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK}, AOI_FABS},
	{"ADD", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_ADD},
	{"FADD", 3, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK, AT_ALL_FLOAT|AL_MASK}, AOI_FADD},
	{"AND", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_AND},
	{"ANDL", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_ANDL},
	{"CALL", 6, {AT_MASK|AL_MODIFIABLE, AT_SIZE_8|AT_UNSIGNED|AL_MASK, AT_MASK|AL_MASK, AT_MASK|AL_MASK, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_CALL},
	{"CAST", 3, {}, AOI_CAST},//fonctionnement particulier a revoir
	{"CASTF", 3, {}, AOI_CASTF},//fonctionnement particulier a revoir
	{"FCAST", 3, {}, AOI_FCAST},//fonctionnement particulier a revoir
	{"FCASTF", 3, {}, AOI_FCASTF},//fonctionnement particulier a revoir
	{"CMP", 2, {AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_CMP},
	{"FCMP", 2, {AT_ALL_FLOAT|AL_MASK, AT_ALL_FLOAT|AL_MASK}, AOI_FCMP},
	{"FCOS", 2, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK}, AOI_FCOS},
	{"DEC", 1, {AT_MASK|AL_MODIFIABLE}, AOI_DEC},
	{"FDEC", 1, {AT_ALL_FLOAT|AL_MODIFIABLE}, AOI_FDEC},
	{"DIV", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_DIV},
	{"FDIV", 3, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK, AT_ALL_FLOAT|AL_MASK}, AOI_FDIV},
	{"HLT", 0, {}, AOI_HLT},
	{"INC", 1, {AT_MASK|AL_MODIFIABLE}, AOI_INC},
	{"FINC", 1, {AT_ALL_FLOAT|AL_MODIFIABLE}, AOI_FINC},
	{"INT", 1, {AT_SIZE_8|AT_UNSIGNED|AL_MASK}, AOI_INT},
	{"JMP", 1, {AT_SIZE_8|AT_UNSIGNED|AL_MASK}, AOI_JMP},
	{"RJMP", 1, {AT_SIZE_8|AT_UNSIGNED|AL_MASK}, AOI_RJMP},
	{"JMPZ", 1, {AT_SIZE_8|AT_UNSIGNED|AL_MASK}, AOI_JMPZ},
	{"RJMPZ", 1, {AT_SIZE_8|AT_UNSIGNED|AL_MASK}, AOI_RJMPZ},
	{"LOAD", 0, {}, AOI_LOAD},
	{"MOV", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_MOV},
	{"MOVR", 3, {AT_MASK|AL_MEMORY, AT_MASK|AL_MEMORY}, AOI_MOVR},
	{"MUL", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_MUL},
	{"FMUL", 3, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK, AT_ALL_FLOAT|AL_MASK}, AOI_FMUL},
	{"NEG", 1, {AT_MASK|AL_MODIFIABLE}, AOI_NEG},
	{"FNEG", 1, {AT_ALL_FLOAT|AL_MODIFIABLE}, AOI_FNEG},
	{"NOT", 1, {AT_MASK|AL_MODIFIABLE}, AOI_NOT},
	{"OR", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_OR},
	{"ORL", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_ORL},
	{"FPI", 1, {AT_ALL_FLOAT|AL_MODIFIABLE}, AOI_FPI},
	{"POP", 1, {AT_MASK|AL_MODIFIABLE}, AOI_POP},
	{"FPOW", 3, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK, AT_ALL_FLOAT|AL_MASK}, AOI_FPOW},
	{"PUSH", 1, {AT_MASK|AL_MASK}, AOI_PUSH},
	{"RAND", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_RAND},
	{"FRAND", 1, {AT_ALL_FLOAT|AL_MODIFIABLE}, AOI_FRAND},
	{"RET", 0, {}, AOI_RET},
	{"SHL", 1, {AT_MASK|AL_MODIFIABLE}, AOI_SHL},
	{"SHR", 1, {AT_MASK|AL_MODIFIABLE}, AOI_SHR},
	{"FSIN", 2, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK}, AOI_FSIN},
	{"SNAP", 0, {}, AOI_SNAP},
	{"FSQRT", 2, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK}, AOI_FSQRT},
	{"SUB", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_SUB},
	{"FSUB", 3, {AT_ALL_FLOAT|AL_MODIFIABLE, AT_ALL_FLOAT|AL_MASK, AT_ALL_FLOAT|AL_MASK}, AOI_FSUB},
	{"WAIT", 1, {AT_MASK|AL_MASK}, AOI_WAIT},
	{"XOR", 3, {AT_MASK|AL_MODIFIABLE, AT_MASK|AL_MASK, AT_MASK|AL_MASK}, AOI_XOR}
};

typedef struct	s_process
{
	t_cpu			cpu;
	t_typed_data	op_args[6];
	uint64_t		voider[6]; //imediate values are stored there to have a valid address
	t_data			stack[1024];
	uint8_t			code[4096];
}				t_process;

void	process_load_op_args(t_process *p, uint8_t nb_args);

#endif
