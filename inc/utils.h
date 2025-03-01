/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:24:07 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 09:24:38 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "data.h"

void	free_split(char **array);
void	free_data(t_data *data);
void	free_and_exit(t_data *data, char *error_msg);

#endif