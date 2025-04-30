/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:43:13 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/11 16:50:13 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_push_swap	*ps;

	if (ac < 2)
		return (0);
	ps = create_push_swap(ac, av);
	if (!ps)
		error();
	if (is_sorted(ps->stack_a))
	{
		free_push_swap(ps);
		return (0);
	}
	if (ps->stack_a->size <= 5)
		mini_sort(ps);
	else
		trial_sort(ps, 8);
	free_push_swap(ps);
	return (0);
}
