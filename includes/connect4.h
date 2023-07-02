/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:02:43 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:51:49 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT_4_HPP
# define CONNECT_4_HPP

# include "libft.h"
# include "mlx.h"
# include <readline/readline.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <stdbool.h>

# define LINES_MIN 6
# define LINES_MAX 10
# define COL_MIN 7
# define COL_MAX 12

# define USER_STONE 'o'
# define AI_STONE 'x'
# define EMPTY '.'

# define USER_WIN 1
# define AI_WIN 2
# define DRAW 3

typedef struct s_game {
	int		lines;
	int		columns;
	char	**board;
	int		turn;
	bool	is_over;
	int		winner;
} t_game;

int		ft_atoi_with_error_check(const char *nptr, bool *error_flag);
void	free_array(char **array);
void	free_all(t_game *game);

bool	game_init(t_game *game);
void	game_loop(t_game *game);
void	check_board(t_game *game, int stone);
void	print_board(t_game *game);

int		get_user_input(t_game *game);
void	print_ending_message(t_game *game);

#endif
