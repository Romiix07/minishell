/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 22:16:47 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/21 22:21:28 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	get_size_arg_tab(char **tab, int j)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	if (!tab)
		return (-1);
	while (tab[++i] && (g_shell->ops[j + i] > 0
			|| (ft_strcmp(tab[i], ">") && ft_strcmp(tab[i], ">>")
				&& ft_strcmp(tab[i], "<") && ft_strcmp(tab[i], "<<")
				&& ft_strcmp(tab[i], "|"))))
		++size;
	return (size);
}

static int	get_offset(char **input, int j)
{
	int	offset;

	offset = 0;
	while (!g_shell->ops[j] && input[offset] && ft_strcmp(input[offset], "|"))
	{
		if ((!ft_strcmp(input[offset], "<") || !ft_strcmp(input[offset], "<<")
				|| !ft_strcmp(input[offset], ">")
				|| !ft_strcmp(input[offset], ">>")) && input[offset + 1])
		{
			offset += 2;
			++j;
		}
		else
			break ;
	}
	return (offset - 1);
}

char	**get_arg_tab(char **input, int j, __attribute__((unused))int *fd)
{
	char	**arg_tab;
	int		i;
	int		size;
	int		offset;

	offset = get_offset(input, j);
	size = get_size_arg_tab(&input[offset + 1], j);
	if (size <= 0)
		return (0);
	if (!ft_calloc((void **)&arg_tab, sizeof(char *) * (size + 1)))
		return (0);
	i = -1;
	while (++offset >= 0 && ++i < size)
		arg_tab[i] = input[offset];
	arg_tab[i] = 0;
	return (arg_tab);
}
