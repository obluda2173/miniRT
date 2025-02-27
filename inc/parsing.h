/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:48:40 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 19:49:59 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "scene_types.h"  // Include shared types
# include "minirt.h"       // Include after shared types

// parsing_extracting_objects.c
size_t array_size(char **array);
t_color parse_color(char *str, t_data *data);
t_vec parse_vector(char *str, t_data *data);
void extract_objs(int fd, t_data *data);

// parsing_structure.c
t_obj_type get_obj_type(t_list *obj_lst);
t_a_light *parse_a_light(char **split_line, t_data *data);
t_s_light *parse_s_light(char **split_line, t_data *data);
t_cam *parse_camera(char **split_line, t_data *data);
t_plane *parse_plane(char **split_line, t_data *data);
t_sphere *parse_sphere(char **split_line, t_data *data);
t_cylinder *parse_cylinder(char **split_line, t_data *data);

#endif