/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:27:50 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 17:17:41 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	print_env_export(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		write(1, "declare -x ", 11);
		while (env[i][++j] && env[i][j] != '=')
			write(1, &env[i][j], 1);
		if (env[i][j] && env[i][j] == '=')
		{
			write(1, "=\"", 2);
			while (env[i][++j])
				write(1, &env[i][j], 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
	}
}

char	**free_char_env(char **env, int i)
{
	int	j;

	j = -1;
	while (env[++j] && (j < i || i == -1))
		free(env[j]);
	free(env);
	return (0);
}

static char	*env_to_string(char *name, char *var)
{
	char	*s;
	int		len;
	int		i;

	len = ft_strlen(name) + ft_strlen(var) + 3;
	s = malloc(sizeof(char) * len);
	if (!s)
		return (0);
	len = -1;
	i = -1;
	while (name && name[++len])
		s[++i] = name[len];
	len = -1;
	s[++i] = '=';
	while (var && var[++len])
		s[++i] = var[len];
	s[++i] = 0;
	return (s);
}

char	**dup_env(void)
{
	char	**env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = g_shell->env;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (0);
	i = -1;
	tmp = g_shell->env;
	while (tmp)
	{
		env[++i] = env_to_string(tmp->name, tmp->var);
		if (!env[i])
			return (free_char_env(env, i));
		tmp = tmp->next;
	}
	env[++i] = 0;
	return (env);
}
