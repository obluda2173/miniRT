/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:30:09 by erian             #+#    #+#             */
/*   Updated: 2025/03/05 13:06:15 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	power_of_ten(int exp)
{
	double result = 1.0;
	while (exp-- > 0)
		result *= 10.0;
	return result;
}

double  ft_atod(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		divisor;

	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0.0;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
		str++;
	fraction = 0.0;
	divisor = 0;
	while (ft_isdigit(*str))
	{
		fraction = fraction * 10.0 + (*str++ - '0');
		divisor++;
	}
	result += fraction / power_of_ten(divisor);
	return (sign * result);
}
