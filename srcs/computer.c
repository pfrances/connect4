/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:32:50 by kitsuki           #+#    #+#             */
/*   Updated: 2023/07/02 23:39:43 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include <limits.h>

static int  count_scores(t_game *game, int line, int col)
{
    int score;
    int i;

    score = 0;

    for (i = 1; line - i >= 0; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line - i][col] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (line - i < 0)
        score += (i - 1) * 2;

    for (i = 1; line + i < game->lines; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line + i][col] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (line + i >= game->lines)
        score += (i - 1) * 2;

    for (i = 1; col - i >= 0; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line][col - i] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (col - i < 0)
        score += (i - 1) * 2;

    for (i = 1; col + i < game->columns; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line][col + i] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (col + i >= game->columns)
        score += (i - 1) * 2;

    for (i = 1; line - i >= 0 && col - i >= 0; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line - i][col - i] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (line - i < 0 || col - i < 0)
        score += (i - 1) * 2;

    for (i = 1; line + i < game->lines && col + i < game->columns; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line + i][col + i] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (line + i >= game->lines || col + i >= game->columns)
        score += (i - 1) * 2;

    for (i = 1; line + i < game->lines && col - i >= 0; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line + i][col - i] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (line + i >= game->lines || col - i < 0)
        score += (i - 1) * 2;

    for (i = 1; line - i >= 0 && col + i < game->columns; i++)
    {
        if (i > 3)
            return (INT_MAX);
        if (game->board[line - i][col + i] == AI_STONE)
            continue ;
        score += (i - 1) * 2;
        break ;
    }
    if (line - i < 0 || col + i >= game->columns)
        score += (i - 1) * 2;
    return (score);
}

static void try_put(int *score, int *column, t_game *game, int now)
{
    int i;
    int tmp;

    i = game->lines - 1;
	for (; i >= 0; i--)
	{
		if (game->board[i][now] != EMPTY)
            continue ;
		game->board[i][now] = AI_STONE;
		break ;
	}
    if (i < 0)
        return ;
    tmp = count_scores(game, i, now);
    if (tmp > *score)
    {
        *score = tmp;
        *column = now;
    }
    game->board[i][now] = EMPTY;
}

void    computer_turn(t_game *game)
{
    int score;
    int column;

    score = INT_MIN;
    column = 0;
    if (game->turn == 0)
    {
        put_stone(game, game->columns / 2, AI_STONE);
        return ;
    }
    for (int i = 0; i < game->columns; i++)
        try_put(&score, &column, game, i);
    put_stone(game, column, AI_STONE);
}
