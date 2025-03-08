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

t_vec	scale(t_vec v, double scalar)
{
	return (vec(v.x * scalar, v.y * scalar, v.z * scalar));
}

double	length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	discr(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	root_n(double a, double b, double c)
{
	return ((-b - sqrt(discr(a, b, c))) / (2 * a));
}

double	root_p(double a, double b, double c)
{
	return ((-b + sqrt(discr(a, b, c))) / (2 * a));
}
