/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:00:49 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/11 20:38:51 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	pipe_check(char **input, int i, int *fd)
{
	if (input && input[0] && !ft_strcmp(input[0], "|") && i == 0)
	{
		*fd = -2;
		write(STDERR_FILENO, "minishell: Redirection operator \" ", 34);
		write(STDERR_FILENO, "|", 1);
		write(STDERR_FILENO, " \" requires a valid argument\n", 29);
		return (-1);
	}
	return (0);
}

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

char	**get_arg_tab(char **input, int j, int *fd)
{
	char	**arg_tab;
	int		i;
	int		size;

	if (pipe_check(input, j, fd) == -1)
		return (0);
	size = get_size_arg_tab(input, j);
	if (size <= 0)
		return (0);
	if (!ft_calloc((void **)&arg_tab, sizeof(char *) * (size + 1)))
		return (0);
	i = -1;
	while (++i < size)
		arg_tab[i] = input[i];
	arg_tab[i] = 0;
	return (arg_tab);
}
