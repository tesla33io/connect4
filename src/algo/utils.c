/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:24:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/02 19:26:27 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"

int	on_crash_code(char *msg, int code)
{
	ft_putendl_fd(msg, 2);
	gc_free_gc(0);
	return (code);
}

void	*on_crash_null(char *msg)
{
	ft_putendl_fd(msg, 2);
	gc_free_gc(0);
	return (NULL);
}
