/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_str3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 23:53:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/21 23:53:52 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_check_charr(char *src, int tab[])
{
	int i;
	int j;

	if (src == NULL || !(*src))
		return (0);
	i = 0;
	while (src[i])
	{
		j = -1;
		while(tab[++j] != -1)
		{
			if (src[i] == tab[j])
				return (tab[j]);
		}
		i++;
	}
	return (0);
}
