/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:03:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/28 13:34:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mffiles.h"
#include "mfstring.h"
#include "mflist.h"

static t_list		*mf_lstfdnew(int fd)
{
	t_list	*lst;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	lst->next = NULL;
	lst->content_size = fd;
	if (!(lst->content = mf_strnew(BUFF_SIZE)))
	{
		free(lst);
		return (NULL);
	}
	return (lst);
}

static t_list		*mf_lstseek(t_list **lst, int fd)
{
	t_list *temp;
	t_list *new;

	temp = *lst;
	while (temp != NULL)
	{
		if ((int)(temp->content_size) == fd)
			return (temp);
		temp = temp->next;
	}
	if (!(new = mf_lstfdnew(fd)))
		return (NULL);
	mf_lstadd(lst, new);
	return (*lst);
}

static int			mf_shorten(char **line, t_list *lst)
{
	if (**line)
	{
		if (mf_strchr(*line, '\n'))
		{
			mf_strcpy((char *)lst->content, mf_strchr(*line, '\n') + 1);
			*mf_strchr(*line, '\n') = '\0';
		}
		else
			mf_strclr((char *)lst->content);
		return (1);
	}
	lst->content_size = -1;
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*lsth;
	t_list			*lst;
	char			buff[BUFF_SIZE + 1];
	int				ret;
	char			*temp;

	if (BUFF_SIZE < 0 || fd < 0 || !line || read(fd, buff, 0) == -1 ||
			!(lst = mf_lstseek(&lsth, fd)) ||
			!(*line = mf_strdup((char *)lst->content)))
		return (-1);
	mf_strclr(buff);
	while (!mf_strchr(*line, '\n') && !mf_strchr(buff, '\n') &&
			(ret = read(fd, buff, BUFF_SIZE)))
	{
		if (buff[0] == 0)
			return (0);
		buff[ret] = '\0';
		temp = *line;
		if (!(*line = mf_strjoin(*line, buff)))
			return (-1);
		free(temp);
	}
	return (mf_shorten(line, lst));
}
