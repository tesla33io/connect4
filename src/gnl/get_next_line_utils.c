/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:00:38 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 13:00:58 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	ft_bzero_gnl(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc_gnl(size_t nmem, size_t size)
{
	char	*content;

	content = malloc(size * nmem);
	if (!content)
		return (NULL);
	ft_bzero_gnl(content, size * nmem);
	return (content);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*content;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	content = malloc(sizeof(char) * (sizetotal + 1));
	if (!content || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		content[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		content[i] = s2[j];
		i++;
		j++;
	}
	content[sizetotal] = 0;
	return (content);
}

size_t	ft_strlen_gnl(const char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *string, int c)
{
	char	*str;

	str = (char *)string;
	while (*str != c && *str != 0)
		str++;
	if (*str == c)
		return (str);
	else
		return (NULL);
}
