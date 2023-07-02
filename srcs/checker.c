/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:02:29 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:28:03 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "connect4.h"

static void	check_horizontal(t_game *game, int stone)
{
	int	i;
	int	j;
	int	count;

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
	int	i;
	int	j;
	int	count;

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
	int	i;
	int	j;
	int	count;

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
	check_horizontal(game, stone);
	check_vertical(game, stone);
	check_diagonal(game, stone);
	
	if (game->is_over == true) {
		if (stone == USER_STONE)
			game->winner = USER_WIN;
		else
			game->winner = AI_WIN;
	}
}
