/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:56:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/22 12:30:52 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static char	*get_var_name(char *s)
{
	char	name[256];
	int		i;
	int		j;

	if (!s || *s != '$')
		return (0);
	if (s[1] == '?')
		return (1 + g_shell->ret / 10);
	i = 1;
	if (!ft_isalpha(s[i]))
		return (0);
	j = 0;
	name[j] = s[i];
	while (ft_isalnum(s[++i]) || s[i] == '_')
		name[++j] = s[i];
	name[++j] = 0;
	return ((char *)name);
}

int	get_strenv_len(char *s, int i, int len, char state)
{
	char	c;

	c = 0;
	while (s && s[++i])
	{
		if (!state && (s[i] == '\'' || s[i] == '"'))
		{
			state = 1;
			c = s[i];
		}
		else if (state && s[i] == c)
			state = 0;
		else if (s[i] == '$' && (!state || (state && c != '\'')))
		{
			if (s[i + 1] != '?')
				len += ft_strlen(get_env_var(get_var_name(&s[i])));
			else
				len += ft_strlen(get_var_name(&s[i]));
			i += ft_strlen(get_var_name(&s[i]));
		}
	}
	return (len);
}

char	*replace_env_var(char *str)
{
	char	*newstr;
	int		i;
	int		j;
	int		len;

	newstr = NULL;
	len = get_strenv_len(str, -1, 0, 0);
	if (len)
		newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (0);
	i = -1;
	j = -1;
	while (str && str[++i])
	{
		if (str[i] == '$')
		{
			ft_strcpy(&newstr[++j], select_env_var());
			i += ;
		}
		newstr[++j] = str[i];
	
	}
	return (newstr);
}
