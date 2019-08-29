/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:24:55 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:26:21 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_get_vrb : return variable (allocated) || NULL :
*/

char		*ft_get_vrb(char *vrb, char **env)
{
	int		len;
	char	*value;

	if (vrb == NULL || env == NULL)
		return (NULL);
	len = ft_strlen(vrb);
	while (*env != NULL)
	{
		if (ft_strnequ(*env, vrb, len))
		{
			value = ft_strsub(*env, len + 1, ft_strlen(*env) - len - 1);
			return (value);
		}
		env++;
	}
	return (NULL);
}

/*
**	ft_add_vrb : add variable to environ :
*/

void		ft_add_vrb(char *arg, char ***env)
{
	char	**environ;
	int		len;

	if (env == NULL || *env == NULL || arg == NULL)
		return ;
	len = ft_strrlen(*env);
	if ((environ = ft_strr_dup(*env, len + 1)) == NULL)
		if (len == 0)
			environ = ft_strr_new(1);
	if (ft_find_char(arg, '=') > 0)
		environ[len] = ft_strdup(arg);
	ft_strrdel(*env);
	*env = environ;
	return ;
}

/*
**	ft_set_vrb : update vrb in environ if exist else create new  :
*/

void		ft_set_vrb(char *vrb, char ***env, int rm)
{
	int		i;
	int		len_vrb;
	char	**temp;

	if (vrb == NULL || *env == NULL)
		return ;
	i = -1;
	temp = *env;
	while (temp[++i] != NULL)
	{
		len_vrb = ft_find_char(temp[i], '=');
		if (len_vrb != -1 && ft_strncmp(vrb, temp[i], len_vrb) == 0)
		{
			ft_strdel(&temp[i]);
			temp[i] = ft_strdup(vrb);
			i = -2;
			break ;
		}
	}
	if (i != -2)
		ft_add_vrb(vrb, env);
	(rm == 1) ? ft_strdel(&vrb) : NULL;
}
