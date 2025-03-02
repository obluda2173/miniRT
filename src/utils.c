/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:14:32 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 15:23:24 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_split(char **array)
{
	size_t i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

void free_specific_object(t_obj *obj)
{
	if (!obj)
		return;
	if (obj->type == SPHERE)
		free((t_sphere *)obj->specific_obj);
	else if (obj->type == PLANE)
		free((t_plane *)obj->specific_obj);
	else if (obj->type == CYLINDER)
		free((t_cylinder *)obj->specific_obj);
	else if (obj->type == S_LIGHT)
		free((t_s_light *)obj->specific_obj);
	free(obj);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return;
	if (scene->camera)
		free(scene->camera);
	if (scene->a_light)
		free(scene->a_light);
	ft_lstclear(&scene->light_lst, (void (*)(void *))free_specific_object);
	ft_lstclear(&scene->obj_lst, (void (*)(void *))free_specific_object);
	free(scene);
}

void	free_data(t_data *data)
{
	if (!data)
		return;
	if (data->scene)
		free_scene(data->scene);
	if (data->mlx)
		free(data->mlx);
}

void	free_and_exit(t_data *data, char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	free_data(data);
	exit(EXIT_FAILURE);
}
