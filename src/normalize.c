/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:22:31 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/28 01:09:44 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	partition(int *arr, int low, int high)
{
	int	i;
	int	j;
	int	pivot;

	i = low - 1;
	j = low;
	pivot = arr[high];
	while (j < high)
	{
		if (arr[j] < pivot)
			ft_swap(&arr[++i], &arr[j]);
		j++;
	}
	ft_swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quick_sort(int *arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

void	stack_to_sorted_hashmap(t_stack *stack, t_hashmap **map)
{
	int	*arr;
	int	i;

	if (!stack || !map || stack->size == 0)
		return ;
	arr = stack_to_arr(stack);
	if (!arr)
		return ;
	quick_sort(arr, 0, stack->size - 1);
	i = 0;
	while (i < stack->size)
	{
		insert(map, arr[i], i);
		i++;
	}
	free(arr);
}

void	stack_normalize(t_stack *stack, t_hashmap **map)
{
	t_node		*curr;
	t_hashmap	*entry;

	if (!stack || !map || stack->size == 0)
		return ;
	curr = stack->head;
	while (curr)
	{
		entry = search(map, curr->data);
		if (!entry)
			return ;
		curr->data = entry->value;
		curr = curr->next;
	}
}
