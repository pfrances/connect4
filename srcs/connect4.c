/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:05:49 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:49:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

void	usage(char *prgm_name) {
	ft_putendl_fd("This programe take 2 arguments.", STDERR_FILENO);
	ft_putstr_fd("Please launch it like this: '", STDERR_FILENO);
	if (prgm_name != NULL)
		ft_putstr_fd(prgm_name, STDERR_FILENO);
	else
		ft_putstr_fd("connect4", STDERR_FILENO);
	ft_putendl_fd(" [number of lines] [number of columns]'.", STDERR_FILENO);
}

int	main(int argc, char *argv[]) {
	t_game	game;
	srand(time(NULL));

	if (argc != 3) {
		usage(argv[0]);
		return 1;
	}

	bool error_flag = true;
	game.lines = ft_atoi_with_error_check(argv[1], &error_flag);
	game.columns = ft_atoi_with_error_check(argv[2], &error_flag);
	if (error_flag == true) {
		ft_putendl_fd("Invalid input.", STDERR_FILENO);
		return 2;
	}

	if (game_init(&game) == false) {
		ft_putendl_fd("game initialisation failed.", STDERR_FILENO);
		return 3;
	}

	game_loop(&game);
	free_all(&game);
	return 0;
}
