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
	# define TAB(x)  (*src)[x]
	# define STR(x)  (*str)[x]
	# define PROMPT 3
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
	int					*fds;
	struct s_pipes		*next;
}						t_pipes;

/// Main
int			ft_cmd_exec(char **args, char **env);
int					ft_check_built(char **arg, char ***env);
int					ft_creat_interf(struct termios *st_savedattr);
char		*ft_read_sh(int fd);
/// Builtins
void				ft_buil_echo(char **arg, char **env);
void				ft_buil_cd(char **arg, char ***env);
void				ft_builtenv_cmd(char **args, char ***env);
void				ft_buil_env(char **args, char ***env);
void				ft_buil_setenv(char **args, char ***env, int len_args);
void				ft_buil_unsetenv(char *arg, char ***env);
int					ft_print_var(char *arg, char **env);
/// Variable
char				*ft_get_vrb(char *vrb, char **env);
void				ft_set_vrb(char *vrb, char ***env, int rm);
void				ft_add_vrb(char *arg, char ***env);
/// Error
void				ft_print_error(char *msg, char *para1, char *para2, int rm);
void		ft_err_exit(char *str);
int					ft_error_cd(char *path, char **arg);
/// Updated
char				**ft_str_split(char const *s, char *c);
int					get_next_line(const int fd, char **line);
char                **ft_str_split_q(char **s, char *c);
/// helper
char				*ft_find_path(char *arg, char **env);
int					ft_count_word(const char *str, char *c);

///*quote
void				ft_rm_quot(char *str);
void				ft_corr_args(char **argv, char **environ);

///* Error handler
void				ft_intia_err(char *tty);
int					ft_error_semic(char *str_arg, char **args_cmd);

///* Signals
void				ft_init_signal(int sig, t_termios *st_saveattr);

void				ft_call_handler();

///* interface
void				ft_init_interf(t_termios *st_savedattr);
void				ft_restor_attr(int fd, t_termios *st_savedattr);
int					ft_index_cur(t_dimen *st_dimen, int *r, int *c);
int					ft_correc_cur(t_dimen *st_dimen);
void				ft_shift_cur(t_dimen *st_dimen, int nbr, int bl);
void				ft_print_char(char **arg, int temp, t_dimen *st_dimen);


///* Dimention
void		ft_move_cur(char capa[2], int c, int r);
void		ft_capa_str(char capa[2]);
int			ft_putchar_err(int c);
t_dimen		*ft_init_dim();

///* Buttons
int     ft_buttons(int btn, char **arg, t_dimen *st_dimen);

#endif