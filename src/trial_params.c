/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trial_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:38:18 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/01 19:17:24 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort(t_push_swap *ps, int n_chunks)
{
	chunk_partitions(ps, n_chunks);
	merge_chunks(ps);
}

int	*create_chunks(int n_trials)
{
	int	i;
	int	end;
	int	start;
	int	*chunks;

	if (n_trials <= 0)
		return (NULL);
	start = 3;
	end = n_trials + 3;
	chunks = malloc(sizeof(int) * ((end - start) + 1));
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < (end - start) + 1)
	{
		chunks[i] = start + i;
		i++;
	}
	return (chunks);
}

void	validate_and_save(t_push_swap *copy, t_action **best_actions,
		int *min_ops)
{
	int	curr_ops;

	curr_ops = count_actions(copy->actions);
	if (is_sorted(copy->stack_a) && curr_ops < *min_ops)
	{
		*min_ops = curr_ops;
		if (*best_actions)
			free_actions(*best_actions);
		*best_actions = copy_actions(copy->actions);
	}
}

t_action	*find_optimal_actions(t_push_swap *ps, int *chunks, int n_trials)
{
	int			i;
	int			min_ops;
	t_push_swap	*copy;
	t_action	*best_actions;

	min_ops = INT_MAX;
	best_actions = NULL;
	i = 0;
	while (i < n_trials)
	{
		copy = copy_init_state(ps);
		if (!copy)
		{
			free_actions(best_actions);
			break ;
		}
		sort(copy, chunks[i]);
		validate_and_save(copy, &best_actions, &min_ops);
		free(copy->stack_a->name);
		free_push_swap(copy);
		i++;
	}
	return (best_actions);
}

void	trial_sort(t_push_swap *ps, int n_trials)
{
	int			*chunks;
	t_action	*optimal_actions;

	chunks = create_chunks(n_trials);
	if (!chunks)
		return ;
	optimal_actions = find_optimal_actions(ps, chunks, n_trials);
	if (optimal_actions)
	{
		ps->actions = optimal_actions;
		print_actions(ps->actions);
	}
	free(chunks);
}
