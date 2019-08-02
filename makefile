NAME = 21sh

SRC = ./src/
S_21SH = ft_built_env.c ft_builtins.c ft_error_handler.c\
	ft_func_minish.c ft_quote.c ft_strsplit.c ft_strsplit_q.c\
	ft_variable.c minishell.c ft_signals.c\
	ft_lexer.c ft_pipe.c ft_execution.c\
	read_line/addition.c\
	read_line/auto_completion.c\
	read_line/copy_paste.c\
	read_line/ctrl_d.c\
	read_line/delete.c\
	read_line/ft_read_line.c\
	read_line/history.c\
	read_line/home_end.c\
	read_line/initial.c\
	read_line/move_by_lines.c\
	read_line/move_by_word.c\
	read_line/moving_cursor.c\
	read_line/output.c\
	read_line/quotes.c\
	read_line/reset_position.c\
	read_line/selection1.c\
	read_line/selection2.c\
	read_line/termcap.c

#S_SELECT = ft_select.c ft_button.c ft_func_h.c ft_func_del.c\
	ft_print.c ft_func_dim.c ft_conf_signal.c ft_hand_signal.c\
	ft_func_task.c ft_func_h_lst.c ft_func_hdim.c

FLAG = #-Wall -Wextra -Werror
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
	gcc -g -c $(FLAG) $(SRC_21SH) -I $(INCL)
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
