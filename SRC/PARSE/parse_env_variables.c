/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cofische <cofische@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:22:26 by mcoskune          #+#    #+#             */
/*   Updated: 2025/05/28 17:59:25 by cofische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	dollar_error(t_msh *msh, int *i)
{
	char	*temp;

	if (!strncmp("echo", msh->input, ft_strlen(msh->input)) \
		&& strrchr(msh->input, '+'))
	{
		exit_error_addition(msh);
		return (1);
	}
	else if (*i == 1)
		check_exit_status_cmd(msh, 1);
	else
	{
		temp = ft_itoa(msh->exit_error);
		if (temp == NULL)
			exit_cleanup("dollar_error()- temp var empty\n", msh, errno, 2);
		copy_input_mod(msh, temp, 0, ft_strlen(temp));
		free(temp);
		(*i)++;
		return (0);
	}
	return (1);
}

// Expanding $'s. Specifically checking if it is ? or a space/tab.
int	expand_dollars(t_msh *msh, int *i)
{
	char	*temp;

	(*i)++;
	if (msh->input[*i] == ' ' || msh->input[*i] == '\t' || \
		msh->input[*i] == '\0')
		copy_input_mod(msh, "$ ", 0, 0);
	else if (msh->input[*i] == '?')
	{
		if (dollar_error(msh, i) == 1)
			return (1);
	}
	else
	{
		temp = expand_env(msh, i, 0);
		if (temp == NULL)
			return (0);
		copy_input_mod(msh, temp, 0, ft_strlen(temp));
		free (temp);
	}
	return (0);
}

// finds what the variable is after $ until it sees space, tab or null
static char	*find_var(t_msh *msh, int *i, int flag)
{
	int		k;
	char	*temp;
	char	*text;

	k = *i;
	text = msh->input;
	if (flag != 0)
		text = msh->parse->temp;
	while (text[*i] != ' ' && text[*i] != '\n' && text[*i] != '\t' && \
			text[*i] != '\0' && check_special(text, i) == REGULAR)
		(*i)++;
	temp = malloc(sizeof(char) * (*i - k + 2));
	if (temp == NULL)
		exit_cleanup("Malloc failed", msh, errno, 2);
	ft_strlcpy(temp, &text[k], *i - k + 2);
	temp[*i - k] = '=';
	temp[*i - k + 1] = '\0';
	return (temp);
}

// Goes through env values. If match is found, returns a malloced memory addr
char	*expand_env(t_msh *msh, int *i, int flag)
{
	int		k;
	int		len;
	char	*temp;
	char	*str;

	temp = find_var(msh, i, flag);
	len = ft_strlen(temp);
	k = 0;
	while (msh->envp != NULL && msh->envp[k] != NULL && msh->envp[k][0] != '\0')
	{
		str = ft_strnstr(msh->envp[k], temp, len);
		if (str)
		{
			str = ft_substr(str, len, ft_strlen(str));
			free (temp);
			return (str);
		}
		k++;
	}
	free(temp);
	return (NULL);
}
