/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:17:40 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/30 17:14:34 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_index(t_stack *stack, int value)
{
	t_node	*curr;
	int		index;

	index = 0;
	if (!stack || !stack->head)
		return (-1);
	if (stack->head->data == value)
		return (0);
	if (stack->tail->data == value)
		return (stack->size - 1);
	curr = stack->head->next;
	while (curr && curr != stack->head)
	{
		if (curr->data == value)
			return (index + 1);
		curr = curr->next;
		index++;
	}
	return (-1);
}

static t_stack	*copy_stack_contents(t_stack *src, t_stack *dst)
{
	t_node	*curr;
	t_node	*node;

	curr = src->head;
	while (curr)
	{
		node = create_node(curr->data);
		if (!node)
			return (free_stack(dst));
		append(dst, node);
		dst->size++;
		curr = curr->next;
	}
	return (dst);
}

t_stack	*stack_copy(t_stack *stack)
{
	t_stack	*copy;

	if (!stack)
		return (NULL);
	copy = stack_init();
	if (!copy)
		return (NULL);
	if (stack->name)
	{
		copy->name = ft_strdup(stack->name);
		if (!copy->name)
		{
			free(copy);
			return (NULL);
		}
	}
	copy = copy_stack_contents(stack, copy);
	if (!copy)
		return (NULL);
	return (copy);
}

int	stack_max(t_stack *stack)
{
	int		max;
	t_node	*curr;

	max = INT_MIN;
	curr = stack->head;
	while (curr)
	{
		if (curr->data > max)
			max = curr->data;
		curr = curr->next;
	}
	return (max);
}

int	stack_min(t_stack *stack)
{
	int		min;
	t_node	*curr;

	min = INT_MAX;
	curr = stack->head;
	while (curr)
	{
		if (curr->data < min)
			min = curr->data;
		curr = curr->next;
	}
	return (min);
}
