/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:56:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/22 15:03:12 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static char	*get_var_name(char *s, char name[256])
{
	int		i;
	int		j;

	if (!s || *s != '$')
		return (0);
	i = 1;
	if (!ft_isalpha(s[i]))
		return (0);
	j = 0;
	name[j] = s[i];
	while (ft_isalnum(s[++i]) || s[i] == '_')
		name[++j] = s[i];
	name[++j] = 0;
	return (name);
}

static char	*select_env_var(char *s, char str[256])
{
	int		i;
	int		n;

	if (!s || *s != '$')
		return (0);
	if (!ft_strncmp(s, "$?", 2))
	{
		n = g_shell->ret;
		if (n > 99)
			i = 2;
		else if (n < 10)
			i = 0;
		else
			i = 1;
		str[i + 1] = 0;
		while (i >= 0)
		{
			str[i--] = n % 10 + 48;
			n /= 10;
		}
	}
	else
		ft_strcpy(str, get_env_var(get_var_name(s, str)));
	return ((char *)str);
}

static int	get_strenv_len(char *s, int i, int len, char state)
{
	char	c;
	char	tmp[256];

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
			len += ft_strlen(select_env_var(&s[i], tmp));
			i += ft_strlen(select_env_var(&s[i], tmp));
		}
		++len;
	}
	return (len);
}

char	*loop_replace(char *newstr, char *str, char tmp[256], int i)
{
	int		state;
	char	c;
	int		j;

	j = -1;
	while (str && str[++i])
	{
		if (!state && (str[i] == '\'' || str[i] == '"'))
		{
			state = 1;
			c = str[i];
		}
		else if (state && str[i] == c)
			state = 0;
		if (str[i] == '$' && (!state || (state && c != '\'')))
		{
			ft_strcpy(&newstr[++j], select_env_var(&str[i], tmp));
			i += ft_strlen(get_var_name(&str[i], tmp));
			j += ft_strlen(get_env_var(get_var_name(&str[i], tmp)));
		}
		else
			newstr[++j] = str[i];
	}
	newstr[++j] = 0;
	return (newstr);
}

char	*replace_env_var(char *str)
{
	char	*newstr;
	char	tmp[256];
	int		len;

	newstr = NULL;
	len = get_strenv_len(str, -1, 0, 0);
	printf("len = %d\n", len);
	if (len)
		newstr = malloc(sizeof(char) * (len + 1));
	if (!newstr)
		return (0);
	newstr = loop_replace(newstr, str, tmp, -1);
	return (newstr);
}
