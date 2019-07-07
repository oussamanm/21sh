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
    st_dimen->index_c++;
    ft_shift_cur(st_dimen, 1, 0);
}

void     ft_btn_left(t_dimen *st_dimen)
{
    st_dimen->index_c--;
    ft_shift_cur(st_dimen, -1, 0);
}

void    ft_btn_del(char **arg, t_dimen *st_dimen, int bl_del) //if bl_del == 0 -> BTN_Delte : BTN_Back 
{
    int temp;

    if ((bl_del == 1 && st_dimen->index_c == PROMPT) || st_dimen->len_arg == 0) // if cur in first cln && btn_back
        return ;
    if (bl_del == 0 && st_dimen->index_c == (st_dimen->len_arg + PROMPT))       // if cur in last cln && btn_del
        return ;
    if (st_dimen->index_c == (st_dimen->len_arg + PROMPT))
        (*arg)[st_dimen->len_arg - 1] = '\0';
    else
        ft_rm_char(*arg, st_dimen->index_c - PROMPT - 1);
    st_dimen->len_arg--;
    st_dimen->index_c--;
    
    if (bl_del == 1) /// BTN_BACK move cur one cln left
    {
        dprintf(fd_err,"ft_move_cur(LE, 0, 1);\n");
	    //tputs(tgetstr("le", NULL), 1, &ft_putchar_err);
        //dprintf(fd_err,"%d\n",tgetflag("am"));
        ft_move_cur("LE", 0, 1);
        //ft_capa_str("up");
        //sleep(3);
    }
    ft_capa_str("cd");
    temp = ft_putstr(&(*arg)[st_dimen->index_c - PROMPT]);
    if (temp != 0)
        ft_move_cur("LE", 0, temp);
}

void    ft_upd_tabmax(t_dimen *st_dimen, char *arg)
{
    int i;
    int curr_row;

    i = 0;
    while (arg[i] != '\0')
    {
        if (arg[i] == '\n' && i < (st_dimen->nbr_cln * curr_row))
        {
            
        }
        else if ()
        {

        }
    }
}

int     ft_buttons(int btn, char **arg, t_dimen *st_dimen)
{
    UNUSED(arg);
    dprintf(fd_err,"*** arg = %s  || index_cur = %d  || temp = %d\n",*arg,st_dimen->index_c, btn);
    if (btn == BTN_RG)
        ft_btn_right(st_dimen);
    else if (btn == BTN_LF)
        ft_btn_left(st_dimen);
    else if (btn == BTN_DEL || btn == BTN_BAK)
        ft_btn_del(arg, st_dimen, (btn == BTN_DEL) ? 0 : 1);
    dprintf(fd_err,"** AFTER  = %s  || index_cur = %d \n\n",*arg,st_dimen->index_c);
    
    return (0);
}