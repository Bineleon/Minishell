
#include "../../includes/minishell.h"

void sub_find_cmds(t_bool *is_file, t_bool *is_cmd, t_fullcmd *current)
{
    if (is_redi(current))
        *is_file = true;
    else if (*is_file)
    {
        *is_file = false;
        current->is_cmd = false;
    }
    else if ((current->type == WORD) && *is_cmd == false)
    {
        current->is_cmd = true;
        *is_cmd = true;
    }
    else
        current->is_cmd = *is_cmd;
}

void find_cmds(t_data *data)
{
    t_fullcmd *current;
    t_bool is_cmd;
    t_bool is_file;

    current = data->token_fullcmd;
    is_file = false;
    is_cmd = false;
    while (current)
    {
        is_cmd = false;
        while (current && current->type != PIPE)
        {
            sub_find_cmds(&is_file, &is_cmd, current);
            current = current->next;
        }
        if (current && current->type == PIPE)
        {
            current->is_cmd = false;
            current = current->next;
        }
    }
}

// void find_cmds(t_data *data)
// {
//     t_fullcmd *current = data->token_fullcmd;
//     t_bool is_file_context = false; // Indique si on attend un fichier après une redirection

//     while (current)
//     {
//         // Réinitialiser pour chaque pipeline
//         t_bool command_found = false;

//         while (current && current->type != PIPE)
//         {
//             // Si c'est une redirection, le token suivant est un fichier/opérande
//             if (current->type == IN || current->type == OUT ||
//                 current->type == APPEND || current->type == HEREDOC)
//             {
//                 is_file_context = true;
//             }
//             else if (is_file_context)
//             {
//                 // Ce token est un fichier, pas une commande
//                 is_file_context = false;
//                 current->is_cmd = false;
//             }
//             else if ((current->type == WORD || current->type == EXPAND) && !command_found)
//             {
//                 // Le premier mot valide après les redirections est la commande
//                 current->is_cmd = true;
//                 command_found = true; // Marquer qu'on a trouvé une commande
//             }
//             else
//             {
//                 // Tout autre mot valide après une commande est un argument
//                 current->is_cmd = command_found; // True si une commande a été trouvée
//             }

//             current = current->next; // Passer au token suivant
//         }

//         // Si on atteint un pipe, ignorer ce token
//         if (current && current->type == PIPE)
//         {
//             current->is_cmd = false;
//             current = current->next; // Passer au token suivant après le pipe
//         }
//     }
// }
