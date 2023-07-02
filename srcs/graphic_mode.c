/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:29:48 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 23:33:25 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

void	put_image(t_game *game, size_t x, size_t y, t_img *img)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img->img_ptr, x * STONE_SIZE, y * STONE_SIZE);
}

void	play_one_turn(t_game *game) {
	put_stone(game, game->next_move, USER_STONE);
	if (game->is_over == true)
		return ;
	int computer_move = rand() % game->columns;
	while (game->board[0][computer_move] != EMPTY) {
		computer_move = rand() % game->columns;
	}
	put_stone(game, computer_move, AI_STONE);
	game->turn++;
	game->next_move = -1;
}

static int	cross_button_event(t_game *game)
{
	free_all(game);
	exit(0);
}

static int	deal_key(int key, t_game *game)
{
	if (key == XK_Escape)
	{
		free_all(game);
		exit(0);
	}
	return (0);
}

static int	mouse_hook(int button, int mouse_x, int mouse_y, void *ptr)
{
	t_game	*game;

	(void)mouse_y;
	(void)button;
	game = (t_game *)ptr;
	if (game->is_over == true || mouse_x / STONE_SIZE >= (int)game->columns)
		return (0);
	game->next_move = mouse_x / STONE_SIZE;
	return (0);
}

static int	render_map(t_game *game)
{
	size_t	x;
	size_t	y;
	t_img *img;

	if (game->win_ptr == NULL)
		return (1);

	if (game->next_move >= 0) {
		play_one_turn(game);
	}
	y = 0;
	while (y < game->lines && game->is_over == false)
	{
		x = 0;
		while (x < game->columns && game->is_over == false)
		{

			if (game->board[y][x] == USER_STONE) {
				img = &game->user_stone_img;
			} else if (game->board[y][x] == AI_STONE) {
				img = &game->ai_stone_img;
			} else {
				img = &game->empty_stone_img;
			}
			put_image(game, x, y, img);
			x++;
		}
		y++;
	}
	return (0);
}

void	graphic_mode(t_game *game)
{
	mlx_hook(game->win_ptr, ClientMessage, StructureNotifyMask,
		&cross_button_event, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &deal_key, game);
	mlx_hook(game->win_ptr, ButtonPress, ButtonPressMask, &mouse_hook, game);
	mlx_loop_hook(game->mlx_ptr, &render_map, game);
	mlx_loop(game->mlx_ptr);
}
