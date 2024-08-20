/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:22:26 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/20 11:25:01 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_ev_var(char *envp)
{
	char	*var_content;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	ft_memmove(envp + i, var_content, ft_strlen(envp + i));
}

void	env_var(t_msh *msh, char *var_name)
{
	int i;

	i = 0;
	while (msh->envp[i] != NULL)
	{
		if (!ft_strncmp(msh->envp[i], var_name, ft_strlen(var_name)))
		{
			replace_ev_var(msh->envp[i]);
			return ;
		}
		i++;
	}
	ft_printf("variable %s doesn't exist\n", var_name);
}
