/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:14:32 by erian             #+#    #+#             */
/*   Updated: 2025/02/28 11:41:27 by erian            ###   ########.fr       */
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



void free_scene(t_scene *scene)
{
    if (!scene)
        return;
    
    if (scene->camera)
    {
        free(scene->camera);
    }
    if (scene->a_light)
    {
        free(scene->a_light);
    }
    
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
