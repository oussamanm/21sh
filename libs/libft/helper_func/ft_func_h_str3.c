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

void	ft_repeat_char(int c, int n)
{
	if (!ft_isprint(c))
		return ;
	while (n > 0)
	{
		ft_putchar_fd(c, 2);
		n--;
	}
}

int		ft_check_charr(char *src, int str[], int exept)
{
	int i;
	int j;

	if (src == NULL || !(*src))
		return (0);
	i = 0;
	while (src[i])
	{
		j = -1;
		while(str[++j] != -1)
		{
			if (exept == 0 && src[i] == str[j])
				return (str[j]);
			if (exept == 1 && src[i] != str[j])
				return (j);
		}
		i++;
	}
	return (0);
}
