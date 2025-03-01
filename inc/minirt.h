/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:30:51 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 09:32:23 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

# include "data.h"
# include "libft.h"
# include "parsing.h"
# include "scene_types.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 720

// Initialization
void free_data(t_data *data);
void free_and_exit(t_data *data, char *error_msg);

#endif