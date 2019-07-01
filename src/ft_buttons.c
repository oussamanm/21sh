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
    ft_crea_cur(st_dimen, 1, 1);
    st_dimen->index_c++;
    if (!ft_correc_cur(st_dimen))
    {
        ft_shift_cur(st_dimen);
        st_dimen->index_c--;
        ft_crea_cur(st_dimen, 0, 1);
        st_dimen->index_c++;
    }
}

void     ft_btn_left(t_dimen *st_dimen)
{
    ft_crea_cur(st_dimen, 1, -1);
    st_dimen->index_c--;
    if (!ft_correc_cur(st_dimen))
    {
        ft_shift_cur(st_dimen);
        st_dimen->index_c++;
        ft_crea_cur(st_dimen, 0, -1);
        st_dimen->index_c--;
    }
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