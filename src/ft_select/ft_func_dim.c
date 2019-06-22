/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_dim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 22:35:59 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 21:59:06 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_dimen		*ft_fill_dim(int fd, t_args *st_list)
{
	t_dimen *dim;

	dim = (t_dimen *)malloc(sizeof(*dim));
	if (ioctl(fd, TIOCGWINSZ, &(dim->st_size)) == -1)
		ft_putstr("Error to get size of terminal !!!\n");
	dim->nbr_word = ft_lst_len(st_list);
	dim->nbr_cln = ft_nbr_cln(dim->nbr_word, dim->st_size.ws_row);
	dim->nbr_wrdl = (dim->nbr_word >= dim->st_size.ws_row) ?
		dim->st_size.ws_row : dim->nbr_word;
	dim->max_cln = ft_fill_tabmax(-1, -1, dim, st_list);
	return (dim);
}

int			*ft_fill_tabmax(int i, int j, t_dimen *dim, t_args *list)
{
	t_args		*head;
	int			*rtn;
	int			max_len;
	int			temp;
	int			temp2;

	max_len = 0;
	head = list;
	temp = dim->nbr_wrdl;
	temp2 = dim->nbr_wrdl;
	temp2 -= (dim->nbr_wrdl > 1) ? 1 : 0;
	rtn = (int *)malloc(sizeof(*rtn) * dim->nbr_cln);
	while (list != NULL && (++i == 0 || head != list))
	{
		if (max_len < (int)ft_strlen(list->name))
			max_len = ft_strlen(list->name);
		if (i == temp2 || i == (dim->nbr_word - 1))
		{
			rtn[++j] = max_len;
			temp2 += temp;
			max_len = 0;
		}
		list = list->next;
	}
	return (rtn);
}

int			ft_geti_lf(int index, t_dimen *dim, t_args **list, t_args *head)
{
	int i_cln;

	i_cln = (index / dim->nbr_wrdl);
	if (i_cln > 0)
	{
		index = index - dim->nbr_wrdl;
		if (index < 0)
			index = dim->nbr_word - 1;
	}
	else if (i_cln == 0)
	{
		if (index == 0)
			index = dim->nbr_word - 1;
		else
		{
			index = (index - 1) + (dim->nbr_wrdl * (dim->nbr_cln - 1));
			if (index < 0)
				index = dim->nbr_word - 1;
			if (index > (dim->nbr_word + 1))
				index = 0;
		}
	}
	if ((*list = ft_lst_find(head, index)) != NULL)
		(*list)->bl_curr = 1;
	return (index);
}

int			ft_geti_rg(int index, t_dimen *dim, t_args **list, t_args *head)
{
	int i_cln;

	i_cln = (index / dim->nbr_wrdl);
	if (i_cln < (dim->nbr_cln - 1))
	{
		index = index + dim->nbr_wrdl;
		if (index >= dim->nbr_word)
			index = dim->nbr_word - 1;
	}
	else if (i_cln == (dim->nbr_cln - 1))
	{
		if (index == (dim->nbr_word - 1))
			index = 0;
		else
		{
			index = index - (dim->nbr_wrdl * (dim->nbr_cln - 1)) + 1;
			if (index >= dim->nbr_word)
				index = dim->nbr_word - 1;
		}
	}
	if ((*list = ft_lst_find(head, index)) != NULL)
		(*list)->bl_curr = 1;
	return (index);
}

int			ft_check_dim(t_dimen *dim)
{
	int i;
	int temp;

	i = 0;
	temp = 0;
	if (dim == NULL)
		return (-1);
	if (dim->nbr_word > dim->st_size.ws_row)
	{
		while (i < dim->nbr_cln)
		{
			temp += dim->max_cln[i];
			i++;
			if (i != dim->nbr_cln)
				temp += 2;
		}
		if (temp > dim->st_size.ws_col)
			return (1);
	}
	else if (dim->max_cln[0] > dim->st_size.ws_col)
		return (1);
	return (0);
}
