/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_task.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:15:32 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/15 22:45:08 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static mode_t	ft_get_type(mode_t mod)
{
	if (!mod)
		return (0);
	mod = mod & S_IFMT;
	if (mod == S_IFREG)
		return (S_IFREG);
	else if (mod == S_IFDIR)
		return (S_IFDIR);
	else if (mod == S_IFLNK)
		return (S_IFLNK);
	if (mod == S_IFCHR || mod == S_IFBLK)
		return (S_IFCHR);
	else
		return (0);
}

mode_t			ft_rtn_type(char *str)
{
	struct stat	st;
	mode_t		rtn;

	rtn = 0;
	if (lstat(str, &st) != 0)
		return (0);
	rtn = ft_get_type(st.st_mode);
	if (rtn == S_IFREG)
	{
		if (access(str, X_OK) == 0)
			rtn = 1;
	}
	return (rtn);
}

t_args			*ft_fill_list(int i, char **argv)
{
	t_args		*st_list;
	t_args		*head;
	t_args		*prev;

	prev = NULL;
	i = -1;
	st_list = (t_args *)malloc(sizeof(*st_list));
	while (argv[++i])
	{
		(i == 0) ? (head = st_list) : NULL;
		if (i != 0)
		{
			st_list->next = (t_args *)malloc(sizeof(*st_list));
			prev = st_list;
			st_list = st_list->next;
		}
		st_list->name = argv[i];
		st_list->bl_curr = (i == 0) ? 1 : 0;
		st_list->bl_selected = 0;
		st_list->prev = prev;
		st_list->type = ft_rtn_type(st_list->name);
	}
	(i > 1 && head) ? (head->prev = st_list) : NULL;
	st_list->next = (i <= 1) ? NULL : head;
	return (head);
}

void			ft_upadte_item(int index, t_args *item, t_dimen *dim)
{
	int r;
	int c;
	int i;

	i = 0;
	c = 0;
	if (item == NULL || dim == NULL)
		return ;
	index = (index < 0) ? (dim->nbr_word - 1) : index;
	index = (index >= dim->nbr_word) ? 0 : index;
	if (dim->nbr_cln != 1)
	{
		while (i < (index / dim->nbr_wrdl))
			c += (dim->max_cln[i++] + 2);
	}
	else
		c = 0;
	r = index - (i * dim->nbr_wrdl);
	ft_move_cur("cm", c, r);
	ft_print_arg(item, 0);
}

int				ft_nbr_cln(int argc, int height)
{
	float	flt;
	int		rtn;

	if (argc == 0)
		return (0);
	flt = (float)argc / height;
	rtn = argc / height;
	if ((flt - rtn) > 0)
		rtn++;
	return (rtn);
}
