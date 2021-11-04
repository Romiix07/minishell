/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:25:57 by rmouduri          #+#    #+#             */
/*   Updated: 2021/10/08 17:25:59 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (((unsigned char)c >= '0' && (unsigned char)c <= '9')
		|| (((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
			|| ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')))
		return (1);
	return (0);
}
