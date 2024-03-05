# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lauger <lauger@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 11:01:31 by marvin            #+#    #+#              #
#    Updated: 2024/03/05 12:18:07 by lauger           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex
NAME_BONUS = ./pipex_bonus

LIBFT = ./libft
LIBFT_LIBRARY = $(LIBFT)/libft.a

CC = /bin/cc
CFLAGS = -g -Wextra -Werror -Wall -I $(LIBFT)
LDFLAGS = -L $(LIBFT) -lft

SRC = ./src/main.c ./src/utils.c ./src/execute.c ./src/execute_here_doc.c \
./src/pars_here_doc.c ./src/parsing.c ./src/commands_free.c

SRC_BONUS = ./src_bonus/main_bonus.c ./src_bonus/utils_bonus.c ./src_bonus/execute_bonus.c ./src_bonus/execute_here_doc_bonus.c \
./src_bonus/pars_here_doc_bonus.c ./src_bonus/parsing_bonus.c ./src_bonus/commands_free_bonus.c

OBJ_DIR = ./obj
OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:./src_bonus/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT_LIBRARY):
	/bin/make --quiet -C $(LIBFT)

$(NAME): $(LIBFT_LIBRARY) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(NAME_BONUS): $(LIBFT_LIBRARY) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LDFLAGS) -o $(NAME_BONUS)

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

$(OBJ_DIR)/%.o: ./src_bonus/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus : $(NAME_BONUS)

clean:
	/bin/make --quiet -C $(LIBFT) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/make --quiet -C $(LIBFT) fclean
	/bin/rm -f $(NAME_BONUS) $(NAME)

re: fclean all

.PHONY: all clean fclean re gdb gdb_bonus
