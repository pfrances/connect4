/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:02:43 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 22:36:19 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_4_HPP
# define CONNECT_4_HPP

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <stdbool.h>

# define LINES_MIN 6
# define LINES_MAX 1024
# define COL_MIN 7
# define COL_MAX 1024

# define USER_STONE 'o'
# define AI_STONE 'x'
# define EMPTY '.'

# define USER_STONE_PATH "./xpm_files/red.xpm"
# define AI_STONE_PATH "./xpm_files/yellow.xpm"
# define EMPTY_STONE_PATH "./xpm_files/empty.xpm"

# define STONE_SIZE 50

# define USER_WIN 1
# define AI_WIN 2
# define DRAW 3

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
	char	*path;
	int		width;
	int		height;
}	t_img;

typedef struct s_game {
	size_t		lines;
	size_t		columns;
	char		**board;
	int			turn;
	bool		is_over;
	int			winner;
	void		*mlx_ptr;
	void		*win_ptr;
	int			next_move;
	size_t		win_width;
	size_t		win_height;
	t_img		user_stone_img;
	t_img		ai_stone_img;
	t_img		empty_stone_img;
	bool		graphic_mode;
	bool		user_start;
}	t_game;


int		ft_atoi_with_error_check(const char *nptr, bool *error_flag);
void	free_array(char **array);
void	free_all(t_game *game);

bool	game_init(t_game *game);
void	terminal_mode(t_game *game);
void	graphic_mode(t_game *game);
void	check_board(t_game *game, int stone);
void	print_board(t_game *game);
void	put_stone(t_game *game, int col, char stone);

int		get_user_input(t_game *game);
void	print_ending_message(t_game *game);

#endif
