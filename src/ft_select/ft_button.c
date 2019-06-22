/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:11:33 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/15 22:06:42 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_bt_select(t_args *st_list, t_dimen *dim)
{
	t_args	*list_temp;
	int		index;

	index = 0;
	list_temp = st_list;
	while (list_temp != NULL)
	{
		if (list_temp->bl_curr == 1 || list_temp->next == NULL)
		{
			list_temp->bl_selected++;
			list_temp->bl_curr = (list_temp->next == NULL) ? 1 : 0;
			ft_upadte_item(index, list_temp, dim);
			if (list_temp->next == NULL)
				break ;
			list_temp->next->bl_curr = 1;
			ft_upadte_item(index + 1, list_temp->next, dim);
			break ;
		}
		list_temp = list_temp->next;
		if (list_temp == st_list)
			break ;
		index++;
	}
	return (1);
}

int		ft_bt_up(t_args *st_list, t_dimen *dim)
{
	t_args	*st_listtemp;
	int		index;

	index = 0;
	st_listtemp = st_list;
	while (st_listtemp != NULL && st_listtemp->next != NULL)
	{
		if (st_listtemp->bl_curr == 1)
		{
			st_listtemp->bl_curr = 0;
			st_listtemp->prev->bl_curr = 1;
			ft_upadte_item(index, st_listtemp, dim);
			ft_upadte_item(index - 1, st_listtemp->prev, dim);
			break ;
		}
		st_listtemp = st_listtemp->next;
		if (st_listtemp == st_list)
			break ;
		index++;
	}
	return (1);
}

int		ft_bt_dw(t_args *st_list, t_dimen *dim)
{
	t_args	*st_listtemp;
	int		index;

	index = 0;
	st_listtemp = st_list;
	while (st_listtemp != NULL && st_listtemp->next != NULL)
	{
		if (st_listtemp->bl_curr == 1)
		{
			st_listtemp->bl_curr = 0;
			st_listtemp->next->bl_curr = 1;
			ft_upadte_item(index, st_listtemp, dim);
			ft_upadte_item(index + 1, st_listtemp->next, dim);
			break ;
		}
		st_listtemp = st_listtemp->next;
		if (st_listtemp == st_list)
			break ;
		index++;
	}
	return (1);
}

int		ft_bt_rg(t_args *list, t_dimen *dim)
{
	t_args	*temp;
	int		index;

	index = -1;
	temp = list;
	while (temp != NULL && (++index == 0 || temp != list) && temp->next != NULL)
	{
		if (temp->bl_curr == 1)
		{
			temp->bl_curr = 0;
			ft_upadte_item(index, temp, dim);
			if (dim->nbr_cln > 1)
				index = ft_geti_rg(index, dim, &temp, list);
			else
			{
				index++;
				temp = temp->next;
				temp->bl_curr = 1;
			}
			ft_upadte_item(index, temp, dim);
			break ;
		}
		temp = temp->next;
	}
	return (1);
}

int		ft_bt_lf(t_args *list, t_dimen *dim)
{
	t_args	*temp;
	int		index;

	index = -1;
	temp = list;
	while (temp != NULL && (++index == 0 || temp != list) && temp->next != NULL)
	{
		if (temp->bl_curr == 1)
		{
			temp->bl_curr = 0;
			ft_upadte_item(index, temp, dim);
			if (dim->nbr_cln > 1)
				index = ft_geti_lf(index, dim, &temp, list);
			else
			{
				index--;
				temp = temp->prev;
				temp->bl_curr = 1;
			}
			ft_upadte_item(index, temp, dim);
			break ;
		}
		temp = temp->next;
	}
	return (1);
}
