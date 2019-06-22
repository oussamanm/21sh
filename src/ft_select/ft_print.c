/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:16:24 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 21:42:39 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_colortype(t_args *item)
{
	if (item->type == S_IFREG)
		ft_putstr_fd(_WHITE, 2);
	else if (item->type == S_IFDIR)
		ft_putstr_fd(_CYAN, 2);
	else if (item->type == 1)
		ft_putstr_fd(_RED, 2);
	else if (item->type == S_IFLNK)
		ft_putstr_fd(_MAGENTA, 2);
	else if (item->type == S_IFCHR)
		ft_putstr_fd(_YELLOW, 2);
	else
		ft_putstr_fd(_GRAY, 2);
}

int			ft_print_arg(t_args *st_list, int i_tab)
{
	int	i;

	if (st_list == NULL)
		return (0);
	i = 0;
	while (st_list != NULL)
	{
		if (i == i_tab)
		{
			ft_colortype(st_list);
			if (st_list->bl_selected)
				ft_capa_str("mr");
			if (st_list->bl_curr)
				ft_putstr_fd("\033[4m", 2);
			ft_putstr_fd(st_list->name, 2);
			ft_putstr_fd("\033[m", 2);
			ft_putstr_fd("\033[0m", 2);
			ft_capa_str("me");
			break ;
		}
		st_list = st_list->next;
		i++;
	}
	return (ft_strlen(st_list->name));
}

static void	ft_print_args(t_args *st_list, t_dimen *dim)
{
	int i;
	int j;
	int tmp_cln;
	int temp;

	i = 0;
	j = 0;
	tmp_cln = 0;
	if (dim == NULL)
		return ;
	while (i < dim->nbr_wrdl)
	{
		j = i;
		tmp_cln = 0;
		while (tmp_cln < dim->nbr_cln && j < dim->nbr_word)
		{
			temp = ft_print_arg(st_list, j);
			ft_repeat_char(' ', (dim->max_cln[tmp_cln] - temp));
			tmp_cln++;
			(tmp_cln != dim->nbr_cln) ? ft_putstr_fd("  ", 2) : NULL;
			j += dim->nbr_wrdl;
		}
		(++i < dim->nbr_wrdl) ? (void)ft_putchar_fd('\n', 2) : NULL;
	}
}

void		ft_upd_interf(t_args *st_list, t_dimen *dim)
{
	ft_capa_str("ti");
	if (ft_check_dim(dim))
	{
		ft_putstr("not enough lines and/or columns");
		return ;
	}
	ft_print_args(st_list, dim);
}

void		ft_seleted_itm(t_args *list)
{
	t_args *head;

	if (list == NULL)
		return ;
	head = list;
	while (list != NULL)
	{
		if (list->bl_selected == 1)
		{
			ft_putstr(list->name);
			list = list->next;
		}
		else
		{
			list = list->next;
			if (list == head || list == NULL)
				return ;
			continue ;
		}
		if (list == head || list == NULL)
			return ;
		ft_putstr(" ");
	}
}
