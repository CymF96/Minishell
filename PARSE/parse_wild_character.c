/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wild_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:10:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/09 16:28:28 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_exp(t_msh *msh, int *i)
{
	int		z;
	char	*str;

	while (*i > -1 && msh->input[*i] != ' ' && msh->input[*i] != '\t')
		(*i)--;
	(*i)++;
	z = *i;
	while (msh->input[z] != ' ' && msh->input[z] != '\t' && \
			msh->input[z] != '\0')
		z++;
	str = malloc (sizeof(char) * (z - *i + 1));
	if (str == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	ft_strlcpy(str, &msh->input[*i], z - *i + 1);
	return (str);
}

// static int	special_nonzero(char *str, char *dname, char **arr, int *y)
// {
// 	char	*temp;

// 	if (arr[*y] != NULL)
// 	{
// 		temp = ft_strnstr(dname, arr[*y], ft_strlen(arr[*y]));
// 		if (temp == NULL || temp != str)
// 			return (-1);
// 		(*y)++;
// 	}
// 	return (0);
// }

// static int	special_nonfinal(char *str, char *dname, char **arr, int *y)
// {
// 	char	*temp;
// 	int		len;
// 	int		strlen;

// 	if (arr[*y] != NULL)
// 	{
// 		temp = ft_strnstr(dname, arr[*y], ft_strlen(arr[*y]));
// 		len = ft_strlen(temp);
// 		strlen = ft_strlen(str);
// 		if (temp == NULL || temp != &str[strlen - len])
// 			return (-1);
// 		(*y)++;
// 	}
// 	return (0);
// }

// static int	find_matching(char *str, char *dname)
// {
// 	int		y;
// 	char	**arr;
// 	char	*temp;
// 	char	*backup;

// 	arr = ft_split(str, '*');
// 	y = 0;
// 	if (str[0] != '*')
// 	{
// 		if (special_nonzero(str, dname, arr, &y) == -1)
// 			return (free_mallocs(NULL, (void **)arr), free(*arr), -1);
// 	}
// 	backup = NULL;
// 	while (arr[y] != NULL)
// 	{
// 		temp = ft_strnstr(dname, arr[y], ft_strlen(arr[y]));
// 		if (temp == NULL || (backup != NULL && temp <= backup))
// 			return (free_mallocs(NULL, (void **)arr), free(arr), -1);
// 		backup = temp;
// 		if (arr[y + 1] == NULL && str[ft_strlen(str)] != '*')
// 			if (special_nonfinal(str, dname, arr, &y) == -1)
// 				return (free_mallocs(NULL, (void **)arr), free(arr), -1);
// 		y++;
// 	}
// 	return (0);
// }

void	handle_wild_character(t_msh *msh, int *i)
{
	char			*str;
	// DIR				*dir;
	// struct dirent	*entry;
	// int				count;

	str = find_exp(msh, i);
	// count = 0;
	// dir = opendir(get_current_dir_name());
	// if (dir == NULL)
	// 	exit_cleanup("Opendir", msh, errno, 2);
	// entry = readdir(dir);
	// while (entry != NULL)
	// {
	// 	if (find_matching(str, entry->d_name) != -1)
	// 	{
	// 		copy_input_mod(msh, entry->d_name, 0, ft_strlen(entry->d_name));
	// 		copy_input_mod(msh, " ", 0, 1);
	// 		count++;
	// 	}
	// 	entry = readdir(dir);
	// }
	// if (count == 0)
	// 	copy_input_mod(msh, str, 0, ft_strlen(str));
	// closedir(dir);
	free(str);
}
