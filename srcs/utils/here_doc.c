/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:19:24 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/20 17:24:27 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "minishell.h"

static int	here_doc_error(char *heredoc)
{
	write(STDERR_FILENO, "minishell: warning: here-document at line ", 42);
	ft_putnbr_fd(g_shell->here_line, STDERR_FILENO);
	write(STDERR_FILENO, " delimited by end-of-file (wanted \"", 35);
	write(STDERR_FILENO, heredoc, ft_strlen(heredoc));
	write(STDERR_FILENO, "\")\n", 3);
	return (2);
}

static int	init_here_doc(int *pipefd, int fds[2])
{
	if (g_shell->op & HERE_DOC && g_shell->here_fd > 2)
		close(g_shell->here_fd);
	else
		g_shell->op |= HERE_DOC;
	fds[0] = open(".here_doc", O_RDONLY | O_CREAT | O_TRUNC, GIVE_RIGHTS);
	if (fds[0] == -1)
		return (0);
	fds[1] = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, GIVE_RIGHTS);
	if (fds[1] == -1)
	{
		close(fds[0]);
		return (0);
	}
	if (g_shell->op & READ_FROM)
	{
		close(pipefd[(g_shell->index - 1) * 2 + 0]);
		g_shell->op ^= READ_FROM;
	}
	if (g_shell->op & REDIRECT_FROM)
	{
		close(g_shell->fds[FDIN]);
		g_shell->op ^= REDIRECT_FROM;
	}
	return (1);
}

int	here_doc(int *pipefd, char *heredoc)
{
	char	*line;
	int		fds[2];

	if (!init_here_doc(pipefd, fds))
		return (return_error("minishell: here-doc: Can't open file", 0, 0, -2));
	while (1)
	{
		line = readline("> ");
		++g_shell->here_line;
		if (!line || !ft_strcmp(line, heredoc))
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	g_shell->here_fd = fds[0];
	close(fds[1]);
	if (!line)
		return (here_doc_error(heredoc));
	free(line);
	return (0);
}
