/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:39:15 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 17:23:32 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static int	check_argv(int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac - 1)
		if (ft_strcmp(av[i], av[i + 1]) > 0)
			return (0);
	return (1);
}

static char	**tab_dup(char **tab)
{
	int		i;
	int		len;
	char	**ret;

	len = 0;
	while (tab[len])
		++len;
	i = -1;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (0);
	while (++i < len)
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
		{
			free_tab(ret, i);
			return (0);
		}
	}
	ret[i] = 0;
	return (ret);
}

static int	sort_print_env(char **env, int len)
{
	int		i;
	char	*tmp;

	while (!check_argv(len, env))
	{
		i = -1;
		while (++i < len - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
		}
	}
	print_env_export(env);
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	return (0);
}

static int	export_val(char *tab, int j)
{
	t_env	*node;

	if (tab && (tab[0] == 0 || tab[0] == '='))
		return_error("minishell: export", tab, "not a valid identifier", 1);
	while (tab[++j] && tab[j] != '=')
	{
		if ((!ft_isalpha(tab[0]) && tab[0] != '_')
			|| (tab[j] != '_' && !ft_isalnum(tab[j])))
		{
			return_error("minishell: export", tab,
				"not a valid identifier", 1);
			break ;
		}
		else if (tab[j + 1] == '=' || !tab[j + 1])
		{
			node = ft_envnew(tab);
			if (!node)
				return (return_error("export: Can't malloc", 0, 0, 1));
			else if (!ft_setenv(node->name, node->var))
				return_error("export: Can't set", node->name, 0, 1);
			free_node(node);
		}
	}
	return (0);
}

int	ft_export(void)
{
	int		len;
	int		ret;
	char	**env;

	if (!g_shell->fct[1])
	{
		len = 0;
		while (g_shell->char_env[len])
			++len;
		env = tab_dup(g_shell->char_env);
		if (!env)
			return (return_error("export: Can't malloc", 0, 0, 1));
		return (sort_print_env(env, len));
	}
	else
	{
		len = -1;
		ret = 0;
		while (g_shell->fct[++len + 1])
			if (export_val(g_shell->fct[len + 1], -1) == 1)
				ret = 1;
		return (ret);
	}
	return (0);
}
