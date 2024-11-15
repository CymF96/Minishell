/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:54:54 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/15 18:34:20 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_exit_number_cont(t_msh *msh, char *temp, int *i)
{
	while (temp[*i] != '\0')
	{
		if (!ft_strncmp("exit", &temp[*i], 4))
			i += 4;
		if (!isdigit(temp[*i]) && \
				!(temp[*i] == '\'' || temp[*i] == '\"' || temp[*i] == ' '))
		{
			msh->exit_error = 2;
			return (2);
		}
		(*i)++;
	}
	return (0);
}

static void	find_exit_error(t_msh *msh, char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		// printf("str at point %d is %s\n", i, str[i]);
		remove_quotes(str[i], ft_strlen(str[i]), str[i]);
		if (ft_isdigit(str[i][0]))
		{
			msh->exit_error = ft_atoi(str[i]);
			return ;
		}
		i++;
	}
}

static int	check_exit_number(t_msh *msh, char *temp)
{
	int		i;
	char	**str;

	i = 0;
	printf("HEREEEEEEEEEEEEEEE");
	str = ft_split(temp, ' ');
	while (str[i] != NULL)
	{
		printf("str at point %d is %s\n", i, str[i]);
		i++;
	}
	if (i > 2)
	{
		msh->exit_error = 127;
		return (free_mallocs(NULL, (void **) str), 1);
	}
	find_exit_error(msh, str);
	free_mallocs(NULL, (void **) str);
	i = 4;
	if (check_exit_number_cont(msh, temp, &i) == 2)
		return (2);
	return (0);
}

static int	check_exit_alone_cont(char *temp, int *i)
{
	int	j;

	j = 0;
	if (!ft_strncmp("exit", &temp[*i], 4) && \
			(temp[*i + 4] == ' ' || temp[*i + 4] == '\0'))
		return (0);
	if (temp[*i] == '\'' || temp[*i] == '\"')
	{
		j = check_quote_ending(temp, *i);
		(*i)++;
		if (!ft_strncmp("exit", &temp[*i], 4) && (*i) + 4 == j && ((*i) + 5 == ' ' || (*i) + 5 == '\0'))
		{
			printf("WE RETURN 0\n");
			return (0);
		}
		else
		{
			printf("WE RETURN 0\n");
			return (1);
		}
	}
	return (-1);
}

static int	check_exit_alone(char *temp)
{
	int	i;
	int	k;

	i = -1;
	while (temp[++i] != '\0')
	{
		k = check_exit_alone_cont(temp, &i);
		if (k != -1)
			return (k);
	}
	return (1);
}

static int	check_if_exit_cont(t_msh *msh, char *temp, int *i)
{
	if (msh->input != NULL)
	{
		temp = ft_strdup(msh->input);
		remove_quotes(temp, ft_strlen(temp), temp);
		if (ft_strncmp("exit", temp, 4) != 0)
			return (free(temp), 0);
		free(temp);
		temp = ft_strdup(msh->input);
		if (check_exit_alone(temp) != 0)
			return (free(temp), 0);
		*i = check_exit_number(msh, temp);
		if (*i == 1)
			return (printf("Exit: Too many arguments\n"), free(temp), 1);
		else if (*i == 2)
			printf("Exit\nExit: %s: Numeric argument required\n", &temp[4]);
		free(temp);
		exit_cleanup("User says 'Be Gone Thot!'", msh, msh->exit_error, 1);
		return (0);
	}
	return (1);
}

int	check_if_exit(t_msh *msh)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	i = check_if_exit_cont(msh, temp, &i);
	return (i);
}
