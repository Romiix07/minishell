/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:41:23 by user42            #+#    #+#             */
/*   Updated: 2021/11/09 14:48:01 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

int	check_dollar_3(char *str, char **ret)
{
	int	keep;

	if (str == 0)
	{
		*ret = concatenate_str(*ret, '$');
		return (0);
	}
	if (ft_isalpha(str[0]) || str[0] == '_' || str[0] == '?')
		return (1);
	keep = 0;
	*ret = concatenate_str(*ret, '$');
	while (str[keep])
	{
		*ret = concatenate_str(*ret, str[keep]);
		keep++;
	}
	free(str);
	return (0);
}

int	check_dollar_2(char *str, char **ret, t_env *env)
{
	t_env	*tmp;
	int		keep;

	tmp = env;
	keep = 0;
	if (check_dollar_3(str, ret) == 0)
		return (0);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			while (tmp->var[keep])
			{
				*ret = concatenate_str(*ret, tmp->var[keep]);
				keep++;
			}
			free(str);
			return (1);
		}
		tmp = tmp->next;
	}
	free(str);
	return (0);
}

int	check_dollar(char *s, int *index, char **ret, t_env *env)
{
	char	*str;
	int		keep;

	*index += 1;
	keep = *index;
	str = 0;
	if (s[*index] == '$')
	{
		if (s[*index + 1])
			*index -= 1;
		return (0);
	}
	while (s[keep])
	{
		if (s[keep] == '"' || s[keep] == '$' || s[keep] == ' ')
			break ;
		keep++;
	}
	while (*index < keep)
	{
		str = concatenate_str(str, s[*index]);
		*index += 1;
	}
	*index -= 1;
	return (check_dollar_2(str, ret, env));
}

char	*check_quote_dollar(char *s, t_env *env, int keep)
{
	char	*ret;
	char	*tmp;
	int		index;

	index = -1;
	ret = 0;
	while (s[++index])
	{
		if (s[index] == '$')
		{
			if (s[index + 1] == '?')
			{
				tmp = ft_itoa(g_shell->ret);
				keep = -1;
				while (tmp[++keep])
					ret = concatenate_str(ret, tmp[keep]);
				free(tmp);
			}
			check_dollar(s, &index, &ret, env);
		}
		else
			ret = concatenate_str(ret, s[index]);
	}
	free(s);
	return (ret);
}
