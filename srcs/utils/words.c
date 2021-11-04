/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:25:22 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/08 17:26:53 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

char	*get_classic_word(char **ret, char *s, int *i, char *charset)
{
	int	j;

	*ret = 0;
	j = -1;
	if (!ft_calloc((void **)ret, sizeof(char)
			* (ft_strlen_isncharset(&s[*i], charset) + 1)))
		return (0);
	while (s[*i] && !is_charset(s[*i], charset))
		(*ret)[++j] = s[(*i)++];
	(*ret)[++j] = 0;
	return (*ret);
}

char	*get_quote(char **ret, char *s, int *i, char c)
{
	int	j;

	*ret = 0;
	j = -1;
	if (!ft_calloc((void **)ret, (ft_strlen_c(&s[*i + 1], c) + 3)))
		return (0);
	(*ret)[++j] = c;
	++(*i);
	while (s[*i] && s[*i] != c)
		(*ret)[++j] = s[(*i)++];
	if (s[*i] == c)
		(*ret)[++j] = c;
	(*ret)[++j] = 0;
	if (s[*i])
		++(*i);
	return (*ret);
}

char	*get_dollar(char **ret, char *s, int *i)
{
	int	j;
	int	size;

	size = 0;
	++(*i);
	j = *i;
	while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
	{
		++j;
		++size;
	}
	if (!ft_calloc((void **)ret, sizeof(char) * (size + 2)))
		return (0);
	j = -1;
	(*ret)[++j] = '$';
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*ret)[++j] = s[(*i)++];
	(*ret)[++j] = 0;
	return (*ret);
}

char	*get_same_char(char **ret, char *s, int *i, char c)
{
	int	size;
	int	j;

	j = -1;
	size = 0;
	while (s[(*i)] == c)
	{
		++(*i);
		++size;
	}
	if (!ft_calloc((void **)ret, sizeof(char) * (size + 1)))
		return (0);
	while (--size >= 0)
		(*ret)[++j] = c;
	(*ret)[++j] = 0;
	return (*ret);
}
