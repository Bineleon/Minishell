

#include "../../includes/minishell.h"


void	skip_var_name(char *line, int *i)
{
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'
			|| line[*i] == '?'))
		*i += 1;
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*extract_var(char *line, int *i, int start)
{
	char	*tmp;

	if (!line[*i] || !is_valid_var_char(line[*i]))
		tmp = gc_strdup("$");
	else
	{
		skip_var_name(line, i);
		tmp = gc_mem(MALLOC, *i - start + 1, NULL);
		ft_strlcpy(tmp, line + start, *i - start + 1);
	}
	return (tmp);
}

