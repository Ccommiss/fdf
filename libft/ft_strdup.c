/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:16:37 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/29 10:57:40 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	k;
	char	*stock;

	i = 0;
	k = ft_strlen(s);
	stock = (char *)malloc(sizeof(char) * k + 1);
	if (!stock)
		return (0);
	while (i < k)
	{
		stock[i] = s[i];
		i++;
	}
	stock[i] = '\0';
	return (stock);
}
