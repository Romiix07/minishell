/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_charset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:01:29 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/02 13:41:45 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_charset(char c, const char *charset)
{
	int	i;

	i = -1;
	if (!charset)
		return (0);
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}
