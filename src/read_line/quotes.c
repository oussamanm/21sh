/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:56:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/18 12:45:48 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int     ft_check_quotes(char *s)
{
    int i;
    int q;

    i = 0;
    q = 0;
    while (s[i])
    {
        if (s[i] == '\'')
        {
            q = 1;
            while (s[++i])
            {
                if (s[i] == '\'')
				{
					q = 0;
					break ;
				}
            }
		}
		else if (s[i] == '\"')
		{
			q = 2;
            while (s[++i])
            {
                if (s[i] == '\"')
				{
					q = 0;
					break ;
				}
            }
		}
		else
        	i++;
    }
    return (q);
}

void    ft_quotes(char **line, t_select *select, int q)
{
	t_history his;
	char	*s;
//	int		c;

	his.history = ft_alloc_tab();
	his.his_count = 0;
//	while (1337)
//	{
	*line = ft_strjoin(*line, "\n");
	if (q == 1)
	{
		ft_putstr("heredoc> ");
		s = ft_read_line(&his, select, 9);
	}
	else if (q == 2)
	{
		ft_putstr("pipe> ");
		s = ft_read_line(&his, select, 6);
	}
	else if (q == 3)
	{	
		ft_putstr("quote> ");
		s = ft_read_line(&his, select, 7);
	}
	else if (q == 4)
	{
		ft_putstr("dquote> ");
		s = ft_read_line(&his, select, 8);
	}
	*line = ft_strjoin(*line, s);
//		c = ft_check_quotes(s);
//		if ((c == 1 && q == 1) || (c == 2 && q == 2))
//			break ;
//		if (ft_strcmp(s, ""))
//		{	
//			ft_stock_history(his.history, s, his.his_count);
//			if (his.his_count < MAX_HISTORY)
//				his.his_count++;
//		}
//	}
}
