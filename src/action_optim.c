/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_optim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:26:59 by sgadinga          #+#    #+#             */
/*   Updated: 2025/03/28 01:27:45 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	combine_rotations(t_action **head, t_action *current,
		t_action *adjacent, char *name)
{
	if (!current || !adjacent || !name)
		return ;
	free(current->name);
	current->name = ft_strdup(name);
	if (!current->name)
		return ;
	current->next = adjacent->next;
	free(adjacent->name);
	free(adjacent);
	if (current == *head)
		*head = current;
}

void	optimize_rotations(t_action **head)
{
	t_action	*current;
	t_action	*adjacent;

	current = *head;
	while (current && current->next)
	{
		adjacent = current->next;
		if ((!ft_strncmp(current->name, "ra", 3) && !ft_strncmp(adjacent->name,
					"rb", 3)) || (!ft_strncmp(current->name, "rb", 3)
				&& !ft_strncmp(adjacent->name, "ra", 3)))
			combine_rotations(head, current, adjacent, "rr");
		else if ((!ft_strncmp(current->name, "rra", 4)
				&& !ft_strncmp(adjacent->name, "rrb", 4))
			|| (!ft_strncmp(current->name, "rrb", 4)
				&& !ft_strncmp(adjacent->name, "rra", 4)))
			combine_rotations(head, current, adjacent, "rrr");
		else if ((!ft_strncmp(current->name, "sa", 3)
				&& !ft_strncmp(adjacent->name, "sb", 3))
			|| (!ft_strncmp(current->name, "sb", 3)
				&& !ft_strncmp(adjacent->name, "sa", 3)))
			combine_rotations(head, current, adjacent, "ss");
		else
			current = current->next;
	}
}
