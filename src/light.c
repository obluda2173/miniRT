/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/03 11:55:03 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

int color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

t_color int_to_color(int integer)
{
	return (t_color){(integer >> 16) & 0xFF, (integer >> 8) & 0xFF, integer & 0xFF};
}

t_color color_add(t_color a, t_color b)
{
	return (t_color){
		.r = fmin(a.r + b.r, 255),
		.g = fmin(a.g + b.g, 255),
		.b = fmin(a.b + b.b, 255)
	};
}

t_color color_scale(t_color c, double factor)
{
	return (t_color){
		.r = fmin(c.r * factor, 255),
		.g = fmin(c.g * factor, 255),
		.b = fmin(c.b * factor, 255)
	};
}

t_color color_clamp(t_color c)
{
	return (t_color){
		.r = fmax(0, fmin(c.r, 255)),
		.g = fmax(0, fmin(c.g, 255)),
		.b = fmax(0, fmin(c.b, 255))
	};
}

int	apply_ambient_light(t_color object_color, t_a_light *ambient)
{
	int r = (int)(object_color.r * ambient->ratio + ambient->color.r * ambient->ratio);
	int g = (int)(object_color.g * ambient->ratio + ambient->color.g * ambient->ratio);
	int b = (int)(object_color.b * ambient->ratio + ambient->color.b * ambient->ratio);

	r = fmin(255, r);
	g = fmin(255, g);
	b = fmin(255, b);

	return color_to_int((t_color){r, g, b});
}

int	apply_light_source(t_color object_color, t_s_light *light, t_vec hit_point, t_vec normal)
{
	t_vec	light_dir = normalize(sub(light->coordinates, hit_point));
	double	intensity = fmax(dot(normal, light_dir), 0.0) * light->ratio;

	int r = fmin(255, (int)(object_color.r * intensity + light->color.r * light->ratio));
	int g = fmin(255, (int)(object_color.g * intensity + light->color.g * light->ratio));
	int b = fmin(255, (int)(object_color.b * intensity + light->color.b * light->ratio));

	return color_to_int((t_color){r, g, b});
}

t_color calculate_light(t_s_light *light, t_vec hit_point, t_vec normal, t_color obj_color)
{
	t_vec light_dir = normalize(sub(light->coordinates, hit_point));
	double intensity = light->ratio;

	// diffuse lighting
	double diff = fmax(dot(normal, light_dir), 0.0);
	t_color diffuse = color_scale(obj_color, diff * intensity);

	// specular lighting 
	// t_vec view_dir = normalize(sub(camera->position, hit_point));
	// t_vec reflect_dir = reflect(scale(light_dir, -1), normal);
	// double spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), SHININESS);
	// t_color specular = color_scale(light->color, spec * intensity);

	return diffuse; // add specular later
}
