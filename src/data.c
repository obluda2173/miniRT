/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:14:32 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 18:57:02 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_split(char **array)
{
    size_t i = 0;

    if (!array)
        return ;
    while (array[i])
        free(array[i++]);
    free(array);
    array = NULL;
}

// void	free_obj_list(t_list *obj_lst)
// {
// 	t_list	*tmp_lst;

// 	while (obj_lst)
// 	{
// 		tmp = obj_lst;
// 		if (obj_lst->obj)
// 		{
// 			if (obj_lst->type == A_LIGHT)
// 				free((t_a_light *)obj_lst->obj);
// 			else if (obj_lst->type == S_LIGHT)
// 				free((t_s_light *)obj_lst->obj);
// 			else if (obj_lst->type == CAMERA)
// 				free((t_cam *)obj_lst->obj);
// 			else if (obj_lst->type == PLANE)
// 				free((t_plane *)obj_lst->obj);
// 			else if (obj_lst->type == SPHERE)
// 				free((t_sphere *)obj_lst->obj);
// 			else if (obj_lst->type == CYLINDER)
// 				free((t_cylinder *)obj_lst->obj);
// 		}
// 		obj_lst = obj_lst->next;
// 		free(tmp);
// 	}
// }

void free_scene(t_scene *scene)
{
    if (!scene)
        return;
    
    if (scene->camera)
        free(scene->camera);
    if (scene->a_light)
        free(scene->a_light);
    
	ft_lstclear(&scene->light_lst, free);
	ft_lstclear(&scene->obj_lst, free);

    free(scene);
}

void free_data(t_data *data)
{
    if (!data)
        return;

    if (data->scene)
        free_scene(data->scene);
    
    free(data);
}

void free_and_exit(t_data *data, char *error_msg)
{
    if (error_msg)
        ft_putstr_fd(error_msg, STDERR_FILENO);
    free_data(data);
    exit(EXIT_FAILURE);
}
