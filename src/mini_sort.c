/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:35:40 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/01 00:58:04 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack *stack, t_action **actions)
{
	if (stack->head->data > stack->head->next->data)
		swap(stack, actions);
}

void	sort_three(t_stack *stack, t_action **actions)
{
	int	a;
	int	b;
	int	c;

	a = stack->head->data;
	b = stack->head->next->data;
	c = stack->head->next->next->data;
	if (a < b && b < c)
		return ;
	if (a > b && a < c)
		swap(stack, actions);
	else if (a > b && b > c)
	{
		swap(stack, actions);
		rrotate(stack, actions);
	}
	else if (a > c && b < c)
		rotate(stack, actions);
	else if (a < c && b > c)
	{
		swap(stack, actions);
		rotate(stack, actions);
	}
	else
		rrotate(stack, actions);
}

void	sort_four_or_five(t_push_swap *ps)
{
	int	min_pos;

	while (ps->stack_a->size > 3)
	{
		min_pos = find_index(ps->stack_a, stack_min(ps->stack_a));
		single_rotation(ps->stack_a, min_pos, &ps->actions);
		push(ps->stack_a, ps->stack_b, &ps->actions);
	}
	sort_three(ps->stack_a, &ps->actions);
	while (ps->stack_b->size > 0)
		push(ps->stack_b, ps->stack_a, &ps->actions);
}

void	mini_sort(t_push_swap *ps)
{
	if (ps->stack_a->size == 2)
		sort_two(ps->stack_a, &ps->actions);
	else if (ps->stack_a->size == 3)
		sort_three(ps->stack_a, &ps->actions);
	else if (ps->stack_a->size == 4 || ps->stack_a->size == 5)
		sort_four_or_five(ps);
	print_actions(ps->actions);
}
