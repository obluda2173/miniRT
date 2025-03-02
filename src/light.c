/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:19 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 14:39:47 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

int color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
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
