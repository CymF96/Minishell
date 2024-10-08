/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:37:29 by mcoskune          #+#    #+#             */
/*   Updated: 2024/07/15 19:35:40 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_rows(const char *str, char del)
{
	int	rows;

	rows = 0;
	if (*str == '\0')
		return (0);
	if (*str != del)
	{
		rows++;
		str++;
	}
	while (*str)
	{
		if (*str != del && *(str - 1) == del)
			rows++;
		str++;
	}
	return (rows);
}

static size_t	row_len(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static void	*safe_malloc(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	int		nb_rows;
	char	**strings;
	int		i;
	size_t	len;

	if (s == NULL)
		return (NULL);
	nb_rows = count_rows(s, c);
	strings = (char **)malloc((nb_rows + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	strings[nb_rows] = NULL;
	i = 0;
	while (i < nb_rows)
	{
		while (*s == c && s != NULL)
			s++;
		len = row_len(s, c);
		strings[i] = safe_malloc(len);
		ft_strlcpy(strings[i], s, len + 1);
		s += len;
		i++;
	}
	return (strings);
}

// static int	ft_word_count(const char *s, char c)
// {
// 	int	wc;
// 	int	i;

// 	wc = 0;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (i == 0 && s[i] != c)
// 			wc++;
// 		if (i > 0 && s[i] != c && s[i - 1] == c)
// 			wc++;
// 		i++;
// 	}
// 	return (wc);
// }

// static char	**ft_malloc_str(char **str, const char *s, char c)
// {
// 	int	count;
// 	int	i;
// 	int	j;

// 	count = 0;
// 	i = 0;
// 	j = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != c)
// 			count++;
// 		if ((s[i] == c && i > 0 && s[i - 1] != c)
// 			|| (s[i] != c && s[i + 1] == '\0'))
// 		{
// 			str[j] = malloc((count + 1) * sizeof(char));
// 			if (!str)
// 				return (NULL);
// 			count = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

// static char	**ft_cpy_str(char **str, const char *s, char c)
// {
// 	int	x;
// 	int	y;
// 	int	i;

// 	x = 0;
// 	y = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 			str[x][y++] = s[i];
// 		if (s[i] != c && s[i + 1] == '\0')
// 			str[x][y] = '\0';
// 		if (s[i] == c && i > 0 && s[i - 1] != c)
// 		{
// 			str[x][y] = '\0';
// 			x++;
// 			y = 0;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

// static char	**ft_memclean(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		str[i] = NULL;
// 		i++;
// 	}
// 	free(str);
// 	return (NULL);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**str;
// 	int		wc;

// 	if (!s || !*s)
// 	{
// 		return (NULL);
// 	}
// 	wc = ft_word_count(s, c);
// 	str = malloc(sizeof(*str) * (wc + 1));
// 	if (!str)
// 		return (NULL);
// 	if (ft_malloc_str(str, s, c))
// 	{
// 		ft_cpy_str(str, s, c);
// 		str[wc] = NULL;
// 	}
// 	else
// 		str = ft_memclean(str);
// 	return (str);
// }
