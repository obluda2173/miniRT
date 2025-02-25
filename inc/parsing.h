/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:42:12 by erian             #+#    #+#             */
/*   Updated: 2025/02/25 17:40:20 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# include "minirt.h"

/* 
** attributes
*/
typedef enum e_obj_type
{
	A_LIGHT,	// ambient light 	A
	S_LIGHT,	// source light		L
	CAMERA,		// camera			C
	PLANE,		// plane			pl
	SPHERE,		// sphere			sp
	CYLINDER,	// Cylinder			cy
	UNDEFINED
}	t_obj_type;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}					t_color;

/* 
** objects
*/
typedef struct s_a_light
{
	double	ratio;
	t_color	color;
}			t_a_light;

typedef struct s_s_light
{
	t_vec	coordinates;
	double	ratio;
	t_color	color;
}			t_s_light;

typedef struct s_cam
{
	t_vec			coordinates;
	t_vec			orientation;
	unsigned int	fov;
}					t_cam;

typedef struct s_plane
{
	t_vec	coordinates;
	t_vec	normal_vector;
	t_color	color;
}			t_plane;

typedef struct s_sphere
{
	t_vec	coordinates;
	double	diameter;
	t_color	color;
}			t_sphere;

typedef struct s_cylinder
{
	t_vec	coordinates;
	t_vec	normal_vector;
	double	diameter;
	double	height;
	t_color	color;
}			t_cylinder;

typedef struct s_obj
{
	t_obj_type			type;
	void				*obj;
	struct s_obj		*next;
}						t_obj;

// parsing_extracting_objects.c
size_t array_size(char **array);
t_color parse_color(char *str, t_data *data);
t_vec parse_vector(char *str, t_data *data);
t_obj *extract_objs(int fd, t_data *data);

// parsing_structure.c
t_a_light *parse_a_light(char **split_line, t_data *data);
t_s_light *parse_s_light(char **split_line, t_data *data);
t_cam *parse_camera(char **split_line, t_data *data);
t_plane *parse_plane(char **split_line, t_data *data);
t_sphere *parse_sphere(char **split_line, t_data *data);
t_cylinder *parse_cylinder(char **split_line, t_data *data);

// parsing.c
void parse(char *file_name, t_data *data);

#endif