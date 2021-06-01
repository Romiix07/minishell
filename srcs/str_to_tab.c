/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:40:39 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/31 12:29:17 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

int	is_charset(char c, const char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

char	*free_tab(char **tab, int limit)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i] && (i < limit || limit == -1))
			free(tab[i]);
		free(tab);
	}
	tab = 0;
	return (0);
}

static int	get_amt_words(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_charset(s[i], " \t\n"))
			++i;
		if (s[i] == '"')
		{
			++count;
			++i;
			while (s[i] && s[i] != '"')
				++i;
			if (s[i] == '"')
				++i;
		}
		else if (s[i] == '\'')
		{
			++count;
			++i;
			while (s[i] && s[i] != '\'')
				++i;
			if (s[i] == '\'')
				++i;
		}
		else if (is_charset(s[i], "$<>;|="))
		{
			++count;
			++i;
			if (!ft_strncmp(&s[i - 1], ">>", 2))
				++i;
			else if (s[i - 1] == '$')
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
					++i;
		}
		else if (s[i] && !is_charset(s[i], " \n\t;$<>|&'\"="))
		{
			++count;
			while (s[i] && !is_charset(s[i], " \n\t;$<>|&'\"="))
				++i;
		}
	}
	return (count);
}

static char	*get_word(char *s, int *i)
{
	char	*ret;
	int		j;

	j = -1;
	ret = 0;
	while (s[*i] && is_charset(s[*i], " \t\n"))
		++*i;
	if ((s[*i] == '"' || s[*i] == '\'') && !get_quote(&ret, s, i, s[*i]))
		return (0);
	else if (!ret && s[*i] == '$' && !get_dollar(&ret, s, i))
		return (0);
	else if (!ret && is_charset(s[*i], ";="))
	{
		if (!ft_calloc((void **)&ret, sizeof(char) * 2))
			return (0);
		ret[0] = s[(*i)++];
	}
	else if (!ret && is_charset(s[*i], "<>&|")
		&& !get_same_char(&ret, s, i, s[*i]))
		return (0);
	else if (!ret && s[*i] && !is_charset(s[*i], " \n\t;$<>|&'\"="))
		if (!get_classic_word(&ret, s, i, " \n\t;$<>|&'\"="))
			return (0);
	return (ret);
}

char	**str_to_tab(char *s)
{
	char	**tab;
	int		i;
	int		j;

	if (!s || !get_amt_words(s))
		return (0);
	if (!ft_calloc((void **)&tab, sizeof(char *) * (get_amt_words(s) + 1)))
		return (0);
	i = 0;
	j = -1;
	while (s[i])
	{
		tab[++j] = get_word(s, &i);
		if (!tab[j])
			return ((char **)free_tab(tab, j));
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			++i;
	}
	return (tab);
}
