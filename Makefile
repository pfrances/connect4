# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:06:24 by pfrances          #+#    #+#              #
#    Updated: 2023/07/02 16:07:58 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = connect4
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -MMD -MP

SRCS_DIR = ./srcs
OBJS_DIR = ./objs
SRCS = $(addprefix $(SRCS_DIR)/,	connect4.c					\
									game_init.c					\
									game_loop.c					\
									game_loop_utils.c			\
									checker.c					\
									free_all.c					\
									ft_atoi_with_error_check.c)
OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

LIBS_DIR = ./libraries
LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = $(LIBS_DIR)/minilibx
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
INCLUDES = -I $(LIBFT_DIR) -I $(MLX_DIR) -I includes
DEFINE_VARS = -D $(ESC) -D $(W) -D $(A) -D $(S) -D $(D) -D $(FRAMERATE) -D $(ADJUST)

#--------------------------------------------------------------------------#

OS = $(shell uname -s)

ifeq ($(OS),Linux)
ESC = ESC=65307
W = W=119
A = A=97
S = S=115
D = D=100
FRAMERATE = FRAMERATE=1000
ADJUST = ADJUST=0
MLX = $(MLX_DIR)/libmlx.a
MLX_LIBS = -I $(MLX_DIR) -L $(MLX_DIR) -lmlx -lXext -lX11 $(MLX)

READLINE = -L/usr/lib/x86_64-linux-gnu -lreadline
INCLUDE += -I/usr/include/readline/
else
ESC = ESC=53
W = W=13
A = A=0
S = S=1
D = D=2
FRAMERATE = FRAMERATE=200
ADJUST = ADJUST=20
MLX = $(MLX_DIR)/libmlx_Darwin.a
INCLUDES += -I/usr/X11/include
MLX_LIBS = -L $(MLX_DIR) -L /usr/X11/include/../lib -lmlx_Darwin -lXext -lX11 -framework OpenGL -framework AppKit

READLINE = -L$(shell brew --prefix readline)/lib -lreadline
INCLUDE += -I$(shell brew --prefix readline)/include
endif
#--------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_LIBS) $(READLINE) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

$(MLX): $(MLX_DIR)/Makefile
	make -C $(MLX_DIR)

$(MLX_DIR)/Makefile:
	git clone $(MLX_REPO) $(MLX_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean
#	if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
#	rm -rf $(MLX_DIR)

re: fclean all

bonus: all

install:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

update:
	brew update && brew upgrade && brew install readline


.PHONY: all clean fclean re bonus install update

-include $(DEPS)