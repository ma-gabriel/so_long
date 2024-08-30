/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:25:54 by geymat            #+#    #+#             */
/*   Updated: 2024/02/14 16:28:33 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

size_t	ft_bigstrlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

char	*ft_strjoin_free_first(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(s1);
	if (!s2)
		free(s1);
	if (!s2)
		return (NULL);
	len2 = ft_strlen(s2);
	res = (char *) malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		free(s1);
	if (!res)
		return (NULL);
	len1 = -1;
	while (s1[++len1])
		res[len1] = s1[len1];
	len2 = -1;
	while (s2[++len2])
		res[len1 + len2] = s2[len2];
	res[len1 + len2] = 0;
	free(s1);
	return (res);
}

int	argv_free(char **argv)
{
	size_t	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		free(argv[i++]);
	free(argv);
	return (1);
}
