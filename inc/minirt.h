/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:30:51 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 18:50:21 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include "libft.h"
# include "get_next_line.h"
# include "scene_types.h"

typedef struct s_data
{
	t_scene	*scene;
	char	*error;
}			t_data;

// data.c
void free_split(char **array);
void    free_data(t_data *data);
void free_and_exit(t_data *data, char *error_msg);

void parse_scene(char *filename, t_data *data);

#endif