/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:07:47 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/22 17:07:50 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _21SH_H
# define _21SH_H

# include "../libs/libft/libft.h"
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <curses.h>

int fd_err;

//**** Helper Macro
	# define BUFF_SIZE 10
	# define UNUSED(x) (void)(x)
	# define M_CHECK(x , y, z) ((x == y || x == z) ? 1 : 0)
	# define M_C (arg[i][0]==34||arg[i][0]==39)
	# define M_CC (arg[i][ft_strlen(arg[i])-1]==34||arg[i][ft_strlen(arg[i])-1]==39)
	# define M_CHECK_W(C)(C==32||C==9||C==11||C==10||C==13||C==12)
	# define M_REDIR(C) (C == '>' || C == '<')
	# define TAB(x)  (*src)[x]
	# define STR(x)  (*str)[x]
	# define PROMPT 3
	# define PATHSIZE 1024
//

//**** Error Msg
	# define FIL_NS "No such file or directory"
	# define FIL_PD "Permission denied"
	# define VRB_IA "Invalid argument"
	# define CMD_NF "Command not found"
	# define CMD_NV "not a valid identifier"
	# define FIL_NU "no such user or named directory: "
	# define FIL_ND "not a directory"
	# define SYN_ER "syntax error" 
	# define PRINT(x) printf("\n***/in %d/***\n",x);
	# define DPRINT(x,y) dprintf(fd_err, x,y);
//

//**** Buttons
	# define BTN_ESC 27			/*Esc*/
	# define BTN_SPC 32			/*Space*/
	# define BTN_ENT 10			/*Enter*/
	# define BTN_DEL 2117294875	/*Delete*/
	# define BTN_BAK 127		/*Back*/
	# define BTN_UP 4283163
	# define BTN_DW 4348699
	# define BTN_RG 4414235
	# define BTN_LF 4479771

//

//**** Tokens
	# define T_TXT 0
	# define T_RED 1
	
	# define T_HER 2
	# define T_AND 3
	# define T_MIN 4
//

//**** MACRO Capability Cursor
	//`vi' String to make the cursor invisible.

	//** ROW
		//`do' String to move the cursor vertically down one line.
		//`DO' String to move cursor vertically down n lines.
		//`up' String to move the cursor vertically up one line.
		//`UP' String to move cursor vertically up n lines.
	//** Cln
		//`le' String to move the cursor left one column.
		//`LE' String to move cursor left n columns.
		//`nd' String to move the cursor right one column.
		//`RI' String to move cursor right n columns.

	//** editing
		//`ce' String to clear from the cursor to the end of the line.

typedef struct termios	t_termios;

int glb;

typedef struct			s_dimen
{
	int					index_c;
	int					nbr_row;
	int					nbr_cln;
	int					len_arg;
	struct winsize		st_size;
}						t_dimen;

typedef struct			s_pipes
{
	char				*cmd;
	int					fds[2];
	int					fd_in;
	int					fd_out;
	int					fd_err;
	struct s_pipes		*next;
}						t_pipes;

typedef struct			s_tokens
{
	int					token;
	char				*value;
	struct s_tokens		*next;
}						t_tokens;

///*** Main
	void		exit_shell(char **env);
	char		*get_next_spli(char *cmd, char *split);
	void		ft_parser(char *cmd, char *split, char ***env);
//

///*** Builtins
	void				ft_buil_echo(char **arg, char **env);
	void				ft_buil_cd(char **arg, char ***env);
	void				ft_builtenv_cmd(char **args, char ***env);
	void				ft_buil_env(char **args, char ***env);
	void				ft_buil_setenv(char **args, char ***env, int len_args);
	void				ft_buil_unsetenv(char *arg, char ***env);
	int					ft_print_var(char *arg, char **env);
	char				*getpwd(void);
//

///*** Variable
	char				*ft_get_vrb(char *vrb, char **env);
	void				ft_set_vrb(char *vrb, char ***env, int rm);
	void				ft_add_vrb(char *arg, char ***env);
//

///*** Error handler
	void				ft_print_error(char *msg, char *para1, char *para2, int rm);
	void				ft_err_exit(char *str);
	int					ft_error_cd(char *path, char **arg);
	void				ft_intia_err(char *tty);
	int					ft_error_semic(char *str_arg, char **args_cmd);
//

///*** Updated
	char				**ft_str_split(char const *s, char *c);
	char                **ft_str_split_q(char **s, char *c);
//

///*** helper
	char				*ft_find_path(char *arg, char **env);
	int					ft_count_word(const char *str, char *c);
	char				*delete_char(char *str, int pos);
	void				edit_str(char **line, char *copy, int pos);
	int					key_is_str(char *buff);
	t_pipes				*ft_strr_list(char **args_pipe);
//

///*** Quote
	void				ft_rm_quot(char **str);
	void				ft_corr_args(char **argv, char **environ);
//


///*** Signals
	void 				ft_call_signal();
	void				ft_call_handler();
//

///*** Dimention
	void		ft_move_cur(char capa[2], int c, int r);
	void		ft_capa_str(char capa[2]);
	int			ft_putchar_err(int c);
//

///*** Pipes
	void		ft_close_pipes(t_pipes *st_pipes);
	void		ft_create_pipes(t_pipes *st_pipes);
	void		ft_apply_pipe(t_pipes *st_pipes, char ***environ);
//

///*** Lexer
	t_tokens	*ft_new_token();
	void	ft_fill_token(t_tokens **st_tokens, int token, char *value);
	void	ft_err_lexer(t_pipes *st_pipes);
	void	ft_lexer_quot(t_tokens **st_tokens, char *arg, int *j);
	void	ft_lexer_red(t_tokens **st_tokens, char *arg, int *j);
	void	ft_lexer_txt(t_tokens **st_tokens, char *arg, int *j);
	void	ft_lexer(t_pipes *st_pipes, char **args);
//

///*** Execution
	int			ft_cmd_exec(char **args, char **env);
	void		ft_split_cmd(t_pipes *st_pipes, char ***env);
	int			ft_check_built(char **arg, char ***env);
	void		ft_call_cmdss(char **str_arg, char ***environ);
//

/*
**	termacp
*/

char			*get_prompt(void);
int				get_col_pos(void);

//
#endif