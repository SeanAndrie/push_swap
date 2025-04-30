/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:52:09 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/11 16:50:31 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	parse_actions(t_push_swap *ps, char *action)
{
	if (!ft_strncmp(action, "sa\n", 3))
		swap(ps->stack_a, &ps->actions);
	else if (!ft_strncmp(action, "sb\n", 3))
		swap(ps->stack_b, &ps->actions);
	else if (!ft_strncmp(action, "ss\n", 3))
		combined_operation(ps, "ss");
	else if (!ft_strncmp(action, "pa\n", 3))
		push(ps->stack_b, ps->stack_a, &ps->actions);
	else if (!ft_strncmp(action, "pb\n", 3))
		push(ps->stack_a, ps->stack_b, &ps->actions);
	else if (!ft_strncmp(action, "ra\n", 3))
		rotate(ps->stack_a, &ps->actions);
	else if (!ft_strncmp(action, "rb\n", 3))
		rotate(ps->stack_b, &ps->actions);
	else if (!ft_strncmp(action, "rr\n", 3))
		combined_operation(ps, "rr");
	else if (!ft_strncmp(action, "rra\n", 4))
		rrotate(ps->stack_a, &ps->actions);
	else if (!ft_strncmp(action, "rrb\n", 4))
		rrotate(ps->stack_b, &ps->actions);
	else if (!ft_strncmp(action, "rrr\n", 4))
		combined_operation(ps, "rrr");
	else
		error();
}

void	checker(t_push_swap *ps)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		parse_actions(ps, line);
		free(line);
	}
}

int	main(int ac, char **av)
{
	t_push_swap	*ps;
	int			init_size;

	if (ac < 2)
		return (0);
	ps = create_push_swap(ac, av);
	if (!ps)
		error();
	init_size = ps->stack_a->size;
	checker(ps);
	if (is_sorted(ps->stack_a) && ps->stack_a->size == init_size)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free_push_swap(ps);
	return (0);
}
