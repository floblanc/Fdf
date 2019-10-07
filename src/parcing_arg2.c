/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_arg2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:00:37 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/05 12:00:57 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		parse_split(t_stock *cur, int letter, int word)
{
	cur->data[word][letter] = 0;
	letter = 0;
	if (cur->data[word][letter] == '-')
		letter++;
	while (ft_isdigit(cur->data[word][letter]))
		letter++;
	if (cur->data[word][letter] || letter > 10 || ft_atol(cur->data[word])
			> 2147483647 || ft_atol(cur->data[word]) < -2147483648)
		return (0);
	return (1);
}
