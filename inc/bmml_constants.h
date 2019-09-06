/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmml_constants.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:35:52 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:35:57 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMML_CONSTANTS_H
# define BMML_CONSTANTS_H

# define LOCALE_MEMORY_SIZE 1024

enum	e_ptr_type
{
	PT_U8,
	PT_I8,
	PT_U16,
	PT_I16,
	PT_U32,
	PT_I32,
	PT_U64,
	PT_I64,
	PT_F32,
	PT_F64,
	PT_ANY
};

enum	e_symbol_type
{
	ST_UNASSIGNED = 0,
	ST_FUNCTION,
	ST_POINTER,
	ST_EXTERN_FUNCTION
};

enum	e_ptr_location
{
	PL_IMMEDIATE,
	PL_ALIAS,
	PL_SYMBOL
};

enum	e_op_param_type
{
	OPT_INTEGER,
	OPT_FLOAT,
	OPT_TYPE
};

enum	e_op_code
{
	OC_ALIAS,
	OC_ADD,
	OC_SUB,
	OC_MUL,
	OC_DIV,
	OC_MOD,
	OC_AND,
	OC_OR,
	OC_XOR,
	OC_SU,
	OC_SD,
	OC_LESS,
	OC_MORE,
	OC_NOT,
	OC_POINT,
	OC_DELTA,
	OC_SET,
	OC_CALL,
	OC_CALL_IF,
	OC_ALLOCATE,
	OC_RELEASE
};

enum	e_error_type
{
	ET_OK = 0,
	ET_ALLOCATION_FAILED,
	ET_INVALID_INSTRUCTION,
	ET_UNDECLARED_SYMBOL,
	ET_INVALID_PARAMETER,
	ET_TOO_MANY_PARAMETERS,
	ET_TOO_FEW_PARAMETERS,
	ET_COULD_NOT_WRITE_OPERATION,
	ET_ALIAS_NAME_TAKEN,
	ET_DUPLICATE_SYMBOL,
	ET_INVALID_PARAMETER_TYPE,
	ET_INVALID_PARAMETER_LOCATION,
	ET_INVALID_SYMBOL_TYPE,
	ET_NULL_FUNCTION
};

#endif
