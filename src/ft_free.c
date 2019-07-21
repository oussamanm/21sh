/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:26:08 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/17 19:26:09 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ft_lst_del(t_pipes **lst)
{
	t_list *temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
        ft_strdel((*lst)->cmd);
		free(*lst);
		*lst = NULL;
		*lst = temp;
	}
	lst = NULL;
}