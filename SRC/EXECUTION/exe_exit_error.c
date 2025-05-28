/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:00:30 by cofische          #+#    #+#             */
/*   Updated: 2025/05/28 17:58:58 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	dollar_expansion(t_msh *msh, int *i, t_type type)
{
	if (type == DOLLAR)
	{
		if (expand_dollars(msh, i) == 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	count(t_msh *msh)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (msh->input[i])
	{
		if (msh->input[i] == '$' && msh->input[i + 1] == '?')
			count++;
		i++;
	}
	return (count);
}

void	exit_error_message(t_msh *msh, int len, char *num, char *ex_code)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (msh->input[i])
	{
		if (msh->input[i] == '\"')
			i++;
		if (msh->input[i] == '$' && msh->input[i + 1] == '?')
		{
			ft_strlcpy(ex_code + j, num, len + 1);
			j += len;
			i += 2;
		}
		else if (msh->input[i])
			ex_code[j++] = msh->input[i++];
	}
	ex_code[j] = '\0';
}

void	exit_error_addition(t_msh *msh)
{
	char	*code_exit;
	char	*exit_error_num;
	int		len;

	exit_error_num = ft_itoa(msh->exit_error);
	len = ft_strlen(exit_error_num);
	code_exit = malloc(ft_strlen(msh->input + 1) + (2 * count(msh)));
	exit_error_message(msh, len, exit_error_num, code_exit);
	ft_printf("%s: command not found\n", code_exit);
	free(code_exit);
	free(exit_error_num);
	msh->exit_error = 127;
}

void	check_exit_status_cmd(t_msh *msh, int flag)
{
	char	*exit_message;

	exit_message = NULL;
	if (msh->exit_error)
		exit_message = strerror(msh->exit_error);
	else if (msh->exit_error < 0)
		ft_printf("Error unknown\n");
	if (flag == 1 && exit_message)
		ft_printf("%d: %s\n", msh->exit_error, exit_message);
	else
		ft_printf("%d\n", msh->exit_error);
}
