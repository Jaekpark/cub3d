/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:04:28 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/18 20:15:08 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# define MAP_EXTENSION ".cub"
# define SAVE_OPT "--save"
# define FILE_PATH "./maps/"
# define VALID_CHAR " 012NSEW"

# define NO_ARGUMENT 0
# define WRONG_FILENAME 1
# define TOO_MANY_ARGUMENT 2
# define WRONG_OPTION 3
# define PARSING_ERROR 4
# define OPEN_ERROR 5

# define NO_TEX 100
# define SO_TEX 101
# define EA_TEX 102
# define WE_TEX 103
# define SP_TEX 104
# define FL_TEX 105
# define CE_TEX 106
# define FL_COLOR 107
# define CE_COLOR 108
# define RESOLUTION 109
# define EMPTY_LINE 110
# define MAP_LINE 111

typedef struct s_str
{
	char *content;
	struct s_str *next;
}	t_str;

typedef struct	s_cub
{
	int			save_opt;
	int			width;
	int			height;
	int			floor_color;
	int			ceilling_color;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_s;
	char		*path_ft;
	char		*path_ct;
	t_str		*head_map;
	int			col;
	int			row;
}				t_cub;

#endif
