/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_strr2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 03:42:48 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:32:16 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		**alloc_chain(char **env, int nbr)
{
	char	**new_env;
	int		i;

	i = 0;
	if (*env == NULL || *env == NULL)
		return (NULL);
	new_env = (char **)malloc(sizeof(*new_env) * (ft_strrlen(env) + nbr + 1));
	while (env[i] && env[i] != NULL)
	{
		new_env[i] = ft_strnew(ft_strlen(env[i]));
		new_env[i] = ft_strcpy(new_env[i], env[i]);
		i++;
	}
	while (nbr > 0)
	{
		new_env[i] = NULL;
		nbr--;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char		**ft_strr_new(int len)
{
	char **args;
	int i;

	i = 0;
	if ((args = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
	{
		ft_putstr("Error in allocation of args\n");
		exit(0);
	}
	while (i < len)
	{
		args[i++] = NULL;
	}
	args[i] = NULL;
	return (args);
}