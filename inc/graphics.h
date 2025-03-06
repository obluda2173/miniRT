/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:36:23 by erian             #+#    #+#             */
/*   Updated: 2025/03/06 18:37:37 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <mlx.h>

# include "data.h"
# include "utils.h"
# include "light.h"

# define ESC		65307
# define WIN_WIDTH	1024
# define WIN_HEIGHT	720

void	init_window(t_data *data);
void	close_window(t_data *data);	
void	render_scene(t_data *data);

#endif