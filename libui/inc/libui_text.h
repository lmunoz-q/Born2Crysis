/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_text.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/29 22:29:47 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_TEXT_H
# define LIBUI_TEXT_H

# include <SDL2/SDL_ttf.h>
# include <libui_typedef.h>

/*
** idea: while in insert mode, use a buffer to store input until the cursor
** goes is not moved by an input (movement result in insert of the current
** buffer in a list of lines)
** example: new file in insert mode: i type 'Hello world!' (not using the
** mouse/enter/arrow keys), then i press the left key to go at the start of
** 'world', 'Hello world!' is append to the first line of the file (NULL)
** the cursor position is now 0,5 (the space)
** if I go in replace mode and type 'W', the previous 'w' will be overwriten
** if I use the delete key, the current line will be split in two: 'Hello ' and
** 'orld!', if I type 'W' and then save, the line will be the concatenation of
** 'Hello ', 'W' and 'orld!'
** if I type 'my beautifull ', and then save, the line will be the concatenation
** of 'Hello ', 'my beautifull ' and 'world!'
** the selection is beetween the cursor and the cut (the cut can be on another
** line in selection mode, refer to 'selection_line' to get the line where the
** cut is)
*/

/*
** end_line_format:
** LUI_ELF_LINE_FEED: \n (most unix)
** LUI_ELF_CARRIAGE_RETURN_LINE_FEED: \r\n (most dos/windows)
** LUI_ELF_CARRIAGE_RETURN: \r (commodore, early mac)
** LUI_ELF_RECORD_SEPARATOR: \x1E (qnx)
** LUI_ELF_LINE_FEED_CARRIAGE_RETURN: \n\r (acorn bbc, risc os)
** LUI_ELF_MIXED: will accept any of the above, \r\n and \n\r will be seen as a
**   single new line, only usable by libui_text_string_to_editable
*/

typedef enum	e_end_line_format
{
	LUI_ELF_LINE_FEED = 0x01,
	LUI_ELF_CARRIAGE_RETURN_LINE_FEED = 0x13,
	LUI_ELF_CARRIAGE_RETURN = 0x02,
	LUI_ELF_RECORD_SEPARATOR = 0x04,
	LUI_ELF_LINE_FEED_CARRIAGE_RETURN = 0x23,
	LUI_ELF_MIXED = 0x37
}				t_end_line_format;

typedef struct	s_editable_text
{
	char				**lines;
	Uint32				*line_length;
	Uint32				nb_lines;
	Uint32				nb_columns;
	Uint32				cursor_line;
	Uint32				cursor_column;
	Uint32				buffer_len;
	char				buffer[1024];
	Uint32				cut;
	Uint32				selection_line;
	int					is_insert : 1;
	int					is_selected : 1;
}				t_editable_text;

/*
** will create a copy of the input string in editable text format
** both src and dst must be non NULL (segfault otherwise)
** the cursor will be put at position 0,0, in replace mode
*/

int				libui_text_string_to_editable(const char *src,
					t_editable_text *dst, t_end_line_format end_line_format);

/*
** fill dst with at most dst_size characters from text, return the size of dst
** suggestion: use libui_text_editable_text_length to allocate a string long
** enough to store text
*/

size_t			libui_text_editable_to_string(t_editable_text *text, char *dst,
							size_t dst_size, t_end_line_format end_line_format);

/*
** return the string length (including end lines characters) of the text
*/

size_t			libui_text_editable_text_length(t_editable_text *text,
											t_end_line_format end_line_format);

void			libui_text_debug_print_editable_text(t_editable_text *text,
													const char *new_line);

#endif
