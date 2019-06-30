/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:37 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:21:40 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*ft_find_path(char *arg, char **env)
{
	int		i;
	char	**str_paths;
	char	*temp;

	i = -1;
	str_paths = NULL;
	if (env == NULL || arg == NULL)
		return (NULL);
	if (env != NULL && *env != NULL)
	{
		temp = ft_get_vrb("PATH", env);
		str_paths = (temp != NULL) ? ft_str_split(temp, ":") : NULL;
		ft_strdel(&temp);
	}
	while (str_paths != NULL && str_paths[++i] != NULL)
	{
		str_paths[i] = ft_strjoir(str_paths[i], "/", 1);
		temp = ft_strjoir(str_paths[i], arg, 0);
		if (access(temp, F_OK) != 0)
			continue ;
		ft_strrdel(str_paths);
		return (temp);
	}
	ft_strrdel(str_paths);
	return (NULL);
}
