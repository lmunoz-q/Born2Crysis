/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_str_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:02:10 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/26 17:02:20 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		doom_str_clean(char *text, unsigned int len)
{
	unsigned int nb;

	nb = 0;
	while (nb < len)
	{
		text[nb] = '\0';
		nb++;
	}
}
