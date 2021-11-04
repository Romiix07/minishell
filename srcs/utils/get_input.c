/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:57:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 23:33:48 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int	temp_check(char *temp)
{
	int	i;

	i = -1;
	if (temp == 0)
		return (1);
	if (temp[0] == '\n')
		return (0);
	while (temp[++i])
	{
		if (temp[i] != ' ' && temp[i] != '\n' && temp[i] != '\0')
			return (1);
	}
	return (0);
}

char	*concatenate_str(char *s, char c)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!ret)
	{
		if (s)
			free(s);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (s && s[++j])
		ret[++i] = s[j];
	if (s)
		free(s);
	j = 0;
	ret[++i] = c;
	ret[++i] = '\0';
	return (ret);
}

static char	**modify_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (g_shell->ops[i] == 0 && ft_strchr(tab[i], '$'))
		{
			tab[i] = check_quote_dollar(tab[i], g_shell->env);
			if (!tab[i])
			{
				free_tab(tab, i);
				return (0);
			}
		}
	}
	return (tab);
}

__int8_t	get_ops(char *s)
{
	int			i;

	i = 0;
	if (s && *s != '\'')
		return (0);
	while (s[++i])
	{
		if (s[i] == '\'' && is_charset(s[i + 1], " \t"))
			return (2);
		else if (s[i] == '\'' && !is_charset(s[i + 1], " \t"))
			return (1);
	}
	return (0);
}

char	**get_input(void)
{
	int		i;
	char	*s;
	char	**tab;

	s = 0;
	s = readline("$ ");
	if (!s)
		ft_exit();
	if (temp_check(s) == 1)
		add_history(s);
	if (s && !get_amt_wd_1(s, 0, 0))
	{
		free(s);
		return (0);
	}
	g_shell->ops = malloc(sizeof(__int8_t) * get_amt_wd_1(s, 0, 0));
	if (!g_shell->ops)
		return (0);
	tab = str_to_tab_1(s);
	if (!tab)
	{
		return_error("minishell: Can't malloc tab", 0, 0, 0);
		return (0);
	}
	return (modify_tab(tab));
}
