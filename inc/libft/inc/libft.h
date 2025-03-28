/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:24:17 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/19 00:53:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include "ft_printf.h"
//# include "get_next_line.h"
# include "get_next_line_bonus.h"

//Estructura para la lista enlazada
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//List operations
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstpiter(t_list *lst, void (*f)(void *), void *param);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Conversions
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_itoa_base(unsigned long value, int base);
char	*ft_itoa_baseup(unsigned long value, int base);
double	ft_atof(char *str);

// Checks
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_skip_space_sign(char *str, int *is_neg);
int		ft_isnumeric(const char *str);

// Memory manipulation
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

// String operations
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_free_arrays(char **array);

// Character conversions
int		ft_toupper(int c);
int		ft_tolower(int c);

//Input/Output operations
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putptr_fd(void *ptr, int fd);
int		ft_putunsigned_fd(unsigned int n, int fd);
int		ft_puthexlo_fd(unsigned int n, int fd);
int		ft_puthexup_fd(unsigned int n, int fd);

//Comun_Course fucntions
int		ft_printf(const char *str, ...);
char	*get_next_line(int fd);

#endif
