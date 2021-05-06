/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:18:59 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/21 17:15:16 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_update(t_game *game)
{
	if (game->key.w || game->key.s)
		mv_forward_back(game, game->cub->map_buffer);
	if (game->key.q || game->key.e)
		rot_right_left(game);
	if (game->key.a || game->key.d)
		mv_right_left(game, game->cub->map_buffer);
}

int		key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit_game(game);
	else if (key == KEY_W || key == KEY_UP)
		game->key.w = 1;
	else if (key == KEY_S || key == KEY_DOWN)
		game->key.s = 1;
	else if (key == KEY_A)
		game->key.a = 1;
	else if (key == KEY_D)
		game->key.d = 1;
	else if (key == KEY_Q || key == KEY_LEFT)
		game->key.q = 1;
	else if (key == KEY_E || key == KEY_RIGHT)
		game->key.e = 1;
	return (0);
}

int		key_release(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit_game(game);
	else if (key == KEY_W || key == KEY_UP)
		game->key.w = 0;
	else if (key == KEY_S || key == KEY_DOWN)
		game->key.s = 0;
	else if (key == KEY_A)
		game->key.a = 0;
	else if (key == KEY_D)
		game->key.d = 0;
	else if (key == KEY_Q || key == KEY_LEFT)
		game->key.q = 0;
	else if (key == KEY_E || key == KEY_RIGHT)
		game->key.e = 0;
	return (0);
}
