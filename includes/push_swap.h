/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgadinga <sgadinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:32:19 by sgadinga          #+#    #+#             */
/*   Updated: 2025/04/11 16:50:04 by sgadinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/includes/libft.h"
# include <limits.h>
# include <stdlib.h>

# define HASH_SIZE 1024

typedef struct s_candidate
{
	int					value;
	int					index;
}						t_candidate;

typedef struct s_rotation
{
	int					index;
	int					n_rotation;
	int					direction;
}						t_rotation;

typedef struct s_hashmap
{
	int					key;
	int					value;
}						t_hashmap;

typedef struct s_node
{
	int					data;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_stack
{
	t_node				*head;
	t_node				*tail;
	int					size;
	char				*name;
}						t_stack;

typedef struct s_action
{
	char				*name;
	struct s_action		*next;
}						t_action;

typedef struct s_push_swap
{
	struct s_stack		*stack_a;
	struct s_stack		*stack_b;
	struct s_hashmap	*lookup[HASH_SIZE];
	struct s_action		*actions;
}						t_push_swap;

// Trial Sort
void					trial_sort(t_push_swap *ps, int margin);
void					sort(t_push_swap *ps, int n_chunks);

// Mini Sort
void					mini_sort(t_push_swap *ps);
void					sort_three(t_stack *stack, t_action **actions);

// Push Swap Initialization
t_push_swap				*create_push_swap(int ac, char **av);
t_push_swap				*copy_init_state(t_push_swap *ps);
t_push_swap				*push_swap_init(void);
void					*free_push_swap(t_push_swap *ps);
void					*full_free(char **tokens, t_stack *stack);

// Push Swap Algorithm
void					chunk_partitions(t_push_swap *ps, int n_chunks);
void					merge_chunks(t_push_swap *ps);

// Push Swap Algorithm Utilities
t_rotation				find_rotations_to_top(t_stack *stack, int index);
int						calculate_cost(t_stack *stack_a, t_stack *stack_b,
							int value);
int						find_best_candidate(t_stack *stack_a, t_stack *stack_b);
int						find_insertion_point(t_stack *stack, int value);
int						find_chunk_median(t_stack *stack, int chunk_size);

// Stack Initialization
t_stack					*create_stack(char **tokens, char *stack_name);
char					**create_tokens(int ac, char **av);
t_stack					*stack_init(void);
void					*free_stack(t_stack *stack);
void					*free_tokens(char **tokens);

// Stack Operations
void					swap(t_stack *stack, t_action **actions);
void					rotate(t_stack *stack, t_action **actions);
void					rrotate(t_stack *stack, t_action **actions);
void					push(t_stack *src, t_stack *dst, t_action **actions);
void					combined_operation(t_push_swap *ps, char *name);

// Stack Validation
int						has_duplicates(t_stack *stack);
int						is_valid_int(char *token);
int						is_sorted(t_stack *stack);
void					error(void);

// Stack Utilities
int						find_index(t_stack *stack, int value);
int						stack_min(t_stack *stack);
int						stack_max(t_stack *stack);
t_stack					*stack_copy(t_stack *stack);

// Node Operations
t_node					*create_node(int data);
void					append(t_stack *stack, t_node *node);
void					prepend(t_stack *stack, t_node *node);
void					free_list(t_node *node);

// Action Operations
t_action				*create_action(char *name);
void					add_action(t_action **head, char *name);
void					free_actions(t_action *head);
int						count_actions(t_action *head);
t_action				*copy_actions(t_action *src);

// Action Optimization
void					optimize_rotations(t_action **head);

// Normalization
void					stack_to_sorted_hashmap(t_stack *stack,
							t_hashmap **map);
void					stack_normalize(t_stack *stack, t_hashmap **map);
void					quick_sort(int *arr, int low, int high);

// Hashmap Operations
int						hash(int key);
void					free_map(t_hashmap **map);
void					insert(t_hashmap **map, int key, int value);
t_hashmap				*search(t_hashmap **map, int key);

// Rotations
void					single_rotation(t_stack *stack, int index,
							t_action **actions);
void					combined_rotation(t_push_swap *ps, t_rotation *rot_a,
							t_rotation *rot_b);

// Other Utilities
int						ft_max(int a, int b);
int						ft_min(int a, int b);
int						ft_atoi_safe(const char *s, int *overflow);
void					ft_swap(int *a, int *b);
int						*stack_to_arr(t_stack *stack);

// Debugging
void					print_stack(t_stack *stack);
void					print_actions(t_action *head);

#endif