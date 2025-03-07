/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:38:21 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 14:02:49 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include	"data.h"
# include	"operations.h"
# include	"raytracing.h"

# define SPECULAR_EXP 21

typedef struct s_intersection
{
	t_vec	hit_point;
	t_vec	normal;
	t_color	base_color;
}			t_intersection;

int		color_to_int(t_color color);
t_color	int_to_color(int integer);
t_color	color_add(t_color a, t_color b);
t_color	color_scale(t_color c, double factor);
t_color	color_clamp(t_color c);
int		apply_ambient_light(t_color object_color, t_a_light *ambient);
int		apply_source_light(t_scene *scene, t_intersection *inter, int color);
t_color	calculate_light(t_s_light *light, t_intersection *inter, t_cam *camera);

void	compute_plane_uv(t_vec hit_point, t_plane *plane, double *u, double *v);
t_color	sample_xpm(t_xpm *xpm, double u, double v);
t_vec	sample_normal_map(t_xpm *normal_map, double u, double v);

#endif