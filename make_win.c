/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 20:03:48 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/07 20:07:02 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"

int main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 1024, "first_test");
	mlx_loop(mlx);
}
