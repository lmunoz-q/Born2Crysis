/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmml_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:36:05 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:36:11 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMML_TYPES_H
# define BMML_TYPES_H

# include <inttypes.h>

typedef enum e_ptr_type			t_ptr_type;
typedef enum e_symbol_type		t_symbol_type;
typedef enum e_ptr_location		t_ptr_location;
typedef enum e_op_param_type	t_op_param_type;
typedef enum e_op_code			t_op_code;
typedef enum e_error_type		t_error_type;

typedef union u_data_ptr		t_data_ptr;
typedef union u_data			t_data;
typedef union u_op_param_data	t_op_param_data;

typedef struct s_entry			t_entry;
typedef struct s_op_param		t_op_param;
typedef struct s_op				t_op;
typedef struct s_symbol_data	t_symbol_data;
typedef struct s_function		t_function;
typedef struct s_error			t_error;
typedef struct s_compiler		t_compiler;
typedef struct s_processor		t_processor;
typedef struct s_op_table		t_op_table;
typedef struct s_library		t_library;

#endif
