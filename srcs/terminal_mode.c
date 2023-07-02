/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:20:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 22:06:53 by pfrances         ###   ########.fr       */
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

void	print_turn(t_game *game)
{
	if (game->turn % 2 == game->user_start)
		ft_putendl_fd("	Player's turn:", STDOUT_FILENO);
	else
		ft_putendl_fd("	AI's turn:", STDOUT_FILENO);
}

void	computer_turn(t_game *game) {
	put_stone(game, get_user_input(game), AI_STONE);
}

void	terminal_mode(t_game *game)
{
	while (true)
	{
		print_turn(game);
		print_board(game);
		if (game->turn % 2 == game->user_start)
			put_stone(game, get_user_input(game), USER_STONE);
		else
			computer_turn(game);
		if (game->is_over == true)
			break ;
		game->turn++;
	}
	print_ending_message(game);
}
