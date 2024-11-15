/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:54:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/15 15:03:37 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_exit_number(t_msh *msh, char *temp)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(temp, ' ');
	while (str[i] != NULL)
		i++;
	if (i > 2)
	{
		msh->exit_error = 127;
		return (free_mallocs(NULL, (void **) str), 1);
	}
	if (str[1] != NULL)
		msh->exit_error = ft_atoi(str[1]);
	free_mallocs(NULL, (void **) str);
	i = 3;
	while (temp[++i] != '\0')
	{
		if (!ft_strncmp("exit", &temp[i], 4))
			i += 4;
		if (!isdigit(temp[i]) && \
				!(temp[i] == '\'' || temp[i] == '\"' || temp[i] == ' '))
		{
			msh->exit_error = 2;
			return (2);
		}
	}
	return (0);
}

static int	check_exit_alone(char *temp)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	flag = 0;
	while (temp[++i] != '\0')
	{
		if (!ft_strncmp("exit", &temp[i], 4) && \
				(temp[i + 4] == ' ' || temp[i + 4] == '\0'))
			return (0);
		if (temp[i] == '\'' || temp[i] == '\"')
		{
			j = check_quote_ending(temp, i);
			while (i < j && temp[i] != '\0')
			{
				if (temp[i] == ' ')
					i++;
				else if (!ft_strncmp("exit", &temp[i], 4) && flag == 0)
				{
					flag = 1;
					i += 4;
				}
				else
					return (1);
			}
		}
	}
	return (0);
}

int	check_if_exit(t_msh *msh)
{
	char	*temp;
	int		i;

	if (msh->input != NULL)
	{
		temp = ft_strdup(msh->input);
		remove_quotes(temp, ft_strlen(temp), temp);
		if (ft_strncmp("exit", temp, 4) != 0)
			return (1);
		free(temp);
		temp = ft_strdup(msh->input);
		if (check_exit_alone(temp) != 0)
			return (free(temp), 0);
		if (!ft_strncmp("exit", temp, 4))
		{
			i = check_exit_number(msh, temp);
			if (i == 1)
				return (printf("Exit: Too many arguments\n"), free(temp), 1);
			else if (i == 2)
				printf("Exit\nExit: %s: Numeric argument required\n", &temp[4]);
			free(temp);
			exit_cleanup("User says 'Be Gone Thot!'", msh, msh->exit_error, 1);
		}
		free(temp);
		return (0);
	}
	return (1);
}
