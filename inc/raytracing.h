/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:29 by erian             #+#    #+#             */
/*   Updated: 2025/03/04 16:16:07 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

bool	ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t);
bool    ray_plane_intersect(t_ray ray, t_plane *plane, double *t);
t_obj	*find_closest_object(t_ray ray, t_list *orig_obj_lst, double *closest_t, t_vec *closest_normal);
bool	is_in_shadow(t_vec hit_point, t_s_light *light, t_scene *scene);

#endif