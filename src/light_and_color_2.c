/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_color_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 11:09:25 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

int	apply_ambient_light(t_color object_color, t_a_light *ambient)
{
	t_color	result;

	result = color_clamp((t_color){
			(object_color.r + ambient->color.r) * ambient->ratio,
			(object_color.g + ambient->color.g) * ambient->ratio,
			(object_color.b + ambient->color.b) * ambient->ratio});
	return (color_to_int(result));
}

int	apply_source_light(t_scene *scene, t_intersection *inter, int color)
{
	t_list		*light_lst;
	t_s_light	*light;
	t_color		light_contrib;

	light_lst = scene->light_lst;
	while (light_lst)
	{
		light = (t_s_light *)light_lst->content;
		if (!is_in_shadow(inter->hit_point, light, scene))
		{
			light_contrib = calculate_light(light, inter, scene->camera);
			color = color_to_int(color_add(int_to_color(color), light_contrib));
		}
		light_lst = light_lst->next;
	}
	return (color);
}

t_color	calculate_light(t_s_light *light, t_intersection *inter, t_cam *camera)
{
	t_vec	light_dir;
	double	diff;
	t_color	diffuse;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	t_color	specular;

	light_dir = normalize(sub(light->coordinates, inter->hit_point));
	diff = fmax(dot(inter->normal, light_dir), 0.0);
	diffuse = color_scale(inter->base_color, diff * light->ratio);

	view_dir = normalize(sub(camera->coordinates, inter->hit_point));
	reflect_dir = reflect(scale(light_dir, -1), inter->normal);
	spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), SPECULAR_EXP);
	specular = color_scale(light->color, spec * light->ratio);

	return (color_add(diffuse, specular));
}
