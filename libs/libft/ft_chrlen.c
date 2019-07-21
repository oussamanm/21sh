/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:56:31 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/16 16:56:42 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_chrlen(const char *str, char c)
{
	int		i;
	int		len;

	len = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			len++;
	}
	return (len);
}
