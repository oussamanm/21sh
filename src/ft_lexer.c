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

/*
** Lexer
*/

t_tokens	*ft_new_token()
{
	t_tokens *st_token;

	st_token = (t_tokens *)malloc(sizeof(t_tokens));
	st_token->token = 0;
	//st_token->value = ft_strnew(len_content);
	st_token->value = NULL;
	st_token->next = NULL;
	return (st_token);
}

void	ft_fill_token(t_tokens **st_tokens, int token, char *value)
{
	(*st_tokens)->token = token;
	(*st_tokens)->value = value;
	(*st_tokens)->next = ft_new_token();
	(*st_tokens) = (*st_tokens)->next;
}

///*** Check error lexer
void	ft_err_lexer(t_pipes *st_pipes)
{
	UNUSED(st_pipes);

}

void	ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j)
{
	int i;
	int quote;

	i = *j;
	quote = arg[0];
	while (arg[i] != '\0')
	{
		if (i != 0 && arg[i] != quote)
		{
			(*st_tokens)->token = T_TXT;
			(*st_tokens)->value = ft_strsub(arg , *j, i);
			*j += i;
		}
		i++;
	}
}


void	ft_lexer_red(t_tokens **st_tokens, char *arg, int *j)
{
	int i;
	int k;
	char str[5];

	i = *j;
	k = 0;
	ft_bzero(str, 5);
	while (arg[i] != '\0')
	{
		if (arg[i] == '&' && ++i)
			str[k++] = '&';
		if (arg[i] == '>' || arg[i] == '<')
		{
			str[k++] = arg[i];
			if (arg[i + 1] == '>' && ++i) 				/// Redirection >>
				str[k++] = '>';
			else if (arg[i + 1] == '<' && ++i) 			/// Here doc	<<
				str[k++] = '<';
		}
		if (arg[i] == '-')
			str[k++] = '-';
		i++;
	}
	*j += i;
}

void	ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j)
{
	int i;
	char *temp;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == ' ' || arg[i + 1] == '\t' || arg[i + 1] == '\0' || !ft_isalphanum(arg[i + 1]))
		{
			temp = ft_strsub(arg, 0, i + 1);
			ft_fill_token(st_tokens, T_TXT, temp);
			break ;
		}
		i++;
	}
	*j += i;
}

void	ft_lexer(t_pipes *st_pipes, char **args)
{
	char *arg;
	t_tokens *st_tokens;
	t_tokens *st_head;
	int i;
	int j;

	i = 0;
	ft_err_lexer(st_pipes);
	st_tokens = ft_new_token();
	st_head = st_tokens;
	while (args[i] != '\0')
	{
		j = 0;
		arg = args[i];
		while (arg[j] != '\0')
		{
			if (arg[j] == '"' || arg[j] == '\'')
				ft_lexer_quot(&st_tokens, arg, &j);
			else if (arg[j] == '&')
				ft_lexer_red(&st_tokens, arg, &j);
			else if (arg[j] == '>' || arg[j] == '<')
				ft_lexer_red(&st_tokens, arg, &j);
			else
				ft_lexer_txt(&st_tokens, &arg[j], &j);
			j++;
		}
		i++;
	}
	// free last node
	st_tokens->next = NULL;
	while (st_head != NULL)
	{
		printf("<%d> : %s\n",st_head->token,st_head->value);
		st_head = st_head->next;
	}
	printf("\n----\n");
}