/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:25:50 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/17 20:25:49 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "minishell.h"

void	reset_redirect(void)
{
	dup2(g_shell->tty[0], STDIN_FILENO);
	dup2(g_shell->tty[1], STDOUT_FILENO);
}

int	ft_redirect(int fd, int *pipefd)
{
	if (g_shell->op & HERE_DOC)
		here_doc(pipefd);
	else if (g_shell->op & READ_FROM)
		dup_close_set(pipefd[(g_shell->index - 1) * 2 + 0], STDIN_FILENO, -1);
	else if (g_shell->index > 0)
	{
		close(pipefd[(g_shell->index - 1) * 2 + 0]);
		close(pipefd[(g_shell->index - 1) * 2 + 1]);
	}
	if (g_shell->op & WRITE_TO)
		dup_close_set(pipefd[g_shell->index * 2 + 1], STDOUT_FILENO, -1);
	else
		close(pipefd[g_shell->index * 2 + 1]);
	if (g_shell->op & REDIRECT_TO)
		dup2(fd, STDOUT_FILENO);
	else if (g_shell->op & REDIRECT_FROM)
		dup2(fd, STDIN_FILENO);
	if (fd > 2)
		close(fd);
	return (0);
}

int	open_file(char *path, char *op, char *heredoc)
{
	int	fd;

	fd = 0;
	g_shell->here_str = heredoc;
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
		g_shell->op &= REDIRECT_FROM | REDIRECT_TO;
		return_error("minishell", path, strerror(errno), -1);
	}
	return (fd);
}

int	check_fctargs(char **input)
{
	int	i;
	int	fd;

	i = -1;
	while (input[++i])
	{
		fd = -1;
		if (ft_strcmp(input[i], "<") == 0
			|| ft_strcmp(input[i], ">") == 0
			|| ft_strcmp(input[i], ">>") == 0)
		{
			fd = open_file(input[i + 1], input[i], 0);
			if (fd == -1)
				return (1);
			else if (fd > 2)
				close(fd);
		}
	}
	return (0);
}

int	get_and_open_file(char **input, int j, int i)
{
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
	while (--i >= 0)
	{
		if (ft_strcmp(input[i], "<<") == 0 && g_shell->ops[j + i] == 0)
			g_shell->op |= HERE_DOC;
		if (g_shell->ops[j + i] == 0
			&& (ft_strcmp(input[i], ">") == 0 || ft_strcmp(input[i], "<") == 0
				|| ft_strcmp(input[i], ">>") == 0
				|| ft_strcmp(input[i], "<<") == 0))
			return (open_file(input[i + 1], input[i], input[i + 1]));
	}
	return (0);
}
