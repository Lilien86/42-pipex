# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lauger <lauger@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 11:01:31 by marvin            #+#    #+#              #
#    Updated: 2024/03/01 14:31:09 by lauger           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./pipex

NAME_BONUS = ./pipex_bonus

LIBFT = ./libft
LIBFT_LIBRARY = $(LIBFT)/libft.a

CC = /bin/cc
CFLAGS = -I $(LIBFT)
LDFLAGS = -L $(LIBFT) -lft

SRC = ./src/main.c ./src/utils.c ./src/execute.c ./src/execute_here_doc.c \
./src/pars_here_doc.c ./src/parsing.c ./src/commands_free.c

SRC_BONUS = ./src_bonus/main.c ./src_bonus/utils.c ./src_bonus/execute.c ./src_bonus/execute_here_doc.c \
./src_bonus/pars_here_doc.c ./src_bonus/parsing.c ./src_bonus/commands_free.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(LIBFT_LIBRARY):
	/bin/make --quiet -C $(LIBFT)

$(NAME): $(LIBFT_LIBRARY) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(NAME_BONUS): $(LIBFT_LIBRARY) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LDFLAGS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT) -c $< -o $@

bonus : $(NAME_BONUS)

clean:
	/bin/make --quiet -C $(LIBFT) clean
	/bin/rm -f $(OBJ_BONUS)
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/make --quiet -C $(LIBFT) fclean
	/bin/rm -f $(NAME_BONUS) $(OBJ_BONUS)
	/bin/rm -f $(NAME) $(OBJ)

re: fclean all

gdb: CFLAGS += -g
gdb: fclean all

gdb_bonus: CFLAGS += -g
gdb_bonus: fclean bonus

.PHONY: all clean fclean re gdb gdb_bonus
