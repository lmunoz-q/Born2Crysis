/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:05:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 19:09:07 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void        kf_item_delete(void *param)
{
    t_e     *e;

    e = param;
    if (!e->editor.is_in_view)
        return ;
    
}