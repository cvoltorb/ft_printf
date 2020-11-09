# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvoltorb <cvoltorb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 17:37:20 by cvoltorb          #+#    #+#              #
#    Updated: 2020/08/02 19:15:17 by cvoltorb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a

SRC =	ft_printf.c ./src/ft_printf_libft.c ./src/ft_printf_parsing.c ./src/ft_printf_print_cs.c \
		./src/ft_printf_print_di.c ./src/ft_printf_print_fe.c ./src/ft_printf_print_puxo.c \
		./src/ft_printf_print_percent.c ./src/ft_printf_utils.c ./src/ft_printf_utils2.c

OBJ =	$(SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
HDR = ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(HDR)
	@ar -rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o:%.c $(HDR)
	@$(CC) $(FLAGS) -c $< -o $@

bonus: all

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus