/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:41:23 by user42            #+#    #+#             */
/*   Updated: 2021/11/03 23:29:15 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

int	check_dollar(char *s, int *index, char **ret, t_env *env)
{
	t_env	*tmp;
	char	*str;
	int		keep;

	*index += 1;
	tmp = env;
	keep = *index;
	str = 0;
	while (s[keep])
	{
		if (s[keep] == '"' || s[keep] == '$')
			break ;
		keep++;
	}
	while (*index < keep)
	{
		str = concatenate_str(str, s[*index]);
		*index += 1;
	}
	*index -= 1;
	keep = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			while (tmp->var[keep])
			{
				*ret = concatenate_str(*ret, tmp->var[keep]);
				keep++;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*check_quote_dollar(char *s, t_env *env)
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
				while (*tmp)
				{
					ret = concatenate_str(ret, *tmp);
					*tmp++;
				}
			}
			check_dollar(s, &index, &ret, env);
		}
		else
			ret = concatenate_str(ret, s[index]);
	}
	free(s);
	return (ret);
}
