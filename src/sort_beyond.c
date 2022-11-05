/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_beyond.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:33:28 by julmuntz          #+#    #+#             */
/*   Updated: 2022/11/05 15:33:00 by julmuntz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*sort_to_a(int pos, t_stack **a, t_stack **b)
{
	int	i;

	i = 1;
	while (i++ < pos)
		rb(b);
	pa(a, b);
	while (--i > 1)
		rrb(b);
	return (*b);
}

static	t_stack	*sort_to_b(t_data *data, t_stack **a, t_stack **b)
{
	int top;
	int bottom;
	t_stack *node;
	t_stack *r_node;

	top = 1;
	bottom = 1;
	node = stackcopy(*a);
	get_index(&node, stacksize(*a));
	r_node = stackcopy(*a);
	stackrev(r_node);
	get_index(&r_node, stacksize(*a));
	while (node)
	{
		if (node->index >= 1
			&& node->index <= data->quarter)
			break ;
		node = node->next;
		top++;
	}
	while(r_node)
	{
		if (r_node->index >= 1
			&& r_node->index <= data->quarter)
			break ;
		r_node = r_node->next;
		bottom++;
	}
	if (top == bottom)
	{
		bottom *= 2;
		while (top > 1)
		{
			if(top == 1)
			{
				while (bottom >= 1)
				{
					rra(a);
					bottom--;
				}
				pb(a, b);
				continue ;
			}
			ra(a);
			top--;
		}
		return (*a);
	}
	else if (top < bottom)
	{
		while (top > 1)
		{
			ra(a);
			top--;
		}
		return (*a);
	}
	else if (bottom < top)
	{
		while (bottom >= 1)
		{
			rra(a);
			bottom--;
		}
		return (*a);
	}
	return (0);
}

static void	get_chunks(t_stack **a, t_stack **b)
{
	t_data data;
	t_stack	*node;

	data.quarter = ft_sqrt(stacksize(*a));
	data.chunk = data.quarter;
	node = *a;
	while (node)
	{
		data.pos = node->pos;
		data.size = stacksize(*a);
		if (data.count_chunk == data.chunk)
			data.chunk += data.quarter;
		else if ((node->index >= (data.chunk - data.quarter + 1)
				&& node->index <= data.chunk))
		{
			node = sort_to_b(&data, a, b);
			pb(a, b);
		}
		else
			node = node->next;
	}
}

static void	*max1_or_max2(t_stack *node, t_data *data,
	t_stack **a, t_stack **b)
{
	if (data->sa_needed == FALSE && data->index == data->max_index)
		node = sort_to_a(node->pos, a, b);
	else if (data->sa_needed == TBD && data->index == data->sec_max_index)
	{
		node = sort_to_a(node->pos, a, b);
		data->sa_needed = TRUE;
	}
	else if (data->sa_needed == TRUE && data->index == data->max_index)
	{
		node = sort_to_a(node->pos, a, b);
		sa(a);
		data->sa_needed = FALSE;
	}
	else if (data->sa_needed == FALSE && data->index == data->sec_max_index)
	{
		node = sort_to_a(node->pos, a, b);
		data->sa_needed = TRUE;
	}
	else
		node = (node)->next;
	return (node);
}

void	sort_beyond(t_stack **a, t_stack **b)
{
	t_stack	*node;
	t_data	data;

	get_chunks(a, b);
	node = *b;
	data.sa_needed = TBD;
	while (node)
	{
		data.index = node->index;
		data.size = stacksize(*b);
		data.max_index = get_max_index(b);
		data.sec_max_index = get_2ndmax_index(b);
		node = max1_or_max2(node, &data, a, b);
	}
	stackclear(b);
}
