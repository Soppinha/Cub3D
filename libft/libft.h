/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <lcosta-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:42:18 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/08/13 22:55:55 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  LIBFT_H
# define LIBFT_H

# include<stdlib.h>
# include<unistd.h>
# include<stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_strlen(const char *str);
int				ft_tolower(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_lstsize(t_list *lst);
int				ft_printf(const char	*format, ...);
int				ft_putchar(char c);
int				ft_putstr(char *s);
int				ft_putnbr(int n);
int				ft_putunbr(unsigned int n);
int				ft_puthex(unsigned long n, int uppercase);
int				ft_putptr(void	*ptr);

char			*ft_itoa(int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const	*s1, char const	*s2);
char			*ft_strmapi(char const	*s, char (*f)(unsigned int, char));

void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list	*lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

unsigned int	ft_strlcpy(char	*dest, const char	*src, unsigned int size);
unsigned int	ft_strlcat(char	*dest, const char	*src, unsigned int size);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

char *get_next_line(int fd);
size_t ft_strlen_gnl(const char *s);
char *ft_strchr_gnl(const char *s, int c);
char *ft_strdup_gnl(const char *s);
char *ft_strjoin_gnl(char *s1, char *s2);
char *st_substr_gnl(char *s, unsigned int start, size_t len);
void *ft_memcpy_gnl(void *dest, const void *src, size_t n);
void *ft_memmove_gnl(void *dest, const void *src, size_t n);

#endif
