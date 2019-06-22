/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:36:46 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 21:25:00 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_bt_del(t_args **list)
{
	t_args	*listtemp;
	t_args	*temp;

	if (list == NULL || *list == NULL)
		return (-1);
	listtemp = *list;
	while (listtemp != NULL)
	{
		if (listtemp->bl_curr == 1)
		{
			temp = listtemp->next;
			ft_lst_delitm(list, listtemp);
			*list = (temp == NULL) ? NULL : *list;
			if (temp == NULL)
				return (-1);
			temp->bl_curr = 1;
			if (*list == listtemp)
				*list = temp;
			break ;
		}
		listtemp = listtemp->next;
		if (listtemp == *list)
			break ;
	}
	return (3);
}

void		ft_lst_del(t_args **lst)
{
	t_args *head;
	t_args *temp;

	if (lst == NULL || (*lst) == NULL)
		return ;
	head = *lst;
	temp = (*lst)->next;
	while (temp != head)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = NULL;
		(*lst) = temp;
		if (temp == NULL)
			return ;
	}
}

static void	ft_null_node(t_args **node)
{
	(*node)->next = NULL;
	(*node)->prev = NULL;
}

void		ft_lst_delitm(t_args **lst, t_args *item)
{
	t_args *next;
	t_args *prev;
	t_args *temp;

	temp = *lst;
	while (temp != NULL)
	{
		if (temp == item)
		{
			next = temp->next;
			prev = temp->prev;
			if (next != prev)
			{
				next->prev = prev;
				prev->next = next;
			}
			else if (prev != NULL && next != NULL)
				ft_null_node(&next);
			free(temp);
			return ;
		}
		temp = temp->next;
		temp = (temp == *lst) ? NULL : temp;
	}
}
