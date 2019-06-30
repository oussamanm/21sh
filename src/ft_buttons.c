/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:14:52 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/27 16:14:58 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void     ft_btn_right(t_dimen *st_dimen)
{
    int c;
    int r;
    int temp;

    temp = st_dimen->index_c / st_dimen->nbr_cln;
    (st_dimen->index_c)++;
    if (ft_index_cur(st_dimen, &r, &c))
        return ;
    if (temp != r)
        ft_capa_str("do");
    else
        ft_capa_str("nd");
}

void     ft_btn_left(t_dimen *st_dimen)
{
    int c;
    int r;
    int temp;

    temp = st_dimen->index_c / st_dimen->nbr_cln;
    (st_dimen->index_c)--;
    if (ft_index_cur(st_dimen, &r, &c))
        return ;
    if (temp != r)
    {
        dprintf(fd_err,"temp = %d  and  r = %d \n",temp,r);
        ft_capa_str("up");
        ft_move_cur("ch", 0, st_dimen->nbr_cln - 1);
    }
    else
        ft_capa_str("le");
}

int     ft_buttons(int btn, char **arg, t_dimen *st_dimen)
{
    UNUSED(arg);
    if (btn == BTN_RG)
        ft_btn_right(st_dimen);
    else if (btn == BTN_LF)
        ft_btn_left(st_dimen);

    return (0);
}