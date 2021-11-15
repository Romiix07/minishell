/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:27:27 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/09 17:56:00 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "minishell.h"

int	check_exec(char **path)
{
	struct stat	statbuf;
	int			i;
	int			ret;

	if (!path)
		return (-1);
	i = -1;
	while (path[++i])
	{
		ret = stat(path[i], &statbuf);
		if (ret == 0 && statbuf.st_mode & S_IXUSR)
			return (i);
	}
	return (-1);
}

int	check_function(int i)
{
	int	ret;

	ret = 0;
	g_shell->cpid = fork();
	if (g_shell->cpid == 0)
	{
		if (g_shell->exec && g_shell->fct && g_shell->env)
			ret = execve(g_shell->exec, g_shell->fct, g_shell->char_env);
		if (ret == -1)
		{
			return_error("minishell", g_shell->input[i],
				"command not found", 0);
			exit(127);
		}
	}
	return (ret);
}

int	is_builtin(int i)
{
	if (!ft_strcmp(g_shell->input[i], "cd")
		|| !ft_strcmp(g_shell->input[i], "pwd")
		|| !ft_strcmp(g_shell->input[i], "export")
		|| !ft_strcmp(g_shell->input[i], "unset")
		|| !ft_strcmp(g_shell->input[i], "echo")
		|| !ft_strcmp(g_shell->input[i], "env")
		|| !ft_strcmp(g_shell->input[i], "exit"))
		return (1);
	return (0);
}

int	check_builtins(int i, int *pipefd)
{
	g_shell->ret = -1;
	if (!is_builtin(i))
		return (-1);
	if (ft_strcmp(g_shell->input[i], "cd") == 0)
		g_shell->ret = ft_cd();
	else if (ft_strcmp(g_shell->input[i], "export") == 0)
		g_shell->ret = ft_export();
	else if (ft_strcmp(g_shell->input[i], "unset") == 0)
		g_shell->ret = ft_unset();
	else if (ft_strcmp(g_shell->input[i], "exit") == 0)
		ft_exit(pipefd);
	if (g_shell->ret != -1)
		return (g_shell->ret);
	g_shell->cpid = fork();
	if (g_shell->cpid == 0)
	{
		if (ft_strcmp(g_shell->input[i], "echo") == 0)
			g_shell->ret = ft_echo(g_shell->fct + 1);
		else if (ft_strcmp(g_shell->input[i], "pwd") == 0)
			g_shell->ret = ft_pwd();
		else if (ft_strcmp(g_shell->input[i], "env") == 0)
			g_shell->ret = print_env(g_shell->env);
		exit(g_shell->ret);
	}
	return (0);
}
