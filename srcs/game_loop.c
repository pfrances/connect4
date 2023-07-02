/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:20:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:30:17 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "connect4.h"

void	put_stone(t_game *game, int col, char stone) {
	int	i;

	i = game->lines - 1;
	while (i >= 0)
	{
		if (game->board[i][col] == '.')
		{
			game->board[i][col] = stone;
			break ;
		}
		i--;
	}
	check_board(game, stone);
}

void	game_loop(t_game *game)
{
	int	turn;

	turn = 0;
	while (true)
	{
		print_board(game);
		if (turn % 2 == 0)
			put_stone(game, get_user_input(game), USER_STONE);
		else
			put_stone(game, ge_user_input(gtame), AI_STONE);
			// computer_turn(game);
		if (game->is_over == true)
			break ;
		turn++;
	}
	print_ending_message(game);
}
