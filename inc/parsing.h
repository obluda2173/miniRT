/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:48:40 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 14:11:26 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>


# include "data.h"
# include "utils.h"
# include "structures.h"
# include "get_next_line.h"
# include "operations.h"

// General Parsing
void parse_scene(char *filename, t_data *data);

// Parsing Helpers
size_t		array_size(char **array);
t_color		parse_color(char *str, t_data *data);
t_vec		parse_vector(char *str, t_data *data);

// Object Extraction
void		extract_objs(int fd, t_data *data);

// Object Parsing
t_a_light	*parse_a_light(char **split_line, t_data *data);
t_s_light	*parse_s_light(char **split_line, t_data *data);
t_cam		*parse_camera(char **split_line, t_data *data);
t_obj		*parse_plane(char **split_line, t_data *data);
t_obj		*parse_sphere(char **split_line, t_data *data);
t_obj		*parse_cylinder(char **split_line, t_data *data);
t_obj	*parse_cone(char **split_line, t_data *data);

// Parsing Robust Check
bool		a_check(char **array, t_data *data);
bool		c_check(char **array, t_data *data);
bool		l_check(char **array, t_data *data);
bool		sp_check(char **array, t_data *data);
bool		pl_check(char **array, t_data *data);
bool		cy_check(char **array, t_data *data);
bool	co_check(char **array, t_data *data);

#endif
