/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operations_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:53 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 11:26:19 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

t_vec	normalize(t_vec v)
{
	double	len;

	len = length(v);
	if (len == 0)
		return (vec(0, 0, 0));
	return (vec(v.x / len, v.y / len, v.z / len));
}

t_vec	reflect(t_vec v, t_vec normal)
{
	double	dot_product;

	dot_product = dot(v, normal);
	return ((t_vec){
		.x = v.x - 2 * dot_product * normal.x,
		.y = v.y - 2 * dot_product * normal.y,
		.z = v.z - 2 * dot_product * normal.z});
}
