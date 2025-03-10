/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:14:32 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 13:27:00 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_split(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

void	free_specific_object(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->type == SPHERE)
		free((t_sphere *)obj->specific_obj);
	else if (obj->type == PLANE)
	{
		if (((t_plane *)obj->specific_obj)->texture
			&& ((t_plane *)obj->specific_obj)->normal_map)
		{
			free(((t_plane *)obj->specific_obj)->texture->data);
			free(((t_plane *)obj->specific_obj)->normal_map->data);
			free(((t_plane *)obj->specific_obj)->texture);
			free(((t_plane *)obj->specific_obj)->normal_map);
		}
		free((t_plane *)obj->specific_obj);
	}
	else if (obj->type == CYLINDER)
		free((t_cylinder *)obj->specific_obj);
	else if (obj->type == CONE)
		free((t_cone *)obj->specific_obj);
	free(obj);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->camera)
		free(scene->camera);
	if (scene->a_light)
		free(scene->a_light);
	ft_lstclear(&scene->light_lst, free);
	ft_lstclear(&scene->obj_lst, (void (*)(void *))free_specific_object);
	free(scene);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->scene)
		free_scene(data->scene);
	if (data->mlx)
	{
		if (data->mlx->win)
			mlx_destroy_window(data->mlx->mlx, data->mlx->win);
		if (data->mlx->mlx)
		{
			mlx_destroy_display(data->mlx->mlx);
			free(data->mlx->mlx);
		}
		free(data->mlx);
	}
}

void	free_and_exit(t_data *data, char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	free_data(data);
	exit(EXIT_FAILURE);
}
