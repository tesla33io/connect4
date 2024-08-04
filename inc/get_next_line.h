/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:00:39 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 12:59:40 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif // !BUFFER_SIZE

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }				t_list;

char		*get_next_line(int fd);
void		*ft_calloc_gnl(size_t nmem, size_t size);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
size_t		ft_strlen_gnl(const char *string);
char		*ft_strchr_gnl(const char *string, int c);

#endif
