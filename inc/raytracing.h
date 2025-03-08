/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:29 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 10:22:37 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "structures.h"

typedef enum e_cy_inter_type
{
	TOP_CAP,
	BOTTOM_CAP,
	SURFACE,
}	t_cy_inter_type;

typedef struct s_cy_inter
{
	double			t;
	t_cy_inter_type	type;
}					t_cy_inter;

bool		ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t);
bool		ray_plane_intersect(t_ray ray, t_plane *plane, double *t);
t_vec		calc_normal_cy(t_ray ray, t_cylinder *cy, t_cy_inter *cy_inter);
t_cy_inter	*ray_inter_cylinder(t_ray ray, t_cylinder cy);
bool ray_inf_cone_intersect(t_ray ray, t_cone cone, double *t);
t_obj		*find_closest_object(t_ray ray, t_list *orig_obj_lst,
				double *closest_t, t_vec *closest_normal);
bool		is_in_shadow(t_vec hit_point, t_s_light *light, t_scene *scene);

#endif
