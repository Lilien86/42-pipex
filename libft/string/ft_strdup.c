/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:57:17 by lauger            #+#    #+#             */
/*   Updated: 2024/02/09 13:33:38 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (src == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	if (dest == NULL)
		return (0);
	while (src[i])
	{
		dest[i] = (unsigned char)src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
