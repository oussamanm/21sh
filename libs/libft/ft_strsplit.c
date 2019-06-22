/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 22:45:55 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 01:56:47 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_getlen(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static	int		ft_getindx(char const *str, char c)
{
	int i;
	int i_bln;

	i = 0;
	i_bln = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			i_bln = 1;
			break ;
		}
		i++;
	}
	if (i_bln == 0)
		return (-1);
	else
		return (i);
}

static	int		ft_cntwr(const char *str, char c)
{
	int	i;
	int	i_count;
	int	i_resu;

	i = 0;
	i_count = 0;
	i_resu = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i_count *= -1;
		if (str[i] != c || i_count < 0)
		{
			if (i_count < 0)
			{
				i_count *= -1;
				i_resu++;
				i_count = 0;
			}
			else
				i_count++;
		}
		i++;
	}
	return (i_resu);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		i_firstw;
	int		i_lenw;
	char	**s_re;

	i = 0;
	j = 0;
	if (!s || !(s_re = (char **)malloc(sizeof(*s_re) * (ft_cntwr(s, c) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		i_firstw = ft_getindx(&s[i], c);
		if (i_firstw == -1)
			break ;
		i += i_firstw;
		i_lenw = ft_getlen(&s[i], c);
		if (!(s_re[j] = (char *)malloc(sizeof(char) * i_lenw + 1)))
			return (NULL);
		s_re[j] = ft_strsub(s, i, i_lenw);
		i += i_lenw;
		j++;
	}
	s_re[j] = NULL;
	return (s_re);
}
