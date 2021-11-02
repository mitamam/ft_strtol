/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:15:53 by mmasuda           #+#    #+#             */
/*   Updated: 2021/11/01 11:54:54 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_strtol.h>

void	set_errno(t_state *state, t_args *args, const int arg_errno)
{
	size_t	index;

	index = state->index;
	if (arg_errno == EINVAL)
		errno = EINVAL;
	else if (arg_errno == ERANGE)
	{
		errno = ERANGE;
		index = ft_strlen(args->str);
	}
	if (state->is_endptr_null == false)
	{
		if (*args->base == 16 && args->str[0] != '0')
			index--;
		*args->endptr = (char *)&args->str[index];
	}
	if (state->negative)
		state->number *= -1;
}

int	convert_char_to_integer(const char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isalpha(c))
		return ((ft_tolower(c) - 'a') + 10);
	return (-1);
}

void	set_when_base_is_zero(t_state *state, t_args *args)
{
	if (*args->base == 0)
	{
		if (args->str[0] == '0')
		{
			if (args->str[1] == 'x' || args->str[1] == 'X')
			{
				*args->base = 16;
				state->index += 1;
			}
			else
				*args->base = 8;
			state->index += 1;
		}
		else
			*args->base = 10;
	}
}

void	finished_convert(t_state *state, t_args *args)
{
	if (state->negative)
		state->number *= -1;
	if (state->is_endptr_null == false)
		*args->endptr = (char *)&args->str[state->index];
}

long	ft_strtol(const char *restrict str, char **restrict endptr, int base)
{
	t_state		state;
	t_args		args;

	intialize_args(&args, str, endptr, &base);
	initialize_state(&state, args);
	if (is_arguments_valid(&state, &args) == false)
		return (0);
	set_when_base_is_zero(&state, &args);
	while (str[state.index] != '\0')
	{
		if (is_store_number_valid(&state, &args) == false)
			return (state.number);
		if (is_under_or_overflowing(state.number,
				state.store_number, base, state.negative))
		{
			set_errno(&state, &args, ERANGE);
			if (state.negative)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		state.number = (state.number * base) + state.store_number;
		state.index++;
	}
	finished_convert(&state, &args);
	return (state.number);
}
