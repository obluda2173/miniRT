/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 15:07:57 by erian            ###   ########.fr       */
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
	// Compute light direction
	t_vec	light_dir = normalize(sub(light->coordinates, hit_point));
	double	intensity = fmax(dot(normal, light_dir), 0.0) * light->ratio;

	// Apply lighting
	int r = fmin(255, (int)(object_color.r * intensity + light->color.r * light->ratio));
	int g = fmin(255, (int)(object_color.g * intensity + light->color.g * light->ratio));
	int b = fmin(255, (int)(object_color.b * intensity + light->color.b * light->ratio));

	return color_to_int((t_color){r, g, b});
}
