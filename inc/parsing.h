/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:48:40 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 14:55:47 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# include "data.h"
# include "utils.h"
# include "structures.h"
# include "get_next_line.h"

// General Parsing
void parse_scene(char *filename, t_data *data);

// Parsing Helpers
size_t		array_size(char **array);
t_color		parse_color(char *str, t_data *data);
t_vec		parse_vector(char *str, t_data *data);

// Object Extraction
void		extract_objs(int fd, t_data *data);
t_obj_type	get_obj_type(t_list *obj_lst);
void		*get_specific_obj(t_list *obj_lst, t_obj_type type);

// Object Parsing
t_a_light	*parse_a_light(char **split_line, t_data *data);
t_obj	*parse_s_light(char **split_line, t_data *data);
t_cam		*parse_camera(char **split_line, t_data *data);
t_obj       *parse_plane(char **split_line, t_data *data);
t_obj       *parse_sphere(char **split_line, t_data *data);
t_obj       *parse_cylinder(char **split_line, t_data *data);

#endif