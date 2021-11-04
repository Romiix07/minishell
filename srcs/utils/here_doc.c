/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:19:24 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/28 18:43:33 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static int	here_doc_error(void)
{
	write(STDERR_FILENO, "minishell: warning: here-document at line ", 42);
	ft_putnbr_fd(g_shell->here_line, STDERR_FILENO);
	write(STDERR_FILENO, " delimited by end-of-file (wanted \"", 35);
	write(STDERR_FILENO, g_shell->here_str, ft_strlen(g_shell->here_str));
	write(STDERR_FILENO, "\")\n", 3);
	return (2);
}

static int	init_here_doc(int *pipefd, int fds[2])
{
	if (pipe(fds) == -1)
		return (0);
	if (g_shell->op & READ_FROM)
		close(pipefd[(g_shell->index - 1) * 2 + 0]);
	return (1);
}

int	here_doc(int *pipefd)
{
	char	*line;
	int		fds[2];

	if (!init_here_doc(pipefd, fds))
		return (return_error("minishell: here-doc: Can't open pipe", 0, 0, 1));
	while (1)
	{
		line = readline("> ");
		++g_shell->here_line;
		if (!line || !ft_strcmp(line, g_shell->here_str))
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	if (!dup_close_set(fds[0], STDIN_FILENO, -1))
		return (0);
	close(fds[1]);
	if (!line)
		return (here_doc_error());
	free(line);
	return (0);
}