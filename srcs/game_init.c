/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:41:26 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:48:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

char **init_board(int lines, int columns) {
	char	**board = (char **)malloc(sizeof(char *) * (lines + 1));
	if (board == NULL)
		return NULL;

	for (int i = 0; i < lines; i++) {
		board[i] = (char *)malloc(sizeof(char) * (columns + 1));
		if (board[i] == NULL) {
			free_array(board);
			return NULL;
		}

		for (int j = 0; j < columns; j++) {
			board[i][j] = EMPTY;
		}
		board[i][columns] = '\0';
	}
	board[lines] = NULL;
	return board;
}

bool	game_init(t_game *game) {

	if (game->lines < LINES_MIN || game->lines > LINES_MAX) {
		ft_putendl_fd("Error: invalid number of lines", STDERR_FILENO);
		return false;
	} else if (game->columns < COL_MIN || game->columns > COL_MAX) {
		ft_putendl_fd("Error: invalid number of columns", STDERR_FILENO);
		return false;
	}

	game->turn = 0;
	game->is_over = false;
	game->winner = 0;
	game->board = init_board(game->lines, game->columns);
	if (game->board == NULL)
		return false;
	return true;
}
