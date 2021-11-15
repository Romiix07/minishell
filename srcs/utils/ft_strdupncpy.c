/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupncpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:52:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/09 15:56:15 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	check_exception(char *s, int len, char *ex, char c)
{
	int	i;
	int	len_cpy;

	i = -1;
	len_cpy = len;
	while (s[++i] && i < len_cpy)
		if ((c && s[i] == c) || (ex && is_charset(s[i], ex)))
			--len;
	return (len);
}

char	*ft_strdupncpy(char *s, int len, char *ex, char c)
{
	char	*ret;
	int		i;
	int		j;
	int		len_cpy;

	len_cpy = len;
	if (ex || c)
		len = check_exception(s, len, ex, c);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = -1;
	j = -1;
	while (++i < len_cpy)
		if (!is_charset(s[i], ex) && s[i] != c)
			ret[++j] = s[i];
	ret[++j] = 0;
	return (ret);
}
