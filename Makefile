# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 14:16:54 by sgadinga          #+#    #+#              #
#    Updated: 2025/04/03 13:59:55 by sgadinga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BNS_NAME = checker
CC = cc
CFLAGS = -Wall -Werror -Wextra -Ilibft/includes -Iincludes

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(addprefix $(SRC_DIR)/, \
		 main.c node_ops.c map_ops.c rotations.c \
		 stack_init.c stack_valid.c stack_utils.c stack_ops.c\
		 ps_init.c ps_algo.c ps_utils.c mini_sort.c \
		 normalize.c other_utils.c debug.c \
		 action_ops.c action_optim.c \
		 trial_params.c)
BNS = $(addprefix $(SRC_DIR)/, \
		checker.c node_ops.c map_ops.c rotations.c \
		stack_init.c stack_valid.c stack_ops.c stack_utils.c\
		ps_init.c debug.c other_utils.c normalize.c \
		action_ops.c action_optim.c) 

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BOBJS = $(BNS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libft $(NAME)

bonus: libft $(BNS_NAME)

libft:
	@make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft


$(BNS_NAME): $(BOBJS)
	$(CC) $(CFLAGS) -o $(BNS_NAME) $(BOBJS) -Llibft -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re libft