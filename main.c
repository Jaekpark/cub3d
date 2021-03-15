/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:57:39 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/03/15 21:54:47 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h>

#define WIDTH 100
#define HEIGHT 100
#define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

typedef struct s_img
{
	void *img;
	int *data;

	int size_l;
	int bpp;
	int endian;
} t_img;

int main(void)
{
	double posX = 22;
	double posY = 12;
	double dirX = -1;
	double dirY = 0;
	double planeX = 0;
	double planeY = 0.66;
	void *mlx;
	void *win;
	t_img img;


	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "mlx");
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		printf("roof cnt %d <cameraX = %f>\n", x, cameraX);
		printf("roof cnt %d <rayDirX = %f>\n", x, rayDirX);
		printf("roof cnt %d <rayDirY = %f>\n", x, rayDirY);
	}
	return (0);
}
