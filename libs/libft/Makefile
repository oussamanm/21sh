# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: onouaman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 18:38:53 by onouaman          #+#    #+#              #
#    Updated: 2019/06/22 19:31:47 by onouaman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_countw.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
ft_isdigit.c ft_isprint.c ft_itoa.c ft_lenint.c ft_lstadd.c ft_lstcount.c\
ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_lstprint.c\
ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c\
ft_memmove.c ft_memset.c ft_nstrdup.c ft_putchar.c ft_putchar_fd.c\
ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c\
ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c\
ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c\
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c\
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c\
ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c

SRC_H = ft_func_h_file.c ft_func_h_str2.c\
ft_func_h_strr.c ft_func_h_upd.c ft_func_h_str.c ft_func_h_str3.c\
ft_func_h_strr2.c

OBJS = $(addprefix , $(SRC:.c=.o))
OBJ_H = $(addprefix , $(SRC_H:.c=.o))

INCLD = ./

all: $(NAME)


$(NAME):
	gcc $(FLAG) -c $(SRC) $(addprefix ./helper_func/, $(SRC_H)) -I $(INCLD)
	ar rc $(NAME) $(OBJS) $(OBJ_H)
	ranlib $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f a.out
	rm -f libft.a

re: fclean all
