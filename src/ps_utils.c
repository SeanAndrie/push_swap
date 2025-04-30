/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:20:49 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/05 21:01:10 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_chunk_median(t_stack *stack, int chunk_size)
{
	int		i;
	int		*arr;
	int		median;
	t_node	*curr;

	arr = malloc(sizeof(int) * chunk_size);
	if (!arr)
		return (0);
	i = 0;
	curr = stack->head;
	while (i < chunk_size)
	{
		arr[i++] = curr->data;
		curr = curr->next;
	}
	quick_sort(arr, 0, ft_min(chunk_size, stack->size) - 1);
	median = arr[chunk_size / 2];
	free(arr);
	return (median);
}

int	find_insertion_point(t_stack *stack_a, int value)
{
	int		min;
	int		max;
	t_node	*curr;
	int		index;

	if (!stack_a || !stack_a->head)
		return (0);
	min = stack_min(stack_a);
	max = stack_max(stack_a);
	if (value < min)
		return (find_index(stack_a, min));
	if (value > max)
		return (find_index(stack_a, max) + 1);
	curr = stack_a->head;
	index = 0;
	while (curr->next)
	{
		if (curr->data < value && curr->next->data > value)
			return (index + 1);
		curr = curr->next;
		index++;
	}
	return ((index + 1) % stack_a->size);
}

t_rotation	find_rotations_to_top(t_stack *stack, int index)
{
	t_rotation	rot;

	rot.n_rotation = 0;
	rot.direction = 0;
	rot.index = index;
	if (!stack || index < 0 || index >= stack->size)
	{
		rot.n_rotation = INT_MAX;
		return (rot);
	}
	if (index > stack->size / 2)
	{
		rot.n_rotation = stack->size - index;
		rot.direction = 1;
	}
	else
	{
		rot.n_rotation = index;
		rot.direction = 0;
	}
	return (rot);
}

int	calculate_cost(t_stack *stack_a, t_stack *stack_b, int value)
{
	t_rotation	rot_a;
	t_rotation	rot_b;

	rot_a = find_rotations_to_top(stack_a, find_insertion_point(stack_a,
				value));
	rot_b = find_rotations_to_top(stack_b, find_index(stack_b, value));
	if (rot_a.n_rotation == INT_MAX || rot_b.n_rotation == INT_MAX)
		return (INT_MAX);
	if (rot_a.direction == rot_b.direction)
		return (ft_max(rot_a.n_rotation, rot_b.n_rotation));
	else
		return (rot_a.n_rotation + rot_b.n_rotation);
}

int	find_best_candidate(t_stack *stack_a, t_stack *stack_b)
{
	int			cost;
	int			index;
	int			min_cost;
	t_node		*curr;
	t_candidate	best;

	index = 0;
	best.index = 0;
	min_cost = INT_MAX;
	best.value = stack_b->head->data;
	curr = stack_b->head;
	while (curr)
	{
		cost = calculate_cost(stack_a, stack_b, curr->data);
		if (cost < min_cost || (cost == min_cost && index < best.index))
		{
			min_cost = cost;
			best.value = curr->data;
			best.index = index;
		}
		index++;
		curr = curr->next;
	}
	return (best.value);
}
