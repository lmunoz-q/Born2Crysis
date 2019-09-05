/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_text_debug_print_editable_text.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:31:41 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:31:42 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_text.h>

void	libui_text_debug_print_editable_text(t_editable_text *text,
											const char *new_line)
{
	Uint32	l;

	l = -1;
	while (++l < text->nb_lines)
		if (text->cursor_line == l)
			printf("%.*s\x1b[7m%c\x1b[0m%.*s%s", text->cursor_column,
				text->lines[l], text->lines[l][text->cursor_column],
				text->line_length[l] - text->cursor_column - 1,
				&text->lines[l][text->cursor_column + 1], new_line);
		else
			printf("%.*s%s", text->line_length[l], text->lines[l], new_line);
}
