/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:03:59 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 20:26:35 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	get_amt_words_2(int words, char **s)
{
	if (**s && !is_charset(**s, "\t <>|"))
	{
		while (**s && !is_charset(**s, "\t <>|"))
			++*s;
		++words;
	}
	else if (**s == ' ' || **s == '\t')
		while (**s && (**s == ' ' || **s == '\t'))
			++*s;
	return (words);
}

int	get_amt_wd_1(char *s, int words, char c)
{
	while (s && *s)
	{
		if (*s == '\'' || *s == '"')
		{
			c = *s;
			++s;
			while (*s && !is_charset(*s, "\t ") && (*s != c
					|| (*s == c && s + 1 && !is_charset(*(s + 1), " \t"))))
				++s;
			if (*s && *s == c)
				++s;
			++words;
		}
		else if (*s == '<' || *s == '>' || *s == '|')
		{
			c = *s;
			while (*s && *s == c)
				++s;
			++words;
		}
		else
			words = get_amt_words_2(words, &s);
	}
	return (words);
}

static char	*get_word_2(char *s, int *index, int start)
{
	char	*ret;
	char	c;
	int		size;

	size = 0;
	if (s[*index] == '>' || s[*index] == '<' || s[*index] == '|')
	{
		c = s[*index];
		while (s[*index] && s[*index] == c)
		{
			++*index;
			++size;
		}
		ret = ft_strdupncpy(&s[start], size, 0);
	}
	else if (!is_charset(s[*index], " \t<>|"))
	{
		while (s[*index] && !is_charset(s[*index], " \t<>|"))
		{
			++*index;
			++size;
		}
		ret = ft_strdupncpy(&s[start], size, "\'\"");
	}
	return (ret);
}

char	*get_word_1(char *s, int *index, char c)
{
	char	*ret;
	int		start;
	int		size;

	while (s[*index] && is_charset(s[*index], "\t ") == 1)
		++*index;
	start = *index;
	size = 0;
	if (s[*index] == '\'' || s[*index] == '"')
	{
		c = s[*index];
		++*index;
		while (s[*index] && !is_charset(s[*index], " \t")
			&& (s[*index] != c || (s[*index] == c && s[*index + 1]
					&& !is_charset(s[*index + 1], " \t"))))
		{
			++*index;
			++size;
		}
		++*index;
		ret = ft_strdupncpy(&s[start + 1], size, &c);
		return (ret);
	}
	ret = get_word_2(s, index, start);
	return (ret);
}

char	**str_to_tab_1(char *s)
{
	char	**tab;
	int		i;
	int		j;

	if (!s || !get_amt_wd_1(s, 0, 0))
		return (0);
	if (!ft_calloc((void **)&tab, sizeof(char *) * (get_amt_wd_1(s, 0, 0) + 1)))
		return ((char **)free_items((void **)&s, 1, 0, 0));
	i = 0;
	j = -1;
	while (s[i])
	{
		g_shell->ops[++j] = get_ops(&s[i]);
		tab[j] = get_word_1(s, &i, 0);
		if (!tab[j])
		{
			free_tab(tab, j);
			return ((char **)free_items((void **)&s, 1, 0, 0));
		}
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			++i;
	}
	if (s)
		free(s);
	return (tab);
}
