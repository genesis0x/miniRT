# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 23:36:35 by hahadiou          #+#    #+#              #
#    Updated: 2023/05/09 00:11:25 by hahadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	get_next_line.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlen.c \
			ft_strtrim.c \
			ft_substr.c 

OBJS = ${addprefix obj/, ${SRCS:.c=.o}}

OBJ_PATH = obj

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I../inc/

RM = rm -f

all: ${NAME}

obj/%.o: %.c
			@mkdir -p $(OBJ_PATH)
			@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
			@ar -rc $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
