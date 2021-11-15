/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:54:44 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 18:56:56 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*normal_word(char *s, int *index, int start)
{
	int		size;
	char	c;

	size = 0;
	while (s[*index] && !is_charset(s[*index], " \t<>|"))
	{
		if (s[*index] == '\'' || s[*index] == '"')
		{
			c = s[(*index)++];
			while (s[*index] && s[*index] != c)
			{
				++size;
				++(*index);
			}
		}
		if (s[*index])
			++(*index);
		++size;
	}
	return (ft_strdupncpy(&s[start], size, "\'\"", 0));
}
