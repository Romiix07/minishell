/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:25:50 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/21 22:15:56 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "minishell.h"

static int	closeif(int *fd)
{
	if (fd && *fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
	return (0);
}

int	open_file(char *path, char *op, int fd)
{
	if (ft_strcmp(op, ">") == 0)
	{
		fd = open(path, OPEN_TRUNC, GIVE_RIGHTS);
		g_shell->op |= REDIRECT_TO;
	}
	else if (ft_strcmp(op, ">>") == 0)
	{
		fd = open(path, OPEN_APPEND, GIVE_RIGHTS);
		g_shell->op |= REDIRECT_TO;
	}
	else if (ft_strcmp(op, "<") == 0)
	{
		fd = open(path, O_RDONLY);
		g_shell->op |= REDIRECT_FROM;
	}
	if (fd == -1)
	{
		if (g_shell->op & REDIRECT_FROM)
			g_shell->op ^= REDIRECT_FROM;
		else if (g_shell->op & REDIRECT_TO)
			g_shell->op ^= REDIRECT_TO;
		return (return_error("minishell", path, strerror(errno), -2));
	}
	return (fd);
}

static int	check_pipe(char **input, int j)
{
	int	i;

	i = -1;
	if (!check_symbol(input, j))
		return (-2);
	if (j > 0 && ft_strcmp(input[-1], "|") == 0 && g_shell->ops[j - 1] == 0)
		g_shell->op |= READ_FROM;
	while (input[++i])
	{
		if (ft_strcmp(input[i], "|") == 0 && g_shell->ops[j + i] == 0)
		{
			g_shell->op |= WRITE_TO;
			break ;
		}
	}
	return (i);
}

int	get_and_open_file(char **input, int i, int *pipefd)
{
	int	max;
	int	index;

	max = check_pipe(input, i);
	if (max == -2)
		return (-2);
	index = -1;
	while (++index < max && input[index])
	{
		if (!g_shell->ops[i + index] && !ft_strcmp(input[index], "<"))
			g_shell->fds[FDIN] = closeif(&g_shell->fds[FDIN])
				+ open_file(input[index + 1], input[index], -1);
		else if (!g_shell->ops[i + index] && !ft_strcmp(input[index], "<<"))
			g_shell->fds[FDIN] = here_doc(pipefd, input[index + 1]);
		else if (!g_shell->ops[i + index] && (!ft_strcmp(input[index], ">")
				|| !ft_strcmp(input[index], ">>")))
			g_shell->fds[FDOUT] = closeif(&g_shell->fds[FDOUT])
				+ open_file(input[index + 1], input[index], -1);
		if (g_shell->fds[FDIN] == -2 || g_shell->fds[FDOUT] == -2)
			return (-1);
	}
	return (0);
}
