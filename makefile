NAME = 21sh

SRC = ./src/
S_21SH = ft_built_env.c ft_builtins.c ft_error_handler.c\
	ft_func_minish.c ft_quote.c ft_strsplit.c ft_strsplit_q.c\
	ft_variable.c get_next_line.c minishell.c ft_signals.c\
	ft_func_dim.c ft_buttons.c ft_lexer.c ft_pipe.c ft_execution.c\
	termcap/auto_complete/auto_completion.c\
	termcap/auto_complete/display_files.c\
	termcap/auto_complete/get_similar_files.c\
	termcap/auto_complete/line_handle.c\
	termcap/auto_complete/list_files.c\
	termcap/auto_complete/manage_file.c\
	termcap/auto_complete/reset_autocomplete.c\
	termcap/auto_complete/str_handle.c\
	termcap/edit_line/copy_cut.c termcap/edit_line/delete.c\
	termcap/edit_line/edit_line.c termcap/edit_line/return_key.c\
	termcap/navigate_cursor/cursor.c\
	termcap/navigate_cursor/navigate_cursor.c\
	termcap/navigate_cursor/navigate_lines.c\
	termcap/navigate_cursor/navigate_word.c termcap/quotes/quotes.c\
	termcap/select_line/select_line.c\
	termcap/select_line/select_navigate.c\
	termcap/select_list/display_select.c\
	termcap/select_list/navigate_select.c termcap/select_list/select_keys.c\
	termcap/history.c termcap/read_input.c termcap/termcap.c

#S_SELECT = ft_select.c ft_button.c ft_func_h.c ft_func_del.c\
	ft_print.c ft_func_dim.c ft_conf_signal.c ft_hand_signal.c\
	ft_func_task.c ft_func_h_lst.c ft_func_hdim.c

FLAG = -Wall -Wextra -Werror
INCL = ./includes
LIBS = ./libs

#SRC_SELECT = $(addprefix ./src/ft_select/, $(S_SELECT))
SRC_21SH = $(addprefix ./src/, $(S_21SH))

OBJS =  $(addprefix , $(S_21SH:.c=.o))

all : $(NAME)

$(NAME) :
	make re -C $(LIBS)/libft/
	mv $(LIBS)/libft/libft.a $(LIBS)
	#gcc -c $(FLAG) $(SRC_SELECT) -I $(INCL)
	gcc -c $(FLAG) $(SRC_21SH) -I $(INCL)
	#gcc -c $(FLAG) ./src/ft_select/*.c -I $(INCL)
	#gcc -c $(FLAG) ./src/*.c -I $(INCL)
	
	#mv $(OBJS) $(LIBS)/
	mv ./*.o $(LIBS)/
	#gcc -o $(NAME) $(addprefix $(LIBS)/, $(OBJS)) $(LIBS)/libft.a -ltermcap
	gcc -o $(NAME) ./libs/*.o $(LIBS)/libft.a -ltermcap

clean :
	Make clean -C $(LIBS)/libft/
	rm -f $(LIBS)/*.o

fclean : clean
	Make fclean -C $(LIBS)/libft/
	rm -f ./$(NAME)
	rm -f $(LIBS)/libft.a

re : fclean all
