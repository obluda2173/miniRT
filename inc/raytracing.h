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
}					t_cy_inter_type;

typedef struct s_cy_inter
{
	double			t;
	t_cy_inter_type	type;
}					t_cy_inter;

typedef struct s_quadratic_coeff
{
	double			a;
	double			b;
	double			c;
}					t_quadratic_coeff;

typedef struct s_cl
{
	double			t;
	t_vec			normal;
	t_obj			*obj;
}					t_cl;

bool				ray_sphere_intersect(t_ray ray, t_sphere *sphere,
						double *t);
bool				ray_plane_intersect(t_ray ray, t_plane *plane, double *t);
t_vec				calc_normal_cy(t_ray ray, t_cylinder *cy,
						t_cy_inter *cy_inter);
t_cl				find_closest_object(t_ray ray, t_list *orig_obj_lst);
bool				is_in_shadow(t_vec hit_point, t_s_light *light,
						t_scene *scene);

void				update_cl_plane(t_ray ray, t_cl *cl, t_obj *obj_node);
void				update_cl_sphere(t_ray ray, t_cl *cl, t_obj *obj_node);
void				update_cl_cone(t_ray ray, t_cl *cl, t_obj *obj_node);
void				update_cl_cyl(t_ray ray, t_cl *cl, t_obj *obj_node);

/* cylinder */
bool				check_pt_inside_bottom_cap(t_ray ray, t_cylinder cy,
						double t);
bool				check_pt_inside_top_cap(t_ray ray, t_cylinder cy, double t);
void				add_t_to_cy_candidates(t_list **candidates, double t,
						t_cy_inter_type type);
t_cy_inter			*find_smallest_cy_inter_t(t_list *candidates);
t_cy_inter			*ray_inter_cylinder(t_ray ray, t_cylinder cy);
bool				check_pt_inside_bottom_cap(t_ray ray, t_cylinder cy,
						double t);

/* cone */
bool				ray_inf_cone_intersect(t_ray ray, t_cone *cone, double *t);
#endif
