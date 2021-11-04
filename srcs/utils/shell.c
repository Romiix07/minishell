/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:08:38 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 23:58:47 by rmouduri         ###   ########.fr       */
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
	if (g_shell->tty[0] > 2)
		close(g_shell->tty[0]);
	if (g_shell->tty[1] > 2)
		close(g_shell->tty[1]);
	if (g_shell->ops)
		free(g_shell->ops);
	free(g_shell);
	return (1);
}

int	init_shell(char **env)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return (1);
	g_shell->input = 0;
	g_shell->env = init_env(env);
	g_shell->char_env = 0;
	g_shell->op = NONE;
	g_shell->fct = 0;
	g_shell->exec = 0;
	g_shell->waitstatus = 0;
	g_shell->ret = 0;
	g_shell->pipes = 0;
	g_shell->index = 0;
	g_shell->tty[0] = -1;
	g_shell->tty[1] = -1;
	g_shell->here_line = 0;
	g_shell->ops = 0;
	if (!g_shell->env)
	{
		free_shell();
		return (return_error("Error t_shell initialization", 0, 0, 1));
	}
	return (0);
}
