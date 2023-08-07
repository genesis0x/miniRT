# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahadiou <hahadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 17:11:01 by hahadiou          #+#    #+#              #
#    Updated: 2023/08/07 17:03:34 by hahadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
FLAGS	=   -IINC -fsanitize=address -g -Wunreachable-code -Ofast
LIBMLX = MLX42/build/libmlx42.a
NAME	= miniRT

INC	= inc
SRC_PATH	= src
UTILS_PATH	= utils
OBJ_PATH	= obj

SRCS = parsing.c \
		#parser_core.c \
		parser_get_data.c \
		parser_get_elem.c \
		parser_get_wall.c \
		parser_utils.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strlen.c \
		ft_strtrim.c \
		ft_substr.c \
		get_next_line.c \
		ft_split.c \
		ft_lstadd_back.c \
		ft_lstlast.c \
		ft_lstnew.c 

SRC		= $(addprefix $(SRC_PATH)/,$(SRCS))
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

NOC		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
WHITE	= \033[1;37m

all: $(NAME)

bonus: $(NAMEB)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling Utils...$(NOC)"
	@echo "$(YELLOW)Compiling miniRT...$(NOC)"
	@$(CC) $(FLAGS) $(LIBMLX) -Iinclude -lglfw -L"/Users/hahadiou/goinfre/homebrew/opt/glfw/lib" src/libft.a -o $@ $^
	@echo "$(GREEN)$@$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)/minirt.h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INC) -c -o $@ $<

run:
	make re && ./miniRT
clean:
	@echo "$(RED)Deleting OBJS ✔️ $(NOC)"
	@make clean -sC $(UTILS_PATH)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)Deleting Binary ✔️$(NOC)"
	@make fclean -sC $(UTILS_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY:	all bonus clean fclean re

