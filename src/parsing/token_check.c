
#include "../../includes/minishell.h"

int is_separator(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '$' || c == ' ');
}

t_token get_token_type(char c)
{
	if (c == '|')
		return PIPE;
	if (c == '<')
		return IN;
	if (c == '>')
		return OUT;
  if (c == ' ')
		return SPC;
	if (c == '$')
		return EXPAND;
	return WORD;
}
