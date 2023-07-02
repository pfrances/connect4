/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 13:41:26 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 23:28:00 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

bool	set_xpm_img(void *mlx_ptr, t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path,
			&img->width, &img->height);
	if (img->img_ptr != NULL) {
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	}
	return (img->img_ptr != NULL);
}

bool	images_init(t_game *game)
{
	if (set_xpm_img(game->mlx_ptr, &game->user_stone_img, USER_STONE_PATH) == false)
		return false;
	if (set_xpm_img(game->mlx_ptr, &game->ai_stone_img, AI_STONE_PATH) == false) {
		mlx_destroy_image(game->mlx_ptr, game->user_stone_img.img_ptr);
		return false;
	}
	if (set_xpm_img(game->mlx_ptr, &game->empty_stone_img, EMPTY_STONE_PATH) == false) {
		mlx_destroy_image(game->mlx_ptr, game->user_stone_img.img_ptr);
		mlx_destroy_image(game->mlx_ptr, game->ai_stone_img.img_ptr);
		return false;
	}
	return true;
}

bool	init_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return false;
	game->win_width = game->columns * STONE_SIZE;
	game->win_height = game->lines * STONE_SIZE;
	if (game->win_width > 2048 || game->win_height > 2048) {
		free(game->mlx_ptr);
		ft_putstr_fd("Error: Board is too big to use graphic mode\n", 2);
		return false;
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->win_width, game->win_height, "Connect 4");
	if (game->win_ptr == NULL) {
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return false;
	}
	return true;
}

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

bool	ask_graphic_mode(void) {
	char	*line = NULL;

	while (1)
	{
		line = readline("Do you want to play in graphic mode? (y/n): ");
		if (line == NULL)
			return false;
		if (ft_strncmp(line, "y", ft_strlen(line)) == 0
			|| ft_strncmp(line, "yes", ft_strlen(line)) == 0) {
			free(line);
			return true;
		} else if (ft_strncmp(line, "n", ft_strlen(line)) == 0
			|| ft_strncmp(line, "no", ft_strlen(line) == 0)) {
			free(line);
			return false;
		} else {
			ft_putendl_fd("Error: invalid input", STDERR_FILENO);
			free(line);
		}
	}
}

bool	game_init(t_game *game) {

	if (game->lines < LINES_MIN || game->lines > LINES_MAX) {
		ft_putendl_fd("Error: invalid number of lines", STDERR_FILENO);
		return false;
	} else if (game->columns < COL_MIN || game->columns > COL_MAX) {
		ft_putendl_fd("Error: invalid number of columns", STDERR_FILENO);
		return false;
	}
	game->next_move = -1;
	game->turn = 0;
	game->is_over = false;
	game->winner = 0;
	game->user_start = rand() % 2;
	game->board = init_board(game->lines, game->columns);
	if (game->board == NULL)
		return false;

	game->graphic_mode = ask_graphic_mode();
	if (game->graphic_mode == false)
		return true;

	if (init_window(game) == false) {
		free_array(game->board);
		return false;
	}

	if (images_init(game) == false) {
		free_array(game->board);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		return false;
	}
	return true;
}
