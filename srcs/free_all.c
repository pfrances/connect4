/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:57:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 23:27:46 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "connect4.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_all(t_game *game)
{
	if (game->graphic_mode) {
		mlx_destroy_image(game->mlx_ptr, game->ai_stone_img.img_ptr);
		mlx_destroy_image(game->mlx_ptr, game->user_stone_img.img_ptr);
		mlx_destroy_image(game->mlx_ptr, game->empty_stone_img.img_ptr);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free_array(game->board);
}
