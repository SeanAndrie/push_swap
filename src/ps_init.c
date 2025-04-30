/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:57:12 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/30 17:18:57 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	*full_free(char **tokens, t_stack *stack)
{
	if (tokens)
		free_tokens(tokens);
	if (stack)
		free_stack(stack);
	return (NULL);
}

void	*free_push_swap(t_push_swap *ps)
{
	if (!ps)
		return (NULL);
	if (ps->stack_a)
		free_stack(ps->stack_a);
	if (ps->stack_b)
		free_stack(ps->stack_b);
	if (ps->actions)
		free_actions(ps->actions);
	free_map(ps->lookup);
	free(ps);
	return (NULL);
}

t_push_swap	*push_swap_init(void)
{
	int			i;
	t_push_swap	*ps;

	ps = malloc(sizeof(t_push_swap));
	if (!ps)
		return (NULL);
	ps->stack_a = NULL;
	ps->stack_b = NULL;
	ps->actions = NULL;
	i = 0;
	while (i < HASH_SIZE)
		ps->lookup[i++] = NULL;
	return (ps);
}

t_push_swap	*copy_init_state(t_push_swap *ps)
{
	t_push_swap	*copy;

	copy = push_swap_init();
	if (!copy)
		return (NULL);
	copy->stack_a = stack_copy(ps->stack_a);
	if (!copy->stack_a)
	{
		free_push_swap(copy);
		return (NULL);
	}
	copy->stack_b = stack_init();
	if (!copy->stack_b)
	{
		free_push_swap(copy);
		return (NULL);
	}
	copy->stack_b->name = "b";
	return (copy);
}

t_push_swap	*create_push_swap(int ac, char **av)
{
	t_push_swap	*ps;
	char		**tokens;

	ps = push_swap_init();
	tokens = create_tokens(ac, av);
	if (!tokens)
		return (free_push_swap(ps));
	ps->stack_a = create_stack(tokens, "a");
	if (!ps->stack_a)
	{
		free_tokens(tokens);
		return (free_push_swap(ps));
	}
	ps->stack_b = stack_init();
	if (!ps->stack_b)
	{
		full_free(tokens, ps->stack_a);
		return (free_push_swap(ps));
	}
	ps->stack_b->name = "b";
	free_tokens(tokens);
	stack_to_sorted_hashmap(ps->stack_a, ps->lookup);
	stack_normalize(ps->stack_a, ps->lookup);
	return (ps);
}
