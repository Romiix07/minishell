/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:42:53 by user42            #+#    #+#             */
/*   Updated: 2021/11/02 13:46:35 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

char	*pre_concatenate_str(char *s, char c)
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
	ret[++i] = c;
	while (s && s[++j])
		ret[++i] = s[j];
	if (s)
		free(s);
	j = 0;
	ret[++i] = '\0';
	return (ret);
}

char	*ft_itoa(int nb)
{
	char	*ret;

	ret = 0;
	if (nb > 9)
	{
		ret = concatenate_str(ret, '0' + (nb % 10));
		nb /= 10;
	}
	else
	{
		ret = concatenate_str(ret, '0' + (nb % 10));
		return (ret);
	}
	while (nb > 9)
	{
		ret = pre_concatenate_str(ret, '0' + (nb % 10));
		nb /= 10;
	}
	ret = pre_concatenate_str(ret, '0' + (nb % 10));
	return (ret);
}
