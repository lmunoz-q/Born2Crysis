/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:06 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>
#include <mflib.h>

static inline void	i_error(t_compiler *comp, int *col, int *lines, char **s)
{
	int		it;

	it = (int)comp->error.pos;
	*col = 1;
	while (it-- && comp->text[it] != '\n')
		++col;
	*s = &comp->text[it + (comp->text[it] == '\n')];
	if (comp->text[it] == '\n')
	{
		*lines = 2;
		while (it--)
			if (comp->text[it] == '\n')
				++*lines;
	}
	else
		*lines = 1;
}

void				error(t_compiler *comp)
{
	int			lines;
	int			col;
	int			it;
	char		*s;
	const char	*errors[] = {"OK", "MEMORY_ALLOCATION_FAILED",
		"INVALID_INSTRUCTION", "UNDECLARED_SYMBOL", "INVALID_PARAMETER",
		"TOO_MANY_PARAMETERS", "TOO_FEW_PARAMETERS", "TOO_MANY_ENTRIES"};

	if (comp->error.type == ET_OK)
		return ;
	i_error(comp, &col, &lines, &s);
	it = 0;
	while (s[it] != '\n' && s[it] != '\0')
		++it;
	mf_printf("Error: %s %i:%i:%i\n", errors[comp->error.type],
		(int)comp->error.pos, lines, col);
	mf_printf("%.*s\n", it, s);
	while (--col)
		mf_printf(" ");
	mf_printf("^\n");
}
