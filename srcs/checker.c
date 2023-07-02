/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:02:29 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 23:32:42 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "connect4.h"

static void	check_horizontal(t_game *game, int stone)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	while (i < game->lines)
	{
		j = 0;
		count = 0;
		while (j < game->columns)
		{
			if (game->board[i][j] == stone)
				count++;
			else
				count = 0;
			if (count == 4)
				game->is_over = true;
			j++;
		}
		i++;
	}
}

static void	check_vertical(t_game *game, int stone)
{
	size_t	i;
	size_t	j;
	size_t	count;

	j = 0;
	while (j < game->columns)
	{
		i = 0;
		count = 0;
		while (i < game->lines)
		{
			if (game->board[i][j] == stone)
				count++;
			else
				count = 0;
			if (count == 4)
				game->is_over = true;
			i++;
		}
		j++;
	}
}

static void	check_diagonal(t_game *game, int stone) {
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	while (i < game->lines)
	{
		j = 0;
		while (j < game->columns)
		{
			if (game->board[i][j] == stone)
			{
				count = 1;
				while (i + count < game->lines && j + count < game->columns)
				{
					if (game->board[i + count][j + count] == stone)
						count++;
					else
						break ;
				}
				if (count == 4)
					game->is_over = true;
			}
			j++;
		}
		i++;
	}
}

void	check_board(t_game *game, int stone)
{
	if (game->is_over == true)
		return ;
	check_horizontal(game, stone);
	check_vertical(game, stone);
	check_diagonal(game, stone);

	if ((size_t)game->turn == game->lines * game->columns) {
		game->is_over = true;
		game->winner = DRAW;
		print_board(game);
		print_ending_message(game);
		exit(0);
	}
	else if (game->is_over == true) {
		if (stone == USER_STONE)
			game->winner = USER_WIN;
		else
			game->winner = AI_WIN;
		print_board(game);
		print_ending_message(game);
		exit(0);
	}
}
