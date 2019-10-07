/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:39:29 by floblanc          #+#    #+#             */
/*   Updated: 2019/09/25 17:58:15 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libprintf.h"

int		find_index(char c, char *base)
{
	int i;

	i = 0;
	while (base[i] != c)
		i++;
	return (i);
}

int		parser(char *base, int size)
{
	int i;
	int	j;

	i = 0;
	if (!(base && size > 1))
		return (0);
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j] || base[j] == ' ' || base[j] == '+'
				|| base[j] == '-')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_atoi_base(char *str, char *base, char *prefix)
{
	int i;
	int	res;
	int size;

	i = 0;
	res = 0;
	size = ft_strlen(base);
	if (!parser(base, size))
		return (0);
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (prefix && ft_strncmp(str + i, prefix, ft_strlen(prefix)))
		return (0);
	if (prefix)
		i += ft_strlen(prefix);
	while (str[i] == base[0])
		i++;
	while (str[i] && ft_charstr(&(str[i]), base))
		res = (res * size) + find_index(str[i++], base);
	return (res);
}
