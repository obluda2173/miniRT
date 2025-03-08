/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:30:09 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 10:46:04 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_negativ(const char *nbr)
{
	while (nbr && *nbr && ft_isspace(*nbr))
		nbr++;
	if (*nbr == '-')
		return (1);
	return (0);
}

double	ft_atod(const char *nbr)
{
	double	res;
	int		i;
	int		j;
	int		sign;

	j = 1;
	sign = 1;
	if (!nbr)
		return (0);
	res = ft_atoi(nbr);
	if (is_negativ(nbr))
		sign = -1;
	while (*nbr && *nbr != '.')
		nbr++;
	if (*nbr == '.')
		nbr++;
	i = ft_strlen(nbr);
	while (i-- > 0)
		j *= 10;
	res += (double)ft_atoi(nbr) * sign / j;
	return (res);
}
