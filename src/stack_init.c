/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:44:26 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/08 23:33:55 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	*free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (NULL);
}

void	*free_stack(t_stack *stack)
{
	if (!stack)
		return (NULL);
	free_list(stack->head);
	stack->head = NULL;
	stack->tail = NULL;
	free(stack);
	return (NULL);
}

char	**create_tokens(int ac, char **av)
{
	char	**tokens;
	int		i;

	tokens = NULL;
	if (ac == 2)
		tokens = ft_split(av[1], ' ');
	else if (ac > 2)
	{
		tokens = ft_calloc(ac + 1, sizeof(char *));
		if (!tokens)
			return (NULL);
		i = 0;
		while (i < ac - 1)
		{
			tokens[i] = ft_strdup(av[i + 1]);
			if (!tokens[i])
				return (free_tokens(tokens));
			i++;
		}
	}
	return (tokens);
}

t_stack	*stack_init(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
	stack->name = NULL;
	return (stack);
}

t_stack	*create_stack(char **tokens, char *stack_name)
{
	int		n;
	t_node	*node;
	t_stack	*stack;
	int		overflow;

	stack = stack_init();
	if (!stack)
		return (NULL);
	stack->name = stack_name;
	while (*tokens)
	{
		n = ft_atoi_safe(*tokens, &overflow);
		if (overflow || !is_valid_int(*tokens))
			return (free_stack(stack));
		node = create_node(n);
		if (!node)
			return (free_stack(stack));
		append(stack, node);
		stack->size++;
		tokens++;
	}
	if (has_duplicates(stack))
		return (free_stack(stack));
	return (stack);
}
