/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:47:21 by erian             #+#    #+#             */
/*   Updated: 2024/12/29 12:49:21 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dllstdelone(t_dllist *lst, void (*del)(void *))
{
	if (lst)
		(*del)(lst->content);
	free(lst);
}
