/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:04:17 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 16:15:31 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_lstsize(t_list *map)
{
	t_node	*temp;
	int		size;

	temp = map->head;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
