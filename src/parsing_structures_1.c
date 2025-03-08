/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structures_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:25:00 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 13:10:41 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_xpm	*parse_xpm(char *filedir, t_data *data)
{
	t_xpm	*xpm;
	t_tmp	tmp;
	void	*img_ptr;
	int		total_pixels;
	int		i;

	xpm = malloc(sizeof(t_xpm));
	img_ptr = mlx_xpm_file_to_image(data->mlx->mlx, filedir,
			&xpm->width, &xpm->height);
	if (!img_ptr)
		free_and_exit(data, "Error: Failed to load xpm file\n");
	tmp.data = mlx_get_data_addr(img_ptr, &tmp.bpp,
			&tmp.size_line, &tmp.endian);
	if (!tmp.data)
		free_and_exit(data, "Error: Failed to get image data\n");
	total_pixels = xpm->width * xpm->height;
	xpm->data = malloc(sizeof(int) * total_pixels);
	if (!xpm->data)
		free_and_exit(data, "Error: Memory allocation failed for xpm data\n");
	i = -1;
	while (++i < total_pixels)
		xpm->data[i] = ((int *)tmp.data)[i];
	mlx_destroy_image(data->mlx->mlx, img_ptr);
	return (xpm);
}

t_cam	*parse_camera(char **split_line, t_data *data)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		free_and_exit(data, "Error: Memory allocation failed for camera\n");
	cam->coordinates = parse_vector(split_line[1], data);
	cam->orientation = parse_vector(split_line[2], data);
	cam->fov = ft_atoi(split_line[3]);
	if (cam->orientation.x < -1 || cam->orientation.x > 1
		|| cam->orientation.y < -1 || cam->orientation.y > 1
		|| cam->orientation.z < -1 || cam->orientation.z > 1)
		data->error = "Error: Invalid orientation vector range\n";
	if (cam->fov < EPSILON || cam->fov > 180)
		data->error = "Error: Invalid fov range\n";
	return (cam);
}

t_a_light	*parse_a_light(char **split_line, t_data *data)
{
	t_a_light	*a_light;

	a_light = malloc(sizeof(t_a_light));
	if (!a_light)
		free_and_exit(data, "Error: Memory allocation \
				failed for ambient light\n");
	a_light->ratio = ft_atod(split_line[1]);
	a_light->color = parse_color(split_line[2], data);
	if (a_light->ratio < 0 || a_light->ratio > 1)
		data->error = "Error: Invalid ambient light ratio range\n";
	return (a_light);
}

t_s_light	*parse_s_light(char **split_line, t_data *data)
{
	t_s_light	*s_light;

	s_light = malloc(sizeof(t_s_light));
	if (!s_light)
		free_and_exit(data, "Error: Memory allocation failed \
				for source light\n");
	s_light->coordinates = parse_vector(split_line[1], data);
	s_light->ratio = ft_atod(split_line[2]);
	s_light->color = parse_color(split_line[3], data);
	if (s_light->ratio < 0 || s_light->ratio > 1)
		data->error = "Error: Invalid source light ratio range\n";
	return (s_light);
}
