/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 23:32:53 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/21 23:32:54 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ft_rm_quot(char **str)
{
	int i;
	int index;
	int	bl_quot;

	i = 0;
	bl_quot = 0;
	index = 0;
	while(STR(i))
	{
		if (bl_quot && STR(i) == '|')
		{
			*str = ft_add_char(*str, i++, '\\', 1);
		}
		if (!bl_quot && M_CHECK(STR(i), 34, 39))
		{
			bl_quot = STR(i);
			index = i;
		}
		else if (bl_quot && STR(i) == bl_quot)
		{
			ft_memmove(&STR(i), &STR(i + 1), ft_strlen(&STR(i + 1)) + 1);
			ft_memmove(&STR(index), &STR(index + 1), ft_strlen(&STR(index + 1)) + 1);
			i -= 2;
			bl_quot = 0;
			index = 0;
		}
		i++;
	}
}
////*** Function to Change sub_string with string
char	*ft_str_remp(char *str, char *remp, int start, int len, int free)
{
	char *rtn;
	int i;
	int len_remp;

	len_remp = ft_strlen(remp);
	i = len_remp - len;
	i = (i <= 0) ? 0 : i;
	rtn = ft_strnew(ft_strlen(str) + i);
	ft_memcpy(rtn, str, start);
	ft_memcpy(&rtn[start],remp, len_remp);
	ft_strcpy(&rtn[start + len_remp], &str[start + len + 1]);
	if (free == 1 || free == 3)
		ft_strdel(&str);
	if (free == 2 || free == 3)
		ft_strdel(&remp);
	return (rtn);
}

////*** Swap Variable with value
char	*ft_swap_vrb(char *arg, int j, char **environ)
{
	int i;
	int index_vrb;
	char *temp;
	char *value;

	if (arg == NULL || !(*arg))
		return NULL;
	i = 0;
	index_vrb = j + 1;
	while (arg[++j])
	{
		if (!ft_isalphanum(arg[j]))
			break ;
		i++;
	}
	/// Get value of Variable
	temp = ft_strsub(arg, index_vrb, i);
	value = ft_get_vrb(temp, environ);
	/// Change Vrb with value
	i = ft_strlen(temp);
	ft_strdel(&temp);
	temp = ft_str_remp(arg, value, index_vrb - 1, i, 3); /// you can free value inside the func
	return (temp);
}

void	ft_corr_args(char **argv, char **environ)
{
	int i;
	int j;
	int quoted;

	i = 0;
	if (*argv == NULL)
		return ;
	while (argv[i] != NULL)
	{
		quoted = 0;
		j = -1;
		//if ((quoted = ft_check_charr(argv[i], (int[]){34, 39, -1}, 0)))
		//	ft_rm_quot(&(argv[i]));
		while (argv[i][++j])
		{
			
			if (argv[i][j] == '\\')
				continue ;
			if (argv[i][j] == '$' && M_CHECK(quoted, 0 , 34) && argv[i][j + 1])
				argv[i] = ft_swap_vrb(argv[i], j, environ);
			else if (argv[i][j] == '~' && !quoted)
				argv[i] = ft_str_remp(argv[i], ft_get_vrb("HOME" , environ), j, 1, 3);
		}
		i++;
	}
}