/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:12:13 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/08 23:40:10 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *stack, t_action **actions)
{
	char	*name;
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return ;
	name = ft_strjoin("s", stack->name);
	if (!name)
		return ;
	first = stack->head;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	second->prev = first->prev;
	second->next = first;
	first->prev = second;
	stack->head = second;
	if (stack->size == 2)
		stack->tail = first;
	add_action(actions, name);
	free(name);
}

void	rotate(t_stack *stack, t_action **actions)
{
	t_node	*first;
	char	*name;

	if (!stack || stack->size < 2)
		return ;
	name = ft_strjoin("r", stack->name);
	if (!name)
		return ;
	first = stack->head;
	stack->head = first->next;
	stack->head->prev = NULL;
	first->prev = stack->tail;
	first->next = NULL;
	stack->tail->next = first;
	stack->tail = first;
	add_action(actions, name);
	free(name);
}

void	rrotate(t_stack *stack, t_action **actions)
{
	t_node	*last;
	char	*name;

	if (!stack || stack->size < 2)
		return ;
	name = ft_strjoin("rr", stack->name);
	if (!name)
		return ;
	last = stack->tail;
	stack->tail = last->prev;
	stack->tail->next = NULL;
	last->prev = NULL;
	last->next = stack->head;
	stack->head->prev = last;
	stack->head = last;
	add_action(actions, name);
	free(name);
}

void	push(t_stack *src, t_stack *dst, t_action **actions)
{
	t_node	*src_top;
	char	*name;

	if (!src || !dst || !src->size)
		return ;
	name = ft_strjoin("p", dst->name);
	if (!name)
		return ;
	src_top = src->head;
	src->head = src_top->next;
	if (src->head)
		src->head->prev = NULL;
	else
		src->tail = NULL;
	src->size--;
	if (!dst->head)
		dst->tail = src_top;
	src_top->next = dst->head;
	if (dst->head)
		dst->head->prev = src_top;
	dst->head = src_top;
	dst->size++;
	add_action(actions, name);
	free(name);
}

void	combined_operation(t_push_swap *ps, char *name)
{
	if (!ft_strncmp(name, "rr", 3))
	{
		rotate(ps->stack_a, &ps->actions);
		rotate(ps->stack_b, &ps->actions);
	}
	else if (!ft_strncmp(name, "rrr", 4))
	{
		rrotate(ps->stack_a, &ps->actions);
		rrotate(ps->stack_b, &ps->actions);
	}
	else if (!ft_strncmp(name, "ss", 3))
	{
		swap(ps->stack_a, &ps->actions);
		swap(ps->stack_b, &ps->actions);
	}
	else
		return ;
	optimize_rotations(&ps->actions);
}
