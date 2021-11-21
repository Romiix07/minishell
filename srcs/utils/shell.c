/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:08:38 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/20 13:28:37 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	free_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->var)
		free(node->var);
	free(node);
}

int	free_shell(void)
{
	int	i;

	if (!g_shell)
		return (0);
	if (g_shell->env)
		free_env(g_shell->env);
	if (g_shell->input)
		free_tab(g_shell->input, -1);
	if (g_shell->fct)
		free(g_shell->fct);
	if (g_shell->exec)
		free(g_shell->exec);
	if (g_shell->char_env)
		free_char_env(g_shell->char_env, -1);
	i = -1;
	while (++i < 4)
		if (g_shell->fds[i] > 2)
			close(g_shell->fds[i]);
	if (g_shell->ops)
		free(g_shell->ops);
	if (g_shell->cpids)
		free(g_shell->cpids);
	free(g_shell);
	return (1);
}

static int	init_fds(void)
{
	g_shell->fds[STDIN] = dup(STDIN_FILENO);
	if (g_shell->fds[STDIN] == -1)
		return (-1);
	g_shell->fds[STDOUT] = dup(STDOUT_FILENO);
	if (g_shell->fds[STDOUT] == -1)
		return (-1);
	g_shell->fds[FDIN] = -1;
	g_shell->fds[FDOUT] = -1;
	return (0);
}

int	init_shell(char **env)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return (1);
	g_shell->input = 0;
	if (init_fds() == -1)
		return (free_shell());
	g_shell->env = init_env(env);
	g_shell->char_env = 0;
	g_shell->op = NONE;
	g_shell->fct = 0;
	g_shell->exec = 0;
	g_shell->waitstatus = 0;
	g_shell->ret = 0;
	g_shell->pipes = 0;
	g_shell->index = 0;
	g_shell->here_line = 0;
	g_shell->ops = 0;
	g_shell->cpids = 0;
	g_shell->pid_index = 0;
	if (!g_shell->env)
	{
		free_shell();
		return (return_error("Error t_shell initialization", 0, 0, 1));
	}
	return (0);
}
