/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupncpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:52:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/02 13:26:29 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	check_exception(char *s, int len, char *ex)
{
	int	i;
	int	len_cpy;

	i = -1;
	len_cpy = len;
	while (s[++i] && i < len_cpy)
		if (is_charset(s[i], ex))
			--len;
	return (len);
}

char	*ft_strdupncpy(char *s, int len, char *ex)
{
	char	*ret;
	int		i;
	int		j;
	int		len_cpy;

	len_cpy = len;
	if (ex)
		len = check_exception(s, len, ex);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = -1;
	j = -1;
	while (++i < len_cpy)
		if (!is_charset(s[i], ex))
			ret[++j] = s[i];
	ret[++j] = 0;
	return (ret);
}
