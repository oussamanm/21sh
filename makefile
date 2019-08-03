NAME = 21sh

SRC = ./src/
OBJS = ft_built_env.o ft_builtins.o ft_error_handler.o\
	ft_func_minish.o ft_quote.o ft_strsplit.o ft_strsplit_q.o\
	ft_variable.o minishell.o ft_signals.o\
	ft_lexer.o ft_pipe.o ft_execution.o\
	read_line/addition.o\
	read_line/auto_completion.o\
	read_line/copy_paste.o\
	read_line/ctrl_d.o\
	read_line/delete.o\
	read_line/ft_read_line.o\
	read_line/history.o\
	read_line/home_end.o\
	read_line/initial.o\
	read_line/move_by_lines.o\
	read_line/move_by_word.o\
	read_line/moving_cursor.o\
	read_line/output.o\
	read_line/quotes.o\
	read_line/reset_position.o\
	read_line/selection1.o\
	read_line/selection2.o\
	read_line/termcap.o\
	read_line/clear_readline.o


FLAG = -Wall -Wextra -Werror 
INCL = ./includes
LIBFT_PATH = libs/libft/
LIBFT = libft.a

OBJS_21SH = $(addprefix ./src/, $(OBJS))


all : $(NAME)

$(NAME) : $(LIBFT_PATH)/$(LIBFT) $(OBJS_21SH)
	@gcc -g $(FLAG) $(OBJS_21SH) -I $(INCL) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -ltermcap 
%.o : %.c
	@gcc $(FLAG) -I $(INCL) -c $< -o $@

$(LIBFT_PATH)/$(LIBFT) :
	@make -C $(LIBFT_PATH)

clean :
	@make clean -C $(LIBFT_PATH)
	@rm -f $(SRC)/*.o $(SRC)/read_line/*.o

fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f ./$(NAME)

re : fclean all
