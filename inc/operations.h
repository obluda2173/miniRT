/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:06:21 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 11:23:46 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "structures.h"

t_vec	vec(double x, double y, double z);
t_vec	add(t_vec v1, t_vec v2);
t_vec	sub(t_vec v1, t_vec v2);
double	dot(t_vec v1, t_vec v2);

double	length(t_vec v);
t_vec	normalize(t_vec v);


#endif