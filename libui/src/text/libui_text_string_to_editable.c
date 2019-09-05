/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_text_string_to_editable.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:31:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 17:14:52 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_text.h>

int						is_new_line(const char *t,
								t_end_line_format end_line_format, Uint32 *i)
{
	if (t[0] == '\n' && end_line_format & LUI_ELF_LINE_FEED)
	{
		if (end_line_format == LUI_ELF_LINE_FEED)
			return (++*i != 0);
		if (t[1] == '\r' && end_line_format & LUI_ELF_LINE_FEED_CARRIAGE_RETURN)
			return ((*i = (*i + 2) | (1 << 31)) != 0);
	}
	if (t[0] == '\r' && end_line_format & LUI_ELF_CARRIAGE_RETURN)
	{
		if (end_line_format == LUI_ELF_CARRIAGE_RETURN)
			return (++*i != 0);
		if (t[1] == '\n' && end_line_format & LUI_ELF_CARRIAGE_RETURN_LINE_FEED)
			return ((*i = (*i + 2) | (1 << 31)) != 0);
		return (0);
	}
	return (t[0] == '\x1E'
		&& end_line_format & LUI_ELF_RECORD_SEPARATOR && ++*i != 0);
}

int						i_error(t_editable_text *dst)
{
	size_t	i;

	if (dst->line_length != NULL)
		free(dst->line_length);
	i = dst->nb_lines;
	if (dst->lines != NULL)
	{
		while (i--)
			free(dst->lines[i]);
		free(dst->lines);
	}
	return (-1);
}

static	void			libui_sub_text_string_to_editable_init(Uint32 *head,
							Uint32 *i, t_editable_text *dst, Uint32 *nl_stack)
{
	*head = 1;
	nl_stack[0] = 0;
	*i = (Uint32)-1;
	dst->line_length = NULL;
	dst->lines = NULL;
	dst->nb_columns = 0;
	dst->cursor_line = 0;
	dst->cursor_column = 0;
	dst->buffer_len = 0;
	dst->cut = 0;
	dst->selection_line = 0;
	dst->is_insert = 0;
	dst->is_selected = 0;
}

static inline Uint32	thing(const char *src,
	t_end_line_format end_line_format, Uint32 *head, Uint32 nl_stack[1 << 16])
{
	Uint32	i;

	i = (Uint32)-1;
	while (src[++i] != '\0')
		if (is_new_line(&src[i], end_line_format, &i))
		{
			if (*head == 1 << 16)
				return ((Uint32)-1);
			nl_stack[(*head)++] = i;
			i = (i & ~(1 << 31)) - 1;
		}
	return (i);
}

int						libui_text_string_to_editable(const char *src,
						t_editable_text *dst, t_end_line_format end_line_format)
{
	Uint32			nl_stack[1 << 16];
	Uint32			h;
	Uint32			i;

	libui_sub_text_string_to_editable_init(&h, &i, dst, nl_stack);
	if ((i = thing(src, end_line_format, &h, nl_stack)) == (Uint32)-1)
		return (-1);
	dst->nb_lines = h;
	if ((dst->lines = malloc(sizeof(char*) * dst->nb_lines)) == NULL)
		return (i_error(dst));
	if ((dst->line_length = malloc(sizeof(Uint32) * dst->nb_lines)) == NULL)
		return (i_error(dst));
	while (h--)
	{
		dst->line_length[h] = i - (nl_stack[h] & ~(1 << 31));
		if ((dst->lines[h] = malloc(dst->line_length[h] + 1)) == NULL)
			return (i_error(dst));
		SDL_memcpy(dst->lines[h], &src[nl_stack[h]], dst->line_length[h]);
		if (dst->line_length[h] > dst->nb_columns)
			dst->nb_columns = dst->line_length[h];
		dst->lines[h][dst->line_length[h]] = '\0';
		i = (nl_stack[h] & ~(1 << 16)) - 1 -
			((nl_stack[h] & (1 << 16)) != 0);
	}
	return (0);
}
