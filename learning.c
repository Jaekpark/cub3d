/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:09:12 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/03/10 13:24:30 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include <stdlib.h>
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_ESC 53

typedef struct s_player
{
	int x;
	int y;
	int color;
}	t_player;

typedef struct s_window
{
	void *mlx;
	void *win;
	t_player player;

	int width;
	int height;

	int row_cnt;
	int col_cnt;
	int grid_color;
}	t_window;

int draw_grid(t_window *window)
{
	int draw_pos;
	int i;

	i = 1;
	while (i < window->row_cnt)
	{
		draw_pos = 0;
		while (draw_pos <= window->width)
		{
			mlx_pixel_put(window->mlx, window->win, draw_pos, i * (window->height / window->row_cnt), window->grid_color);
			draw_pos++;
		}
		i++;
	}
	i = 1;
	while (i < window->col_cnt)
	{
		draw_pos = 0;
		while (draw_pos <= window->width)
		{
			mlx_pixel_put(window->mlx, window->win, i * (window->width / window->col_cnt), draw_pos, window->grid_color);
			draw_pos++;
		}
		i++;
	}
	return (0);
}

void init_player(t_window *window)
{
	mlx_pixel_put(window->mlx, window->win, window->player.x, window->player.y, window->player.color);
}

void move_left(t_window *window)
{
	int old_x = window->player.x;
	int old_y = window->player.y;
	int black = 0x000000;
	
	if ((0 < window->player.x && window->player.x <= window->width) && (0 < window->player.y && window->player.y <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x, old_y, black);
		mlx_pixel_put(window->mlx, window->win, --window->player.x, window->player.y, window->player.color);
	}
}

void move_right(t_window *window)
{
	int old_x = window->player.x;
	int old_y = window->player.y;
	int black = 0x000000;
	
	if ((0 < window->player.x && window->player.x <= window->width) && (0 < window->player.y && window->player.y <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x, old_y, black);
		mlx_pixel_put(window->mlx, window->win, ++window->player.x, window->player.y, window->player.color);
	}
}

void move_up(t_window *window)
{
	int old_x = window->player.x;
	int old_y = window->player.y;
	int black = 0x000000;
	
	if ((0 < window->player.x && window->player.x <= window->width) && (0 < window->player.y && window->player.y <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x, old_y, black);
		mlx_pixel_put(window->mlx, window->win, window->player.x, --window->player.y, window->player.color);
	}
}

void move_down(t_window *window)
{
	int old_x = window->player.x;
	int old_y = window->player.y;
	int black = 0x000000;
	
	if ((0 < window->player.x && window->player.x <= window->width) && (0 < window->player.y && window->player.y <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x, old_y, black);
		mlx_pixel_put(window->mlx, window->win, window->player.x, ++window->player.y, window->player.color);
	}
}

int press_key(int key, t_window *window)
{
	if (key == K_W)
		move_up(window);
	else if (key == K_S)
		move_down(window);
	else if (key == K_A)
		move_left(window);
	else if (key == K_D)
		move_right(window);
	else if (key == K_ESC)
		exit(0);
	return (0);
}

int main(void)
{
	t_window window;

	window.width = 500;
	window.height = 500;
	window.row_cnt = 10;
	window.col_cnt = 10;
	window.grid_color = 0x00FFFF;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, "mlx_grid");

	window.player.color = 0xFF0000;
	window.player.x = 220;
	window.player.y = 220;
	init_player(&window);
	mlx_loop_hook(window.mlx, draw_grid, &window);
	mlx_hook(window.win, 2, 1, press_key, &window);
	mlx_loop(window.mlx);
}
