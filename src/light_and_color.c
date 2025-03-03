/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_and_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/03 14:44:10 by erian            ###   ########.fr       */
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
	return color_clamp((t_color){
		.r = a.r + b.r,
		.g = a.g + b.g,
		.b = a.b + b.b});
}

t_color color_scale(t_color c, double factor)
{
	return color_clamp((t_color){
		.r = c.r * factor,
		.g = c.g * factor,
		.b = c.b * factor});
}

int apply_ambient_light(t_color object_color, t_a_light *ambient)
{
	t_color result = color_clamp((t_color){
		.r = (object_color.r + ambient->color.r) * ambient->ratio,
		.g = (object_color.g + ambient->color.g) * ambient->ratio,
		.b = (object_color.b + ambient->color.b) * ambient->ratio});

	return color_to_int(result);
}

t_color calculate_light(t_s_light *light, t_vec hit_point, t_vec normal, t_color obj_color)
{
	t_vec light_dir = normalize(sub(light->coordinates, hit_point));
	double intensity = light->ratio;

	// diffuse lighting
	double diff = fmax(dot(normal, light_dir), 0.0);
	t_color diffuse = color_scale(obj_color, diff * intensity);

	// specular lighting (to be added later)
	// t_vec view_dir = normalize(sub(camera->position, hit_point));
	// t_vec reflect_dir = reflect(scale(light_dir, -1), normal);
	// double spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), SHININESS);
	// t_color specular = color_scale(light->color, spec * intensity);

	return diffuse; // add specular later
}
