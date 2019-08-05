/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:39:18 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/24 23:39:19 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "read_line.h"

///*** Helper Function ***///

int			ft_sum_asci(char str[])
{
	int sum;

	if (str == NULL)
		return (0);
	sum = 0;
	while (*str != '\0')
	{
		sum += *str;
		str++;
	}
	return (sum);
}


t_tokens	*ft_new_token()
{
	t_tokens *st_token;

	st_token = (t_tokens *)malloc(sizeof(t_tokens));
	st_token->token = 0;
	st_token->value = NULL;
	st_token->prev = NULL;
	st_token->next = NULL;
	st_token->indx = -1;
	st_token->is_arg = 0;
	return (st_token);
}

void		ft_fill_token(t_tokens **st_tokens, int token, char *value, int indx)
{
	t_tokens *prev;

	(*st_tokens)->token = token;
	(*st_tokens)->value = value;
	(*st_tokens)->indx = indx;
	(*st_tokens)->next = ft_new_token();
	prev = (*st_tokens);
	(*st_tokens) = (*st_tokens)->next;
	(*st_tokens)->prev = prev;
}

void		ft_upd_token(t_tokens *st_tokens, int token, char *value)
{
	if (st_tokens == NULL)
		return ;
	st_tokens->token = token;
	if (st_tokens->value != NULL)
		ft_strdel(&(st_tokens->value));
	st_tokens->value = ft_strdup(value);
}


///*** LEXER *****////

void		ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int i;
	int quote;

	i = 0;
	quote = arg[0];
	while (arg[i] != '\0')
	{
		if (i != 0 && arg[i] == quote)
		{
			ft_fill_token(st_tokens, T_QUO, ft_strsub(arg , 0, i + 1), indx);
			*j += i;
			return ;
		}
		i++;
	}
}

void		ft_lexer_red(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int i;
	int k;
	char str[5];

	i = 0;
	k = 0;
	ft_bzero(str, 5);
	while (arg[i] != '\0')
	{
		if (arg[i] == '&' && i != 2)
			str[k++] = '&';
		else if (arg[i] == '&')
			str[k++] = ERRO_IN_AND;
		else if (arg[i] == '>' || arg[i] == '<')
		{
			str[k++] = arg[i];
			if ((arg[i + 1] == arg[i] /*|| arg[i + 1] == '<'*/) && ++i) /// Redirection >> OR Here doc	<<
				str[k++] = arg[i];
		}
		else if (arg[i] == '-' && k == 2 && str[1] == '&') // Check dash if in pos 2 " >>- || >&- "
			str[k++] = '-';
		else if (i-- || 1)
			break ;
		i++;
	}
	ft_fill_token(st_tokens, ft_sum_asci(str) * -1, ft_strdup(str), indx);
	*j += i;
}

void		ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j, int indx)
{
	int i;
	char *temp;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == ' ' || arg[i + 1] == '\t' || arg[i + 1] == '\0' || arg[i + 1] == '&' || arg[i + 1] == '|' || arg[i + 1] == '>' || arg[i + 1] == '<')
		{
			temp = ft_strsub(arg, 0, i + 1);
			ft_fill_token(st_tokens, T_TXT, temp, indx);
			break ;
		}
		i++;
	}
	*j += i;
}

t_tokens	*ft_lexer(char **args)
{
	char *arg;
	t_tokens *st_tokens;
	t_tokens *st_head;
	int i;
	int j;

	i = 0;
	st_tokens = ft_new_token();
	st_head = st_tokens;
	while (args[i] != '\0')
	{
		j = 0;
		arg = args[i];
		while (arg[j] != '\0')
		{
			if (arg[j] == '"' || arg[j] == '\'')						// Quotes
				ft_lexer_quot(&st_tokens, &arg[j], &j, i);
			else if (arg[j] == '&' && ft_check_char("><", arg[j + 1]))	// '&' with redirection
				ft_lexer_red(&st_tokens, &arg[j], &j, i);
			else if (arg[j] == '>' || arg[j] == '<')					// Redirection
				ft_lexer_red(&st_tokens, &arg[j], &j, i);
			else if (st_tokens->prev != NULL && st_tokens->prev->token == T_RED_OUT_A && arg[j] == '-' && j != 0 && arg[j - 1] == '&') // append - to redirection if separated execpt (&>-)
				ft_upd_token(st_tokens->prev, T_RED_OUT_B, ">&-");
			else
				ft_lexer_txt(&st_tokens, &arg[j], &j, i);				// Text
			j++;
		}
		i++;
	}
	// free last node // and protect it
	st_tokens->prev->next = NULL;
	free(st_tokens);
	
		st_tokens = st_head;
		while (st_tokens != NULL)
		{
			dprintf(fd_err, "Token = <%d> : %s\n",st_tokens->token,st_tokens->value);
			st_tokens = st_tokens->next;
		}
		dprintf(fd_err,"\n--------------\n");
	//exit(0);
	
	return (st_head);
}
