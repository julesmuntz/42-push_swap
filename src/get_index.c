/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:25:57 by julmuntz          #+#    #+#             */
/*   Updated: 2022/10/03 20:39:41 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_pos(t_stack **ptr)
{
	t_stack	*current;
	int		count;

	current = *ptr;
	count = 0;
	while (current)
	{
		current->pos = count;
		current = current->next;
		count++;
	}
}

int	min_value_pos(t_stack **ptr)
{
	t_stack	*current;
	int		min_value_pos;
	int		min_value_index;

	current = *ptr;
	min_value_index = INT_MAX;
	get_pos(ptr);
	min_value_pos = current->pos;
	while (current)
	{
		if (current->index < min_value_index)
		{
			min_value_index = current->index;
			min_value_pos = current->pos;
		}
		current = current->next;
	}
	return (min_value_pos + 1);
}

void	get_index(t_stack *node, int size)
{
	t_stack	*top;
	t_stack	*current;
	int		value;

	top = NULL;
	while (size > 0)
	{
		current = node;
		value = INT_MIN;
		while (current)
		{
			if (current->value == INT_MIN && current->index == 0)
				current->index = 1;
			if (current->value > value && current->index == 0)
			{
				value = current->value;
				top = current;
				current = node;
			}
			current = current->next;
		}
		if (top)
			top->index = size;
		size--;
	}
}