/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:57:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/31 11:01:39 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

char	*concatenate_str(char *s, char c)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!ret)
	{
		if (s)
			free(s);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (s && s[++j])
		ret[++i] = s[j];
	if (s)
		free(s);
	j = 0;
	ret[++i] = c;
	ret[++i] = '\0';
	return (ret);
}

char	**get_input(t_shell *shell)
{
	char	*s;
	char	c;
	int		r;

	write(1, "$ ", 2);
	s = 0;
	r = read(0, &c, 1);
	while (r > 0)
	{
		if (c == '\n' || !c)
			break ;
		s = concatenate_str(s, c);
		if (!s)
			return (0);
		r = read(0, &c, 1);
	}
	if (r <= 0 && !s)
		return (0);
	// if (!check_line(s))
		// return (free_items(&s, 1, 0, 0));
	if (!add_hist(shell->hist, s))
		return (free_items((void **)&s, 1, 0, 0));
	return (str_to_tab(s));
}
