/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:06:21 by erian             #+#    #+#             */
/*   Updated: 2025/03/05 16:12:30 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include <math.h>

# include "structures.h"

# define M_PI    3.14159265358979323846
# define EPSILON 1e-6

t_vec	vec(double x, double y, double z);
t_vec	add(t_vec v1, t_vec v2);
t_vec	sub(t_vec v1, t_vec v2);
t_vec	cross(t_vec v1, t_vec v2);
t_vec	scale(t_vec v, double scalar);
double	dot(t_vec v1, t_vec v2);

double	length(t_vec v);
double	discr(double a, double b, double c);
double	root_n(double a, double b, double c);
double	root_p(double a, double b, double c);
t_vec	normalize(t_vec v);
t_vec	reflect(t_vec v, t_vec normal);


#endif