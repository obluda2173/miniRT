/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:38:21 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 14:41:28 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include <math.h>

# include "data.h"

int color_to_int(t_color color);
int	apply_ambient_light(t_color object_color, t_a_light *ambient);

#endif