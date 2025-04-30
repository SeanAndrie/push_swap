/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 22:46:46 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/04 00:17:01 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	hash(int key)
{
	if (key < 0)
		key = -key + HASH_SIZE;
	return (key % HASH_SIZE);
}

void	insert(t_hashmap **map, int key, int value)
{
	int	index;

	index = hash(key);
	while (map[index])
	{
		if (map[index]->key == key)
		{
			map[index]->value = value;
			return ;
		}
		index = (index + 1) % HASH_SIZE;
	}
	map[index] = malloc(sizeof(t_hashmap));
	if (!map[index])
		return ;
	map[index]->key = key;
	map[index]->value = value;
}

t_hashmap	*search(t_hashmap **map, int key)
{
	int	index;

	index = hash(key);
	while (map[index])
	{
		if (map[index]->key == key)
			return (map[index]);
		index = (index + 1) % HASH_SIZE;
	}
	return (NULL);
}

void	free_map(t_hashmap **map)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
}
