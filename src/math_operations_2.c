/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operations_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:05:53 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 11:26:22 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include "raytracing.h"

t_vec	scale(t_vec v, double scalar)
{
	return (vec(v.x * scalar, v.y * scalar, v.z * scalar));
}

double	length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	discr(t_quadratic_coeff coeff)
{
	return (coeff.b * coeff.b - 4 * coeff.a * coeff.c);
}

double	root_n(t_quadratic_coeff coeff)
{
	return ((-coeff.b - sqrt(discr(coeff))) / (2 * coeff.a));
}

double	root_p(t_quadratic_coeff coeff)
{
	return ((-coeff.b + sqrt(discr(coeff))) / (2 * coeff.a));
}
