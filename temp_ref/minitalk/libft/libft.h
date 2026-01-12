/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:46:40 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:41:14 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// Libraries for standard definitions such as size_t and uintptr_t
# include <stdlib.h>
# include <stdint.h>

// GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define MAX_FD 1024

// printf
# define HEX_B "0123456789ABCDEF"
# define HEX "0123456789abcdef"
# define HEX_LEN 16
# define DEC "0123456789"
# define FLAGS_CHECK "-+ 0#"
# define PRECISION_CHECK "."
# define TYPE_CHECK "cspdiuxXb%%"

// GNL
char	*get_next_line(int fd);

// printf
typedef struct s_flags
{
	int	minus;
	int	plus;
	int	space;
	int	zero;
	int	hash;
}	t_flags;

typedef struct s_prec
{
	int	dot;
	int	len;
}	t_prec;

typedef struct s_spec
{
	t_flags	flags;
	int		width;
	t_prec	prec;
	char	type;
	int		zprec;
}	t_spec;

int		ft_printf(const char *format, ...);
int		ft_is_conv(const char *format, int *move, t_spec	*conv);
void	ft_padding(int n, int *p_count, char c);
int		ft_putchar_rv(char c);
void	ft_putchar_rvf(char c, t_spec *conv, int *p_count);
void	ft_putstr_rvf(char *str, t_spec *conv, int *p_count);
int		ft_unblen_base(uintptr_t nb, uintptr_t base_len);
void	ft_putunb_base(uintptr_t nb, char *base, int *p_count);
void	ft_putptr_rvf(uintptr_t ptr, t_spec *conv, int *p_count);
void	ft_putuint_base_rvf(unsigned int nb, char *base, t_spec *conv,
			int *p_count);
void	ft_putint_base_rvf(int nb, char *base, t_spec *conv, int *p_count);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// extra
long	ft_atol(const char *nptr);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(int c);
int		ft_isallspaces(const char *str);
int		ft_isalldigits(const char *str);
void	ft_free_arr(char **arr);
int		ft_bitcount(int nbr);
int		ft_strstr_count(const char *str, const char *pattern);
int		ft_strdel(char **str, char *pattern);
int		ft_strrep(char **str, char *del, char *rep);

#endif