/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:07:16 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/27 14:47:15 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	single_rotation(t_stack *stack, int index, t_action **actions)
{
	int	n_rotations;

	if (index > stack->size / 2)
	{
		n_rotations = stack->size - index;
		while (n_rotations--)
			rrotate(stack, actions);
	}
	else
	{
		n_rotations = index;
		while (n_rotations--)
			rotate(stack, actions);
	}
}

void	rotate_remain(t_stack *stack, t_rotation *rot, t_action **actions)
{
	if (rot->n_rotation > 0)
	{
		if (!rot->direction)
			while (rot->n_rotation-- > 0)
				rotate(stack, actions);
		else
			while (rot->n_rotation-- > 0)
				rrotate(stack, actions);
	}
}

void	combined_rotation(t_push_swap *ps, t_rotation *rot_a, t_rotation *rot_b)
{
	if (rot_a->direction == rot_b->direction)
	{
		while (rot_a->n_rotation > 0 && rot_b->n_rotation)
		{
			if (rot_a->direction == 0)
				combined_operation(ps, "rr");
			else
				combined_operation(ps, "rrr");
			rot_a->n_rotation--;
			rot_b->n_rotation--;
		}
	}
	rotate_remain(ps->stack_a, rot_a, &ps->actions);
	rotate_remain(ps->stack_b, rot_b, &ps->actions);
}
