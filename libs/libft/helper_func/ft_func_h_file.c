/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 03:42:03 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:28:03 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_find_file(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dr;
	int				len;

	dir = opendir(path);
	if (access(path, F_OK) != 0 || dir == NULL)
		return (-1);
	len = ft_strlen(file);
	while ((dr = readdir(dir)) != NULL)
	{
		if (len == dr->d_namlen && ft_strcmp(dr->d_name, file) == 1)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}