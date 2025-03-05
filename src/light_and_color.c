/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/05 16:29:14 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

int color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

t_color int_to_color(int integer)
{
	return ((t_color){(integer >> 16) & 0xFF, (integer >> 8) & 0xFF, integer & 0xFF});
}

t_color color_clamp(t_color c)
{
	return ((t_color){
		.r = fmax(0, fmin(c.r, 255)),
		.g = fmax(0, fmin(c.g, 255)),
		.b = fmax(0, fmin(c.b, 255))});
}

t_color color_add(t_color a, t_color b)
{
	return (color_clamp((t_color){
		.r = a.r + b.r,
		.g = a.g + b.g,
		.b = a.b + b.b}));
}

t_color color_scale(t_color c, double factor)
{
	return (color_clamp((t_color){
		.r = c.r * factor,
		.g = c.g * factor,
		.b = c.b * factor}));
}

int apply_ambient_light(t_color object_color, t_a_light *ambient)
{
	t_color	result;

	result = color_clamp((t_color){
		.r = (object_color.r + ambient->color.r) * ambient->ratio,
		.g = (object_color.g + ambient->color.g) * ambient->ratio,
		.b = (object_color.b + ambient->color.b) * ambient->ratio});

	return (color_to_int(result));
}

int apply_source_light(t_scene *scene, t_intersection *inter, int color)
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

	light_dir = normalize(sub(light->coordinates, inter->hit_point));
	diff = fmax(dot(inter->normal, light_dir), 0.0);
	diffuse = color_scale(inter->base_color, diff * light->ratio);

	// specular lighting (to be added later)
	t_vec view_dir = normalize(sub(camera->coordinates, inter->hit_point));
	t_vec reflect_dir = reflect(scale(light_dir, -1), inter->normal);
	double spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), SPECULAR_EXP);
	t_color specular = color_scale(light->color, spec * light->ratio);

	return (color_add(diffuse, specular));
}
