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

#include "shell.h"

/*
**	ft_remove_quot : Remove Quote from args :
*/

void		ft_remove_quot(char **args)
{
	int		j;
	int		i;
	char	*arg;
	int		quote;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		arg = args[i];
		j = -1;
		while (arg[++j] != '\0')
		{
			if (arg[j] == '\'' || arg[j] == '"')
			{
				quote = arg[j];
				ft_strcpy(&arg[j], &arg[j + 1]);
				if ((j = ft_find_char(arg, quote)) >= 0)
					ft_strcpy(&arg[j], &arg[j + 1]);
			}
		}
		i++;
	}
}

/*
**	ft_str_remp : Function to Change sub_string with string :
*/

char		*ft_str_remp(char *str, char *remp, int start, int len)
{
	char	*rtn;
	int		len_remp;
	int		bl;

	bl = 0;
	if (!remp || !str)
		return (NULL);
	if (len < 0)
	{
		len *= -1;
		bl = 1;
	}
	len_remp = ft_strlen(remp);
	rtn = ft_strnew(ft_strlen(str) - len + len_remp);
	ft_strncpy(rtn, str, start);
	ft_strncpy(rtn + start, remp, len_remp);
	ft_strcpy(rtn + start + len_remp, str + start + len);
	if (bl == 1)
	{
		ft_strdel(&str);
		ft_strdel(&remp);
	}
	return (rtn);
}

/*
**  ft_swap_vrb : Swap Variable with value :
*/

char		*ft_swap_vrb(char *arg, int *index, char **environ)
{
	int		i;
	int		index_vrb;
	char	*temp;
	char	*value;

	if (arg == NULL || !(*arg))
		return (NULL);
	i = 0;
	index_vrb = *index + 1;
	while (arg[++(*index)] && (ft_isalpha(arg[*index]) ||
		ft_isalnum(arg[*index]) || arg[*index] == '_'))
		i++;
	*index -= i;
	temp = ft_strsub(arg, index_vrb, i);
	value = ft_get_vrb(temp, environ);
	(value == NULL) ? value = ft_strnew(0) : NULL;
	i = ft_strlen(temp);
	*index += (ft_strlen(value) - 1);
	ft_strdel(&temp);
	temp = ft_str_remp(arg, value, index_vrb - 1, i + 1);
	ft_strdel(&value);
	return (temp);
}

/*
**  ft_corr_args : Correction cmd_line by change expansions :
*/

char		*ft_corr_args(char *str_cmds, char **environ)
{
	int		i;
	char	*cmd;

	i = 0;
	if (str_cmds == NULL)
		return (NULL);
	cmd = str_cmds;
	while (cmd[i])
	{
		i += (cmd[i] == '\'') ? ft_find_char(cmd + i + 1, cmd[i]) + 2 : 0;
		if (cmd[i] == '$' && cmd[i + 1])
		{
			str_cmds = cmd;
			cmd = ft_swap_vrb(cmd, &i, environ);
			ft_strdel(&str_cmds);
			continue ;
		}
		else if (cmd[i] == '~' &&
			(cmd[i + 1] == '/' || !cmd[i + 1] || ft_isspace(cmd[i + 1])))
			cmd = ft_str_remp(cmd, ft_get_vrb("HOME", environ), i, -1);
		i += cmd[i] != '\0';
	}
	return (cmd);
}

/*
**	ft_update_tokens : update token by remove quotes
*/

void		ft_update_tokens(t_tokens *st_tokens)
{
	char		*temp;
	t_tokens	*st_temp;

	st_temp = st_tokens;
	while (st_temp)
	{
		if (st_temp->token == 1)
		{
			temp = ft_strsub(st_temp->value, 1, ft_strlen(st_temp->value) - 2);
			ft_strdel(&(st_temp->value));
			st_temp->value = temp;
		}
		st_temp = st_temp->next;
	}
}
