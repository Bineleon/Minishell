/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/10 16:21:31 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection(t_data *data)
{
	int	row;

	row = 0;
	while (tab[row])
		free(tab[row++]);
	free(tab);
}
char	**jointab(char **tab, char *str)
{
	int		i;
	char	**newtab;

	i = 0;
	while (tab[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 1));
	if (!newtab)
		return (NULL);
	newtab[0] = ft_strdup(str);
	if (!newtab[0])
		return (free(newtab), NULL);
	i = 0;
	while (tab[i])
	{
		newtab[i + 1] = ft_strdup(tab[i]);
		if (!newtab[i + 1])
			return (freetab(newtab), NULL);
		i++;
	}
	return (newtab);
}
