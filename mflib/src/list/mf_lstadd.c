/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:41:21 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/20 14:17:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist.h"

void	mf_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}