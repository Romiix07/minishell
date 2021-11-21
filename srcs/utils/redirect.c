/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:14:44 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/20 17:27:31 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

void	reset_redirect(void)
{
	dup2(g_shell->fds[STDIN], STDIN_FILENO);
	dup2(g_shell->fds[STDOUT], STDOUT_FILENO);
}

int	ft_redirect(int *pipefd)
{
	if (g_shell->op & HERE_DOC)
		dup_close_set(g_shell->here_fd, STDIN_FILENO, -1);
	if (g_shell->op & READ_FROM)
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
		dup_close_set(g_shell->fds[FDOUT], STDOUT_FILENO, -1);
	if (g_shell->op & REDIRECT_FROM)
		dup_close_set(g_shell->fds[FDIN], STDIN_FILENO, -1);
	return (0);
}
