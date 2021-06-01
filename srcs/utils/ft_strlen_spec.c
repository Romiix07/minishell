/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:32:35 by rmouduri          #+#    #+#             */
/*   Updated: 2021/05/25 10:46:43 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_ischarset(const char *s, const char *charset)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && is_charset(s[i], charset))
		++i;
	return (i);
}

int	ft_strlen_isncharset(const char *s, const char *charset)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && !is_charset(s[i], charset))
		++i;
	return (i);
}

int	ft_strlen_c(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}
