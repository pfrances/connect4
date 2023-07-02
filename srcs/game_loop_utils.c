/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:18:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:26:12 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "connect4.h"

void	print_board(t_game *game)
{
	int	i;

	ft_putstr_fd("\n\t  ", STDOUT_FILENO);
	for (i = 0; i < game->columns; i++) {
		ft_putnbr_fd(i, STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);

	i = 0;
	while (game->board[i] != NULL)
	{
		ft_putstr_fd("\t| ", STDOUT_FILENO);
		ft_putstr_fd(game->board[i], STDOUT_FILENO);
		ft_putendl_fd(" |", STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("\t", STDOUT_FILENO);
	for (i = 0; i < game->columns + 4; i++)
		ft_putchar_fd('-', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_ending_message(t_game *game)
{
	if (game->is_over == true)
	{
		if (game->winner == USER_WIN)
			ft_putendl_fd("You win!", STDOUT_FILENO);
		else if (game->winner == AI_WIN)
			ft_putendl_fd("You lose...", STDOUT_FILENO);
		else
			ft_putendl_fd("Draw.", STDOUT_FILENO);
	}
}

int	get_user_input(t_game *game) {
	int	columns;
	bool	error_check;
	char	*input = NULL;

	while (true)
	{
		error_check = true;
		input = readline("Please enter a column number: ");
		columns = ft_atoi_with_error_check(input, &error_check);
		free(input);
		if (error_check) {
			ft_putendl_fd("Invalid column number.", STDOUT_FILENO);
			continue ;
		}
		if (columns < 0 || columns >= game->columns)
			ft_putendl_fd("Invalid column number.", STDOUT_FILENO);
		else if (game->board[0][columns] != '.')
			ft_putendl_fd("This column is full.", STDOUT_FILENO);
		else
			break ;
	}
	return (columns);
}