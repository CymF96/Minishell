/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:22:26 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/23 15:31:46 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_var(t_msh *msh, int *i)
{
	int		k;
	int		len;
	char	*temp;

	k = *i;
	len = 0;
	while (msh->input[*i] != ' ' && msh->input[*i] != '\t' \
			&& msh->input[*i] != '\0')
	{
		(*i)++;
		len++;
	}
	temp = malloc(sizeof(char) * (*i - k + 2));
	if (temp == NULL)
		exit_cleanup("Malloc failed", msh, errno);
	ft_strlcpy(temp, &msh->input[k], *i - k + 2);
	return (temp);
}
char	*expand_env(t_msh *msh, t_parse *pars, int *i, int *j)
{
	int		k;
	int		len;
	char	*temp;

	k = 0;
	temp = find_var(msh, i);
	len = ft_strlen(temp);
	while (msh->envp[k] != NULL)
	{
		if (!ft_strncmp(temp, msh->envp[k], len))
		{
			free(temp);
			temp = msh->envp[k][len];
			return (temp);
		}
		k++;
	}
	ft_printf("variable %s doesn't exist\n", temp);
	free(temp);
	return (NULL);
}
