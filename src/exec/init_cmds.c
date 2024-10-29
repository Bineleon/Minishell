/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:41 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/29 23:50:09 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void new_cmd(t_data *data, t_fullcmd *fullcmd)
// {
//     int i;
//     int arg_count;
//     t_fullcmd *tmp;

//     i = 0;
//     arg_count = 0;
//     tmp = fullcmd;
//     // A refactoriser
//     while (tmp && tmp->type != PIPE && tmp->type != IN && tmp->type != OUT)
//     {
//         arg_count++;
//         tmp = tmp->next;
//     }
//     data->cmds->args = gc_mem(MALLOC, sizeof(char *) * (arg_count + 1), NULL);
//     data->cmds->str = gc_mem(MALLOC, sizeof(char *) * (arg_count + 1), NULL);
//     tmp = fullcmd;
//     data->cmds->cmd = gc_strdup(tmp->str);
//     while (tmp && tmp->type != PIPE && tmp->type != IN && tmp->type != OUT)
//     {
//         printf("i = %d\n", i);
//         data->cmds->args[i] = gc_strdup(tmp->str);
//         data->cmds->str[i] = gc_strdup(tmp->str);
//         i++;
//         tmp = tmp->next;
//     }
//     data->cmds->args[i] = NULL;
//     data->cmds->str[i] = NULL;
// }

void new_cmd(t_cmd *cmds, t_fullcmd *fullcmd)
{
    int i;
    int arg_count;
    t_fullcmd *tmp;

    i = 0;
    arg_count = 0;
    tmp = fullcmd;
    // A refactoriser
    while (tmp && tmp->type != PIPE && tmp->type != IN && tmp->type != OUT)
    {
        arg_count++;
        tmp = tmp->next;
    }
    cmds->args = gc_mem(MALLOC, sizeof(char *) * (arg_count + 1), NULL);
    cmds->str = gc_mem(MALLOC, sizeof(char *) * (arg_count + 1), NULL);
    tmp = fullcmd;
    cmds->cmd = gc_strdup(tmp->str);
    while (tmp && tmp->type != PIPE && tmp->type != IN && tmp->type != OUT)
    {
        if (i == 0)
        {
			cmds->cmd = gc_strdup(fullcmd->str);
            // printf("\n\ncmds->cmd = %s\n\n", cmds->cmd);
        }
        // printf("i = %d\n", i);
        cmds->args[i] = gc_strdup(tmp->str);
        cmds->str[i] = gc_strdup(tmp->str);
        i++;
        tmp = tmp->next;
    }
    cmds->args[i] = NULL;
    cmds->str[i] = NULL;
}


// void init_cmds(t_data *data)
// {
//     t_cmd *tmp;

//     data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
//     init_cmd(data->cmds);
//     tmp = data->cmds;

//     while (data->token_fullcmd)
//     {
//         new_cmd(data, data->token_fullcmd); // il faut que la fonction change data->cmds->cmd puis son next la ca change le meme

//         while (data->token_fullcmd && data->token_fullcmd->type != PIPE)
//             data->token_fullcmd = data->token_fullcmd->next;
//         if (data->token_fullcmd && data->token_fullcmd->type == PIPE)
//         {
//             data->token_fullcmd = data->token_fullcmd->next;
//             tmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
//             tmp->next->prev = tmp;
//             tmp = tmp->next;
//             init_cmd(tmp);
//         }
// 	      // printf("\n\nICI\n\n");
//     }
// }

void init_cmds(t_data *data)
{
    t_cmd *tmp;

    data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
    init_cmd(data->cmds);
    tmp = data->cmds;

    // printf("dans la boucle init cmd\n");
    while (data->token_fullcmd)
    {
        // printf("avant cmds 0 = %s\n", data->cmds->cmd);
        new_cmd(tmp, data->token_fullcmd); // ON ENVOIE TMP SINON CA MODIFIE QUE DATA ET PAS DATA NEXT
        // printf("apres cmds 0 = %s\n", data->cmds->cmd);
        while (data->token_fullcmd && data->token_fullcmd->type != PIPE)
            data->token_fullcmd = data->token_fullcmd->next;
        if (data->token_fullcmd && data->token_fullcmd->type == PIPE)
        {
            data->token_fullcmd = data->token_fullcmd->next;
            tmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
            tmp->next->prev = tmp;
            tmp = tmp->next;
        }
    }
}


// void	new_cmd(t_data *data, t_fullcmd *fullcmd)
// {
// 	int		i;
//   t_fullcmd *tmp;

//   tmp = fullcmd;

// 	i = 0;
//       data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
//       init_cmd(data->cmds);
// 	while (fullcmd->str && fullcmd->type != PIPE && fullcmd->type != IN
// 		&& fullcmd->type != OUT)
// 	{
// 		  printf("\n\nstr: %s\n", fullcmd->str);
// 		// if (i == 0)
//     // {
// 			data->cmds->cmd = gc_strdup(fullcmd->str);
//       // data->cmds->cmd = gc_mem(MALLOC, ft_strlen(fullcmd->str) + 1, NULL);
//       // ft_strlcpy(data->cmds->cmd, fullcmd->str, ft_strlen(fullcmd->str) + 1);
//        printf("\n\ndata->cmds->cmd = %s\n\n", data->cmds->cmd);

//     // }
//     data->cmds->args = gc_mem(MALLOC, sizeof(char *) + 1, NULL);
// 		data->cmds->args[i] = gc_strdup(fullcmd->str);
//     data->cmds->str = gc_mem(MALLOC, sizeof(char *) + 1, NULL);
// 		data->cmds->str[i] = gc_strdup(fullcmd->str);
// 		i++;
// 		fullcmd = fullcmd->next;
//     printf("\n\nICI\n\n");
// 	}

//     data->cmds->args[i] = NULL;
//     data->cmds->str[i] = NULL;
// 	while (fullcmd->str && fullcmd->type != PIPE)
// 	{
//     printf("\n\nICI\n\n");
// 		data->cmds->str[i] = gc_strdup(fullcmd->str);
// 		i++;
// 		fullcmd = fullcmd->next;
// 	}
// }

// void	init_cmds(t_data *data)
// {
// 	// int	i;

// 	// i = 0;
// 	// data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 	// init_cmd(data->cmds);
// 	new_cmd(data, data->token_fullcmd);
//   printf("\n\nICI\n\n");
// 	while (data->token_fullcmd->str)
// 	{
// 		while(data->cmds)
// 		{
// 			data->cmds->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 			data->cmds->next->prev = data->cmds;
// 			data->cmds = data->cmds->next;
// 		}
// 		init_cmd(data->cmds);
// 		new_cmd(data, data->token_fullcmd);
// 		while (data->token_fullcmd && data->token_fullcmd->type != PIPE)
// 			data->token_fullcmd = data->token_fullcmd->next;
// 		if (data->token_fullcmd && data->token_fullcmd->type == PIPE)
// 			data->token_fullcmd = data->token_fullcmd->next;
// 		data->token_fullcmd = data->token_fullcmd->next;
// 	}
// }
