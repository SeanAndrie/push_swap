/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:45 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/03 21:08:31 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	partition_to_b(t_push_swap *ps, int *pushed)
{
	push(ps->stack_a, ps->stack_b, &ps->actions);
	(*pushed)++;
}

void	process_chunk(t_push_swap *ps, int median, int chunk_size)
{
	int	pushed;
	int	rotated;
	int	init_size;

	pushed = 0;
	rotated = 0;
	init_size = ps->stack_a->size;
	while (pushed < chunk_size && ps->stack_a->size > 3)
	{
		if (ps->stack_a->head->data < median || init_size <= chunk_size)
			partition_to_b(ps, &pushed);
		else
		{
			rotate(ps->stack_a, &ps->actions);
			rotated++;
			if (rotated >= init_size)
				partition_to_b(ps, &pushed);
		}
	}
	if (ps->stack_a->size > 3)
		while (rotated-- > 0)
			rrotate(ps->stack_a, &ps->actions);
}

void	chunk_partitions(t_push_swap *ps, int n_chunks)
{
	int	median;
	int	chunk_size;
	int	curr_chunk;

	curr_chunk = 1;
	chunk_size = ft_max(3, ps->stack_a->size / n_chunks);
	while (ps->stack_a->size > 3 && curr_chunk <= n_chunks)
	{
		median = find_chunk_median(ps->stack_a, chunk_size);
		process_chunk(ps, median, chunk_size);
		curr_chunk++;
	}
	if (ps->stack_a->size == 3)
		sort_three(ps->stack_a, &ps->actions);
}

void	merge_chunks(t_push_swap *ps)
{
	int			best_val;
	int			insert_index;
	t_rotation	rot_a;
	t_rotation	rot_b;

	while (ps->stack_b->head)
	{
		best_val = find_best_candidate(ps->stack_a, ps->stack_b);
		insert_index = find_insertion_point(ps->stack_a, best_val);
		rot_a = find_rotations_to_top(ps->stack_a, insert_index);
		rot_b = find_rotations_to_top(ps->stack_b, find_index(ps->stack_b,
					best_val));
		combined_rotation(ps, &rot_a, &rot_b);
		push(ps->stack_b, ps->stack_a, &ps->actions);
	}
	single_rotation(ps->stack_a, find_index(ps->stack_a,
			stack_min(ps->stack_a)), &ps->actions);
}
