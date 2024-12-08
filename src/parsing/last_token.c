
#include "../../includes/minishell.h"

void  find_redi(t_data *data)
{
    t_fullcmd *token;
    t_fullcmd *prev;

    token = data->token_fullcmd;
    prev = NULL;
    while(token)
    {
        if (token )
        prev = token;
        token = token->next;
    }
}
