/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:20:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 23:37:08 by kitsuki          ###   ########.fr       */
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

void	print_turn(t_game *game, int rand_num)
{
	if (game->turn % 2 == rand_num)
		ft_putendl_fd("	Player's turn:", STDOUT_FILENO);
	else
		ft_putendl_fd("	AI's turn:", STDOUT_FILENO);
}

void	game_loop(t_game *game)
{
	int	rand_num = rand() % 2;

	while (true)
	{
		print_turn(game, rand_num);
		print_board(game);
		if (game->turn % 2 == rand_num)
			put_stone(game, get_user_input(game), USER_STONE);
		else
			computer_turn(game);
		if (game->is_over == true)
			break ;
		game->turn++;
	}
	print_ending_message(game);
}
