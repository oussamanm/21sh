/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 23:32:53 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/21 23:32:54 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rm_quot(char *str)
{
	int i;
	int index;
	int	bl_quot;

	i = 0;
	bl_quot = 0;
	index = 0;
	while(str[i])
	{
		if (!bl_quot && M_CHECK(str[i], 34, 39))
		{
			bl_quot = str[i];
			index = i;
		}
		else if (bl_quot && str[i] == bl_quot)
		{
			ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
			ft_memmove(&str[index], &str[index + 1], ft_strlen(&str[index + 1]) + 1);
			i -= 2;
			bl_quot = 0;
			index = 0;
		}
		i++;
	}
}

void	ft_corr_quot(char **argv)
{
	int i;

	i = 0;
	if (*argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		if (ft_check_charr(argv[i], (int[]){34, 39, -1}))
			ft_rm_quot(argv[i]);
		i++;
	}
}