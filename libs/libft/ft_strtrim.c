/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:22:35 by onouaman          #+#    #+#             */
/*   Updated: 2018/10/21 19:05:59 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_firstsp(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

static	size_t	ft_lastsp(size_t len, const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[len])
	{
		if (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
			i++;
		else
			break ;
		len--;
	}
	return (i);
}

char			*ft_strtrim(char const *s)
{
	size_t	cnt1;
	size_t	cnt2;
	size_t	len;
	char	*n_s;

	if (s == NULL || s[0] == '\0')
		return ("");
	else
	{
		len = ft_strlen(s);
		cnt1 = ft_firstsp(s);
		if (cnt1 == len)
			return ("");
		cnt2 = ft_lastsp((len - cnt1 - 1), &s[cnt1]);
		if (!(n_s = (char *)malloc(sizeof(*s) * (len - cnt1 - cnt2 + 1))))
			return (NULL);
		ft_strncpy(n_s, &s[cnt1], (len - cnt1 - cnt2));
		n_s[len - cnt1 - cnt2] = '\0';
	}
	return (n_s);
}
