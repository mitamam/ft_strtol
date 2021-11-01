/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 14:22:19 by mmasuda           #+#    #+#             */
/*   Updated: 2021/11/01 11:54:49 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strtol.h>

void	intialize_args(t_args *args, const char *restrict str,
char **restrict endptr, int *base)
{
	args->str = str;
	args->endptr = endptr;
	args->base = base;
}

void	initialize_state(t_state *state, const t_args args)
{
	int	base;

	base = *args.base;
	state->number = 0;
	state->index = 0;
	state->negative = false;
	state->is_base_valid = (base == 0 || (base >= 2 && base <= 36));
	state->is_endptr_null = (args.endptr == NULL);
	state->is_string_empty = (args.str[0] == '\0');
}

t_bool	is_under_or_overflowing(const long long number,
const int store_number, const int base, const t_bool negative)
{
	long long	multipled_number;
	long		multiple;
	long		divide;

	multiple = number * base;
	divide = multiple / base;
	if (divide != number)
		return (true);
	multipled_number = number * base;
	if (negative)
	{
		multipled_number *= -1;
		if (multipled_number < (LONG_MIN + store_number))
			return (true);
	}
	else
	{
		if (multipled_number > (LONG_MAX - store_number))
			return (true);
	}
	return (false);
}

t_bool	is_arguments_valid(t_state *state, t_args *args)
{
	if (args->str[0] == '-')
	{
		state->negative = true;
		state->index++;
	}
	else if (state->is_base_valid == false || state->is_string_empty == true)
	{
		set_errno(state, args, EINVAL);
		return (false);
	}
	return (true);
}

t_bool	is_store_number_valid(t_state *state, t_args *args)
{
	state->store_number = convert_char_to_integer(args->str[state->index]);
	if (state->store_number == -1 || state->store_number >= *args->base)
	{
		if (state->index == 0)
			set_errno(state, args, EINVAL);
		else
			set_errno(state, args, 0);
		return (false);
	}
	return (true);
}
