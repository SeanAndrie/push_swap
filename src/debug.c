/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:41:33 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/28 02:49:58 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_stack *stack)
{
	t_node	*curr;

	if (!stack || !stack->head)
	{
		ft_printf("%s (%d) : NULL\n", stack->name, stack->size);
		return ;
	}
	curr = stack->head;
	ft_printf("%s (%d) : ", stack->name, stack->size);
	while (curr)
	{
		ft_printf("%d <-> ", curr->data);
		curr = curr->next;
	}
	ft_printf("NULL\n");
}

void	print_actions(t_action *head)
{
	t_action	*curr;

	curr = head;
	while (curr)
	{
		ft_printf("%s\n", curr->name);
		curr = curr->next;
	}
}
