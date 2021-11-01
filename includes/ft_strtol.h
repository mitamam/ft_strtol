/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:16:07 by mmasuda           #+#    #+#             */
/*   Updated: 2021/11/01 12:17:59 by mmasuda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOL_H
# define FT_STRTOL_H

# include	<stdlib.h>
# include	<errno.h>
# include	<limits.h>

typedef enum e_bool { false, true }	t_bool;

typedef struct s_state
{
	long long	number;
	int			store_number;
	size_t		index;
	t_bool		negative;
	t_bool		is_endptr_null;
	t_bool		is_base_valid;
	t_bool		is_string_empty;
}				t_state;

typedef struct s_args
{
	const char	*restrict	str;
	char	**restrict		endptr;
	int						*base;
}				t_args;

/* ft_strtol.c */
long	ft_strtol(const char *restrict str, char **restrict endptr, int base);
void	finished_convert(t_state *state, t_args *args);
void	set_when_base_is_zero(t_state *state, t_args *args);
int		convert_char_to_integer(const char c);
void	set_errno(t_state *state, t_args *args, const int arg_errno);

/* ft_strtol_utils.c */
t_bool	is_store_number_valid(t_state *state, t_args *args);
t_bool	is_arguments_valid(t_state *state, t_args *args);
t_bool	is_under_or_overflowing(const long long number,
			const int store_number, const int base, const t_bool negative);
void	initialize_state(t_state *state, const t_args args);
void	intialize_args(t_args *args, const char *restrict str,
			char **restrict endptr, int *base);

/* ft_strtol_libft.c */
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_tolower(int c);

#endif
