/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:57:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/07/02 16:11:33 by pfrances         ###   ########.fr       */
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
	free_array(game->board);
}
