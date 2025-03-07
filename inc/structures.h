/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:47:23 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 15:22:58 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TYPES_H
# define SCENE_TYPES_H

# include "libft.h"

typedef enum e_obj_type
{
	CAMERA,
	A_LIGHT,
	S_LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	UNDEFINED
}	t_obj_type;

typedef struct s_tmp
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}			t_tmp;

typedef struct s_xpm
{
	int	*data;
	int	width;
	int	height;
}		t_xpm;

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
}			t_color;

typedef struct s_cam
{
	t_vec			coordinates;
	t_vec			orientation;
	unsigned int	fov;
}					t_cam;

typedef struct s_a_light
{
	double		ratio;
	t_color		color;
}			t_a_light;

typedef struct s_s_light
{
	t_vec		coordinates;
	double		ratio;
	t_color		color;
}				t_s_light;

typedef struct s_plane
{
	t_vec		coordinates;
	t_vec		normal_vector;
	t_color		color;
	t_xpm		*texture;
	t_xpm		*normal_map;
}				t_plane;

typedef struct s_sphere
{
	t_vec		coordinates;
	double		diameter;
	t_color		color;
}				t_sphere;

typedef struct s_cylinder
{
	t_vec		coordinates;
	t_vec		axis_vector;
	double		diameter;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct s_obj
{
	t_obj_type	type;
	void		*specific_obj;
}				t_obj;

typedef struct s_scene
{
	t_cam		*camera;
	t_a_light	*a_light;
	t_list		*light_lst;
	t_list		*obj_lst;
	unsigned int	c_count;
	unsigned int	a_count;
}				t_scene;

typedef struct s_ray
{
	t_vec 		origin;
	t_vec 		direction;
}				t_ray;

#endif
