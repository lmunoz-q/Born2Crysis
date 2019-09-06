/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:34 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

static inline t_error_type	i_allocs(t_compiler *comp, const char *text,
										t_function *func, int d)
{
	(void)d;
	if ((comp->text = strdup(text)) == NULL)
		return (ET_ALLOCATION_FAILED);
	*comp = (t_compiler){.text = comp->text, .head = comp->text,
		.cur_func = func, .alias_names = malloc(sizeof(char*) * 2),
		{.type = ET_OK, .pos = 0}};
	if (comp->alias_names == NULL)
		return (ET_ALLOCATION_FAILED);
	comp->alias_names[1] = NULL;
	if ((comp->alias_names[0] = strdup("$")) == NULL)
		return (ET_ALLOCATION_FAILED);
	if ((comp->alias_names[1] = strdup("#")) == NULL)
		return (ET_ALLOCATION_FAILED);
	return (ET_OK);
}

t_error_type				compile_function(const char *text, t_function *func,
											int d)
{
	t_compiler	comp;
	char		s;
	char		*sp;

	if ((comp.error.type = i_allocs(&comp, text, func, d)) != ET_OK)
		return (finish_compilation(&comp, d));
	while (*comp.head != '\0' && comp.error.type == ET_OK)
	{
		while (*comp.head == ' ' || *comp.head == '\t')
			++comp.head;
		if (*comp.head == '\0' || *comp.head == '\n')
			continue ;
		sp = comp.head;
		while (*sp != '\0' && *sp != '\n')
			++sp;
		s = *sp;
		*sp = '\0';
		if (*comp.head != '#' && sp != comp.head)
			compile_line(&comp);
		comp.head = sp + 1;
		*sp = s;
	}
	return (finish_compilation(&comp, d));
}
