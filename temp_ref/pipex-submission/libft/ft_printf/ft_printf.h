/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:29:36 by mnussler          #+#    #+#             */
/*   Updated: 2025/07/15 01:29:39 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

# define HEX_LOWER_PREFIX "0x"
# define HEX_UPPER_PREFIX "0X"

# define STRING_NULL "(null)"
# define POINTER_NULL "(nil)"

# define ALLOWED_FORMAT_SPECIFIERS "cspdiuxX%"

# define DECIMAL_BASE "0123456789"
# define HEX_LOWER_BASE "0123456789abcdef"
# define HEX_UPPER_BASE "0123456789ABCDEF"

typedef struct s_opts
{
	int	left_align;
	int	zero_pad;
	int	plus_sign;
	int	space_prefix;
	int	hash_prefix;
	int	width;
	int	precision;
	int	has_precision;
}		t_opts;

typedef struct s_num_opts
{
	int				left_align;
	int				content_len;
	int				zero_pad;
	int				width_pad;
	int				has_precision;
	int				precision_pad;
	int				prefix_len;
	char			*prefix_str;
	size_t			number;
	char			*base;
}					t_num_opts;

/**
 * @brief Produces output according to a format string and writes to stdout.
 *
 * Supports the following conversion specifiers:
 *
 * - %c: single character
 *
 * - %s: c-style string of characters
 *
 * - %p: pointer address in hexadecimal format
 *
 * - %d: signed decimal integer (base 10)
 *
 * - %i: signed integer (base 10)
 *
 * - %u: unsigned decimal integer (base 10)
 *
 * - %x: unsigned hexadecimal integer (lowercase) (base 16)
 *
 * - %X: unsigned hexadecimal integer (uppercase) (base 16)
 *
 * - %%: literal percent sign
 *
 * Supports the following options:
 *
 * - flags: -, 0, +, space, # (can appear in any order/combination)
 *
 * - width: Numeric field width (comes after flags)
 *
 * - precision: .precision (comes after width)
 *
 * @param format The format string containing conversion specifiers.
 * @param ... Variable arguments corresponding to conversion specifiers.
 * @return The number of characters printed (excluding null terminator),
 * or -1 if an error occurs.
 */
int		ft_printf(const char *format, ...);

/**
 * @brief Parses format specifier options from a format string starting at '%'.
 *
 * Parses according to C standard format:
	% [flags] [width] [.precision] specifier
 *
 * - Flags: -, 0, +, space, # (can appear in any order/combination)
 *
 * - Width: Numeric field width (comes after flags)
 *
 * - Precision: .precision (comes after width)
 *
 * - Specifier: Conversion type (d, s, x, etc.) - must be valid
 *
 * @param format The format string.
 * @param pos Pointer to the current position (starting at '%').
 * @param opts The options structure to populate.
 * @return The number of characters parsed, or -1 on error.
 */
int		ft_parse_format_opts(const char *format, int *pos, t_opts *opts);

// ---------------------------------------------------------------------
//  Functions for printing formatted output
// ---------------------------------------------------------------------

/**
 * @brief Prints a single character.
 * @param c The character to print.
 * @param opts The opts structure containing formatting opts.
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_char(char c, t_opts *opts);

/**
 * @brief Prints a string.
 * @param str The string to print.
 * @param opts The opts structure containing formatting opts.
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_str(char *str, t_opts *opts);

/**
 * @brief Prints a signed decimal integer.
 * @param n The integer to print.
 * @param opts The opts structure containing formatting opts.
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_nbr(int n, t_opts *opts);

/**
 * @brief Prints an unsigned decimal integer.
 * @param n The integer to print.
 * @param opts The opts structure containing formatting opts.
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_unbr(unsigned int n, t_opts *opts);

/**
 * @brief Prints a hexadecimal integer.
 * @param n The integer to print.
 * @param opts The opts structure containing formatting opts.
 * @param c The character indicating the base (x or X).
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_hex(unsigned int n, t_opts *opts, char c);

/**
 * @brief Prints a pointer address.
 * @param ptr The pointer to print.
 * @param opts The opts structure containing formatting opts.
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_ptr(void *ptr, t_opts *opts);

/**
 * @brief Prints an unsigned number with formatting options.
 * @param opts The opts structure containing formatting opts.
 * @param prefix_str The prefix string to print.
 * @param n The unsigned number to print.
 * @param base The base to use for the output.
 * @return The number of characters written, or -1 on error.
 */
int		ft_printf_unbr_util(t_opts *opts, char *prefix_str, size_t n,
			char *base);

// ---------------------------------------------------------------------
//  Helper functions to output to stdout
// ---------------------------------------------------------------------

/**
 * @brief Outputs padding characters to stdout.
 * @param count The number of padding characters to print.
 * @param pad_char The character to use for padding.
 * @return The number of characters printed, or -1 on error.
 */
int		ft_putpad(int count, char pad_char);

/**
 * @brief Outputs a single character to stdout.
 * @param c The character to output.
 * @return The number of characters written (1), or -1 on error.
 */
int		ft_putchar(char c);

/**
 * @brief Outputs first `len` characters of a string to stdout.
 * @param s The string to output.
 * @param len The length of the string to output.
 * @return The number of characters written, or -1 on error.
 */
int		ft_putlstr(char *s, int len);

/**
 * @brief Outputs an unsigned decimal integer to stdout.
 * @param n The unsigned integer to output.
 * @param base The base to use for the output.
 * @return The number of characters written, or -1 on error.
 */
int		ft_putunbr(size_t n, char *base);

// ---------------------------------------------------------------------
//  General helper functions
// ---------------------------------------------------------------------

/**
 * @brief Calculates the length of a number in a given base.
 * @param n The number to calculate the length of.
 * @param base The base to use for the calculation.
 * @return The length of the number in the given base.
 */
int		ft_unsigned_numlen(size_t n, int base);

/**
 * @brief Calculates the maximum of two integers.
 * @param a The first integer.
 * @param b The second integer.
 * @return The maximum of the two integers.
 */
int		ft_max(int a, int b);

/**
 * @brief Calculates the minimum of two integers.
 * @param a The first integer.
 * @param b The second integer.
 * @return The minimum of the two integers.
 */
int		ft_min(int a, int b);

#endif
