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

int		ft_sum_asci(char str[])
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
	return (st_token);
}

void	ft_fill_token(t_tokens **st_tokens, int token, char *value, int indx)
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

void	ft_upd_token(t_tokens *st_tokens, int token, char *value)
{
	if (st_tokens == NULL)
		return ;
	st_tokens->token = token;
	if (st_tokens->value != NULL)
		ft_strdel(&(st_tokens->value));
	st_tokens->value = ft_strdup(value);
}

///*** LEXER *****////
void		ft_err_lexer(t_pipes *st_pipes)
{
	UNUSED(st_pipes);

}

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
		if (arg[i] == '&')
			str[k++] = '&';
		else if (arg[i] == '>' || arg[i] == '<')
		{
			str[k++] = arg[i];
			if ((arg[i + 1] == '>' || arg[i + 1] == '<') && ++i) /// Redirection >> OR Here doc	<<
				str[k++] = arg[i];
		}
		else if (arg[i] == '-' && k == 2) // Check dash if in pos 2 " >>- || >&- "
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
		if (arg[i + 1] == ' ' || arg[i + 1] == '\t' || arg[i + 1] == '\0' || !ft_isalphanum(arg[i + 1]))
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
			else if (st_tokens->prev != NULL && st_tokens->prev->token == T_RED_OUT_A && arg[j] == '-')
				ft_upd_token(st_tokens->prev, T_RED_OUT_B, ">&-");
			else
				ft_lexer_txt(&st_tokens, &arg[j], &j, i);				// Text
			j++;
		}
		i++;
	}
	// free last node
	st_tokens->next = NULL;
	/*
		st_tokens = st_head;
		while (st_tokens != NULL)
		{
			printf("<%d> : %s \t\t and his prev = %s\n",st_tokens->token,st_tokens->value,(st_tokens->prev != NULL) ? st_tokens->prev->value : "NULL");
			st_tokens = st_tokens->next;
		}
		printf("\n----\n");
	*/
	return (st_head);
}

///*** PARSER *****////

t_redir		*ft_new_redir()
{
	t_redir	*st_redir;

	st_redir = (t_redir *)malloc(sizeof(t_redir));
	st_redir->next = NULL;
	return (st_redir);
}

void		ft_init_redi(t_redir *st_redir, int type_red)
{
	if (st_redir == NULL)
		return ;
	st_redir->type_red = type_red;
	///Right redirection
	if (type_red == 1)
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = -1;
		st_redir->fd_des = -1;
		st_redir->fd_close = -1;
	}
	else if (type_red == 0)
	{
		st_redir->fd_red = 0;
		st_redir->fd_des = -1;
		st_redir->fd_err = -1;
		st_redir->fd_close = -1;
	}
}

int		ft_isalldigit(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/*
INPUT
wc: stdin: read: Is a directory
bash: asd: No such file or directory
bash: ttt: Permission denied
OUTPUT
bash :ggg : Is a directory
bash: ttt: Permission denied
*/

int		ft_check_file(char *file, int mode) /// mode == 0 :read || else : write
{
	int bl;
	struct stat st_stat;

	mode = (mode == 0) ? R_OK : W_OK;
	bl = 0;
	if (access(file, F_OK) == 0)
	{
		if (lstat(file, &st_stat) == 0 && S_ISDIR(st_stat.st_mode) && ++bl)
			ft_print_error("Is a directory", NULL, file, 0);
		else if (access(file, mode) != 0 && ++bl)
			ft_print_error(FIL_PD, NULL, file, 0);
	}
	else if (mode == R_OK && ++bl)
		ft_print_error(FIL_NS, NULL, file, 0);
	return (bl);
}

int		ft_open_file(char *file, int type)
{
	int fd;
	int flag;

	if (file == NULL)
		return (-1);
	fd = -1;
	if (ft_check_file(file, type) == 0)
	{
		flag = FLAG_TYPE(type);
		if ((fd = open(file, flag | O_CREAT, 0644)) == -1)
			printf("Error in open File");
	}
	return (fd);
}

void	ft_redi_out(t_redir *st_redir, t_tokens *st_tokens)
{
	/// Initiale Vrb redirection
	ft_init_redi(st_redir, 1);
	if (st_tokens->token == T_RED_OUT_S) // 7>file
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = ft_open_file(st_tokens->next->value, 1);
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_OUT_A) /// >& || &>
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		if ((st_tokens->value)[1] == '&' && ft_isalldigit(st_tokens->next->value))
		{
			st_redir->fd_des = ft_atoi(st_tokens->next->value);
			st_tokens->next->is_arg = 1;
		}
		else // &> . >&FILE
		{
			st_redir->fd_red = 1;
			st_redir->fd_err = 2;
			st_redir->fd_des = ft_open_file(st_tokens->next->value, 1);
			st_tokens->next->is_arg = 1;
		}
	}
	else if (st_tokens->token == T_RED_OUT_B) // >&-
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_close = ft_atoi(st_tokens->prev->value);
		else
			st_redir->fd_close = 1;
	}
}

void	ft_redi_in(t_redir *st_redir, t_tokens *st_tokens)
{
	/// Initiale Vrb redirection
	ft_init_redi(st_redir, 0);

	if (st_tokens->token == T_RED_IN_S)
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = 1337;
	}
	else if (st_tokens->token == T_RED_IN_A) /// [n1]<& n2
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = ft_atoi(st_tokens->next->value); // next must be a number
	}
	else if (st_tokens->token == T_RED_IN_B) /// <&-
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value))
			st_redir->fd_close = ft_atoi(st_tokens->prev->value);
	}
}

void	ft_read_tokens(t_pipes *st_pipes, t_tokens *st_tokens)
{
	t_redir		*st_redir;
	t_redir		*head;

	head = NULL;
	while (st_tokens != NULL)
	{
		if (st_tokens->token < 0) /// Redirection
		{
			if (head == NULL)
			{
				st_redir = ft_new_redir();
				head = st_redir;
			}
			else
			{
				st_redir->next = ft_new_redir();
				st_redir = st_redir->next;
			}
			if (CHECK_TOKEN(st_tokens->token, T_RED_OUT_S, T_RED_OUT_A, T_RED_OUT_B))	/// OUT_PUT
				ft_redi_out(st_redir, st_tokens);
			else if (CHECK_TOKEN(st_tokens->token, T_RED_IN_S, T_RED_IN_A, T_RED_IN_B))	/// IN_PUT
				ft_redi_in(st_redir, st_tokens);
			/*else if (CHECK_TOKEN(st_tokens->token, T_RED_APP_S, T_RED_APP_M, 0))		/// APPEND
				ft_redi_app(st_pipes, st_tokens);
			else if (CHECK_TOKEN(st_tokens->token, T_RED_HER_D, 0, 0))					/// HERE_DOC
				ft_redi_her(st_pipes, st_tokens);*/
		}
		st_tokens = st_tokens->next;
	}
	st_pipes->st_redir = head;
}

void	ft_apply_redi(t_pipes *st_pipes)
{
	t_redir *lst_redi;
	
	if (st_pipes == NULL)
		return ;
	lst_redi = st_pipes->st_redir;
	while (lst_redi != NULL)
	{
		if (lst_redi->fd_close != -1)
			close(lst_redi->fd_close);
		if (lst_redi->fd_red != -1 && lst_redi->fd_des != -1)
		{
			if (dup2(lst_redi->fd_des , lst_redi->fd_red) == -1)
				ft_err_exit("Error in dub \n");
			//close(lst_redi->fd_des);
		}
		if (lst_redi->fd_err != -1 && lst_redi->fd_des != -1)
		{
			if (dup2(lst_redi->fd_des, lst_redi->fd_err) == -1)
				ft_err_exit("Error in dub \n");
			//close(lst_redi->fd_des);			
		}
		lst_redi = lst_redi->next;
	}
}

char	**ft_strr_new(int len)
{
	char **args;
	int i;

	i = 0;
	if ((args = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		ft_err_exit("Error in allocation of args\n"); /// should add free
	while (i < len)
	{
		args[i++] = NULL;
	}
	return (args);
}

void	ft_update_args(t_tokens *st_tokens, char ***args)
{
	int count;
	int	i;
	t_tokens *st_temp;

	count = 0;
	i = 0;
	st_temp = st_tokens;
	while (st_temp != NULL && st_temp->value != NULL)
	{
		if (!(st_temp->token < 0 || st_temp->is_arg == 1))
			count++;
		st_temp = st_temp->next;
	}
	st_temp = st_tokens;
	ft_strrdel(*args);
	*args = ft_strr_new(count);
	while (st_temp != NULL && st_temp->value != NULL)
	{
		if (!(st_temp->token < 0 || st_temp->is_arg == 1))
			(*args)[i++] = ft_strdup(st_temp->value);
		st_temp = st_temp->next;
	}
	(*args)[i] = NULL;
}

void	ft_parse_cmd(t_pipes *st_pipes, char ***args)
{
	t_tokens	*st_tokens;


	// Call Lexer and return list of tokens
	st_tokens = ft_lexer(*args);

	// Read Tokens and fill Redirection of node cmd
	ft_read_tokens(st_pipes, st_tokens);

	t_redir *temp;
	temp = st_pipes->st_redir;
	while (temp)
	{
		printf("TYEP REDIRECTION = %d\n",temp->type_red);
		printf("fd_red = %d\n",temp->fd_red);
		printf("fd_des = %d\n",temp->fd_des);
		printf("fd_err = %d\n",temp->fd_err);
		printf("fd_close = %d\n",temp->fd_close);
		temp = temp->next;
	}
	// Apply Redirection
	ft_apply_redi(st_pipes);

	// Remove nodes redirection and update args
	ft_update_args(st_tokens, args);
	// Check error after create tokens
		//ft_err_lexer(st_pipes);
}
//
/*
void	ft_rm_redi(t_tokens *st_tokens, char **args)
{
	t_tokens *next;
	t_tokens *prev;

	next = NULL;
	prev = NULL;
	while (st_tokens != NULL)
	{
		if (st_tokens->token < 1 || st_tokens->is_arg == 1)
		{
			next = st_tokens->next;
			prev = st_tokens->prev;
			free(st_tokens->value);
			free(st_tokens);
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->prev = prev;
			st_tokens = next;
		}
		else
			st_tokens = st_tokens->next;
	}
	st_tokens = (prev == NULL) ? next : prev;
	while (st_tokens != NULL)
	{
		if (st_tokens-prev != NULL)
			st_tokens = st_tokens->prev;
	}
}
*/
