/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:28:17 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/27 18:02:30 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "minishell.h"

static int	ft_cd_topath(void)
{
	char	*pwd;

	if (chdir(g_shell->fct[1]) == -1)
		return (return_error("cd", strerror(errno),
				g_shell->fct[1], 1));
	pwd = getcwd(0, 0);
	if (!pwd)
		return (return_error("minishell: cd", "Can't get current working \
		directory", 0, 1));
	if (!ft_setenv("OLDPWD", get_env_var("PWD")))
	{
		free(pwd);
		return (return_error("minishell: cd", "Can't set PWD", 0, 1));
	}
	if (!ft_setenv("PWD", pwd))
	{
		free(pwd);
		return (return_error("minishell: cd", "Can't set OLDPWD", 0, 1));
	}
	free(pwd);
	return (0);
}

static int	ft_cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env_var("PWD");
	if (!oldpwd)
		return (return_error("minishell: cd", "Can't get env var PWD", 0, 1));
	oldpwd = ft_strdup(get_env_var("OLDPWD"));
	if (!oldpwd)
		return (return_error("minishell: cd", "Can't get env var \
		OLDPWD", 0, 0));
	if (chdir(oldpwd) == -1)
	{
		free(oldpwd);
		return (return_error("minishell: cd", "Can't go to", oldpwd, 1));
	}
	if (!ft_setenv("OLDPWD", get_env_var("PWD")))
	{
		free(oldpwd);
		return (return_error("minishell: cd", "Can't set PWD", 0, 1));
	}
	if (!ft_setenv("PWD", oldpwd))
	{
		free(oldpwd);
		return (return_error("minishell: cd", "Can't set OLDPWD", 0, 1));
	}
	free(oldpwd);
	return (0);
}

static int	ft_cd_home(void)
{
	char	*home;
	t_env	*tmp;

	home = get_env_var("HOME");
	if (!home)
		return (return_error("Can't get env value HOME", 0, 0, 1));
	if (chdir(home) == -1)
		return (return_error("cd", strerror(errno), home, 1));
	if (!ft_setenv("OLDPWD", get_env_var("PWD")))
		return (return_error("Can't modify/malloc existing\
		OLDPWD env val", 0, 0, 1));
	tmp = g_shell->env;
	while (tmp && tmp->next && ft_strcmp("PWD", tmp->next->name) != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->next)
	{
		if (!ft_setenv("PWD", home))
			return (return_error("Can't malloc PWD env val", 0, 0, 1));
		return (0);
	}
	if (!ft_setenv("PWD", home))
		return (return_error("Can't modify/malloc existing \
		PWD env val", 0, 0, 1));
	return (0);
}

int	ft_cd(void)
{
	int		ret;
	char	*s;

	if (!g_shell->fct[1] || !ft_strcmp(g_shell->fct[1], "~"))
		return (ft_cd_home());
	else if (!ft_strcmp(g_shell->fct[1], "-"))
	{
		ret = ft_cd_oldpwd();
		s = get_env_var("PWD");
		if (s)
		{
			write(1, s, ft_strlen(s));
			write(1, "\n", 1);
		}
		return (ret);
	}
	else
		return (ft_cd_topath());
	return (0);
}
