/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:31:48 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/19 13:31:50 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char    *ft_complete_thename(char *s)
{
    char *begin;

    if (ft_strlen(s) == 0)
        return (NULL);
    if (!(begin = ft_strrchr(s, ' ')))
        return (ft_strdup(s));
    return (ft_strdup(begin + 1));
}

char	ft_looks_like(char *name, char *begin)
{
	int i;
	int len;

	len = ft_strlen(begin);
	i = 0;
	if ((int)ft_strlen(name) <= len)
		return (0);
	if (!ft_strncmp(name, begin, len))
		return (len);
	return (0);
}

char	*ft_search_in_dir(char *begin, char *dirname)
{
	DIR *dir;
	struct dirent *dp;
	int	ret;

	dir = opendir(dirname);
	while ((dp = readdir(dir)))
	{
		if ((ret = ft_looks_like(dp->d_name, begin)) > 0)
			return (ft_strdup(dp->d_name + ret));
	}
	return (NULL);
}

char	*ft_search_in_thepath(char *path, char *begin)
{
	char **tb;
	char *ret;
	int j;

	j = -1;
	fprintf(g_fd, "tb == ||");
	if (!(tb = ft_strsplit(path, ':')))
		return (NULL);
	fprintf(g_fd, "tb == |%s|\n", tb[0]);
	while (tb[++j])
		if ((ret = ft_search_in_dir(begin, tb[j])))
			return(ret);
	return (NULL);
}

char    *ft_auto_completion(t_cursor *pos, t_history *his, char *s)
{
    char	*begin;
	char	*complete;
	char	*new;
	int		len;

    if (pos->index != (int)ft_strlen(s) || !(begin = ft_complete_thename(s)))
		return (s);
	complete = ft_search_in_dir(begin, ".");
	if (!complete)
		complete = ft_search_in_thepath(his->path, begin);
	if (!complete)
		return (s);
	len = ft_strlen(complete);
	ft_putstr_term(pos->num_col, complete, pos);
	new = ft_strfreejoin(s, complete);
	ft_get_end_of_line_pos(pos, new, pos->num_col);
	ft_get_new_pos(pos, len);
	pos->index += len;
	free(begin);
	return (new);
}
