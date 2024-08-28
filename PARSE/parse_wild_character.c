/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wild_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:10:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/28 12:20:32 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_exp(t_msh *msh, int *i, int *j)
{
	int		z;
	char	*str;

	z = *i;
	while (msh->input[z] != ' ' && msh->input[z] != '\t' && z >= 0)
		z--;
	z++;
	while (msh->input[*i] != ' ' && msh->input[*i] != '\t' && \
		msh->input[*i] != '\0')
		(*i)++;
	str = malloc (sizeof(char) * (*i - z + 2));
	if (str == NULL)
		exit_cleanup("Malloc failed", msh, errno);
	ft_strlcpy(str, &msh->input[z], *i - z + 2);
	*j = z;
	return (str);
}

static int	special_nonzero(char *str, char *dname, char **arr, int *y)
{
	char	*temp;

	if (arr[*y] != NULL)
	{
		temp = ft_strnstr(dname, arr[*y], ft_strlen(arr[*y]));
		if (temp == NULL || temp != str)
			return (-1);
		(*y)++;
	}
}

static int	special_nonfinal(char *str, char *dname, char **arr, int *y)
{
	char	*temp;
	int		len;
	int		strlen;

	if (arr[*y] != NULL)
	{
		temp = ft_strnstr(dname, arr[*y], ft_strlen(arr[*y]));
		len = ft_strlen(temp);
		strlen = ft_strlen(str);
		if (temp == NULL || temp != &str[strlen - len])
			return (-1);
		(*y)++;
	}
}

static int	find_matching(char *str, char *dname)
{
	int		y;
	char	**arr;
	char	*temp;
	char	*backup;

	arr = ft_split(str, '*');
	y = 0;
	if (str[0] != '*')
	{
		if (special_nonzero(str, dname, arr, &y) == -1)
			return (free_mallocs(NULL, arr), free(arr), -1);
	}
	backup = NULL;
	while (arr[y] != NULL)
	{
		temp = ft_strnstr(dname, arr[y], ft_strlen(arr[y]));
		if (temp == NULL || (backup != NULL && temp <= backup))
			return (free_mallocs(NULL, arr), free(arr), -1);
		backup = temp;
		if (arr[y + 1] == NULL && str[ft_strlen(str)] != '*')
			if (special_nonfinal(str, dname, arr, &y) == -1)
				return (free_mallocs(NULL, arr), free(arr), -1);
		y++;
	}
}

void	handle_wild_character(t_msh *msh, t_parse *pars, int *i, int *j)
{
	char			*str;
	DIR				*dir;
	struct dirent	*entry;
	int				k;

	str = find_exp(msh, i, j);
	dir = opendir (".");
	if (dir == NULL)
		exit_cleanup("Opendir", msh, errno);
	entry = readdir (dir);
	while (entry != NULL)
	{
		k = 0;
		if (find_matching(str, entry->d_name) != -1)
		{
			k = 0;
			while (entry->d_name[k] != '\0')
				pars->modified[(*j)++] = entry->d_name[k++];
			pars->modified[(*j)++] = ' ';
		}
		entry = readdir (dir);
	}
	closedir (dir);
	free (str);
}
