/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 02:18:45 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/06 02:18:46 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
** Calculate sum of ASCI : O
*/
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

/*
** New t_tokens : O
*/
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

/*
** Fill t_tokens : O
*/
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

/*
** ft_upd_token : append - to redirection if separated : O
*/
void		ft_upd_token(t_tokens *st_tokens, int token, char *value)
{
	if (st_tokens == NULL)
		return ;
	st_tokens->token = token;
	if (st_tokens->value != NULL)
		ft_strdel(&(st_tokens->value));
	st_tokens->value = ft_strdup(value);
}
