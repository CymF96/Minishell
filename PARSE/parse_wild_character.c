/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wild_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:10:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/27 18:22:43 by mcoskune         ###   ########.fr       */
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

static int	find_matching(char *str, char *dname)
{
	int	z;
	int	y;
	int	x;
	char **arr;

	arr = ft_split(str, '*');
	y = ft_strlen(str);
	

	if (ft_strnstr()) == NULL)
	{
		x = 0;
		while (arr[x] != NULL)
			free (arr[x]);
		free(arr);
		return (-1);
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
	while ((entry = readdir (dir)) != NULL)
	{
		if (find_matching(str, entry->d_name) != -1)
		{
			k = 0;
			while (entry->d_name[k] != '\0')
				pars->modified[(*j)++] = entry->d_name[k++];
		}
	}
	closedir (dir);
	free (str);
}
