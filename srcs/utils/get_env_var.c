/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:27:10 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 13:02:09 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static char	*get_path_str(char *path, char *name)
{
	char	*s;
	int		size;
	int		i;

	size = ft_strlen(name) + ft_strlen_c(path, ':');
	s = malloc(sizeof(char) * (size + 2));
	size = -1;
	i = -1;
	while (path[++i] && path[i] != ':')
		s[++size] = path[i];
	s[++size] = '/';
	i = -1;
	while (name[++i])
		s[++size] = name[i];
	s[++size] = 0;
	return (s);
}

int	free_path_tab(char **tab, int i)
{
	int	j;

	j = -1;
	while (++j < i || (tab[j] && i == -1))
		free(tab[j]);
	free(tab);
	return (0);
}

static int	fill_path_tab(char **tab, char *path, char *name, int amount)
{
	int	i;
	int	j;

	tab[0] = ft_strdup(name);
	if (!tab[0])
		return (free_path_tab(tab, 1));
	tab[amount + 2] = 0;
	i = 0;
	j = 0;
	while (++i < amount + 2)
	{
		tab[i] = get_path_str(&path[j], name);
		if (!tab[i])
			return (free_path_tab(tab, i));
		while (path[j] && path[j] != ':')
			++j;
		++j;
	}
	return (1);
}

char	**get_path(char *name)
{
	char	**tab;
	char	*path;
	int		i;
	int		amount;

	path = get_env_var("PATH");
	if (path == 0)
		return (0);
	i = -1;
	amount = 0;
	while (path && path[++i])
		if (path[i] == ':')
			++amount;
	tab = malloc(sizeof(char *) * (amount + 3));
	if (!tab)
		return (0);
	if (!fill_path_tab(tab, path, name, amount))
		return (0);
	return (tab);
}

char	*get_env_var(char *s)
{
	t_env	*tmp;

	tmp = g_shell->env;
	while (tmp)
	{
		if (tmp->name && ft_strcmp(tmp->name, s) == 0)
			return (tmp->var);
		tmp = tmp->next;
	}
	return (0);
}
