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

void		error(t_compiler *comp)
{
	int			lines;
	int			columns;
	int			it;
	char		*s;
	const char	*errors[] = {"OK", "MEMORY_ALLOCATION_FAILED",
		"INVALID_INSTRUCTION", "UNDECLARED_SYMBOL", "INVALID_PARAMETER",
		"TOO_MANY_PARAMETERS", "TOO_FEW_PARAMETERS", "TOO_MANY_ENTRIES"};

	if (comp->error.type == ET_OK)
	{
		printf("No errors :)\n");
		return ;
	}
	it = (int)comp->error.pos;
	columns = 1;
	while (it-- && comp->text[it] != '\n')
		++columns;
	s = &comp->text[it + (comp->text[it] == '\n')];
	if (comp->text[it] == '\n')
	{
		lines = 2;
		while (it--)
			if (comp->text[it] == '\n')
				++lines;
	}
	else
		lines = 1;
	it = 0;
	while (s[it] != '\n' && s[it] != '\0')
		++it;
	printf("Error: %s %i:%i:%i\n", errors[comp->error.type],
		   (int)comp->error.pos, lines, columns);
	printf("%.*s\n", it, s);
	while (--columns)
		printf(" ");
	printf("^\n");
}
