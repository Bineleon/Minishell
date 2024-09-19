/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:21:59 by neleon            #+#    #+#             */
/*   Updated: 2024/09/19 20:30:42 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	free_malloc(char **split, int size)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (i < size)
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = NULL;
	}
}

static char	*ft_word(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((ft_word_len(s, c) + 1) * sizeof(char));
	if (!word)
		return (free(word), NULL);
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		word_count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	words = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!words)
		return (free_malloc(words, i), NULL);
	while (j < word_count)
	{
		while (s[i] == c)
			i++;
		words[j] = ft_word(&s[i], c);
		if (!words[j])
			free_malloc(words, j);
		i += ft_word_len(&s[i], c);
		j++;
	}
	words[word_count] = NULL;
	return (words);
}