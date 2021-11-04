/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:27:23 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/15 20:23:12 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

void	close_pipes(int *pipefd)
{
	int	i;

	i = -1;
	while (++i < g_shell->pipes * 2)
	{
		if (pipefd[i] > 2)
			close(pipefd[i]);
	}
	g_shell->index = 0;
	free(pipefd);
	if (g_shell->tty[0] > 2)
		close(g_shell->tty[0]);
	if (g_shell->tty[1] > 2)
		close(g_shell->tty[1]);
	g_shell->tty[0] = -1;
	g_shell->tty[1] = -1;
}

int	*create_pipes(void)
{
	int	i;
	int	*pipefd;

	g_shell->pipes = 1;
	i = -1;
	while (g_shell->input[++i])
		if (ft_strcmp(g_shell->input[i], "|") == 0)
			++g_shell->pipes;
	pipefd = malloc(sizeof(int) * (g_shell->pipes * 2));
	if (!pipefd)
		return (0);
	i = 0;
	while (i < g_shell->pipes * 2)
	{
		pipe(&pipefd[i]);
		i += 2;
	}
	return (pipefd);
}
