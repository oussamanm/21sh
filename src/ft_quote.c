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
char	*ft_str_remp(char *str, char *remp, int start, int len, int rm)
{
	char *rtn;
	int len_remp;

	if (!remp || !str)
		return NULL;
	len_remp = ft_strlen(remp);
	rtn = ft_strnew(ft_strlen(str) - len + len_remp);
	ft_strncpy(rtn, str, start);
	ft_strncpy(rtn + start, remp, len_remp);
	ft_strcpy(rtn + start + len_remp, str + start + len);
	if ((rm == 1 || rm == 3) && str)
		free(str);
	if ((rm == 2 || rm == 3) && remp)
		free(remp);
	return (rtn);
}
/*
*/
////*** Swap Variable with value
char	*ft_swap_vrb(char *arg, int *index, char **environ)
{
	int i;
	int index_vrb;
	char *temp;
	char *value;

	if (arg == NULL || !(*arg))
		return NULL;
	i = 0;
	index_vrb = *index + 1;
	while (arg[++(*index)])
	{
		if (!ft_isalpha(arg[*index]) && ft_isalnum(arg[*index]) && arg[*index] == '_')
			break ;
		i++;
	}
	/// resete index to $
	*index -= i;
	/// Get value of Variable
	temp = ft_strsub(arg, index_vrb, i);
	value = ft_get_vrb(temp, environ);
	if (value == NULL)
		value = ft_strnew(1);
	/// Change Vrb with value
	i = ft_strlen(temp);
	/// incres i by len of value
	*index += i;
	ft_strdel(&temp);
	temp = ft_str_remp(arg, value, index_vrb - 1, i + 1, 0); /// you can free value inside the func
	ft_strdel(&value);
	return (temp);
}

////*** Correction cmd_line by change expansions
char 	*ft_corr_args(char *str_cmds, char **environ)
{
	int i;
	char *cmd;

	i = 0;
	if (str_cmds == NULL)
		return (NULL);
	cmd = str_cmds;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		 	i += ft_find_char(cmd + i + 1, cmd[i]) + 2;
		if (cmd[i] == '$' && cmd[i + 1])
		{
			str_cmds = cmd;
			cmd = ft_swap_vrb(cmd, &i, environ);
			ft_strdel(&str_cmds);
		}
		else if (cmd[i] == '~' && (cmd[i + 1] == '/' || !cmd[i + 1] || ft_isspace(cmd[i + 1])))
			cmd = ft_str_remp(cmd, ft_get_vrb("HOME" , environ), i, 1, 3);
		i += cmd[i] != '\0';
	}
	return (cmd);
}
