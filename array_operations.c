/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:52:53 by jmabel            #+#    #+#             */
/*   Updated: 2022/03/21 19:44:57 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_count_column(char const *s, char c)
{
	int	count;
	int	i;
	int	len;

	len = (int)ft_strlen(s);
	i = 0;
	count = 0;
	if (len == 0)
		return (count);
	if (s[len - 1] == '\n')
		len--;
	while (i < len)
	{
		if (s[i] != c && (s[i + 1] == c
				|| s[i + 1] == '\0' || s[i + 1] == '\n'))
			count++;
		i++;
	}
	return (count);
}