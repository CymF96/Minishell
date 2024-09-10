/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_create_modified.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:25:28 by mcoskune          #+#    #+#             */
/*   Updated: 2024/09/10 14:57:54 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Expanding $'s. Specifically checking if it is ? or a space/tab.
void	expand_dollars(t_msh *msh, int *i)
{
	char	*temp;

	(*i)++;
	if (msh->input[*i] == ' ' || msh->input[*i] == '\t')
		copy_input_mod(msh, "$", 0, 1);
	else if (msh->input[*i] == '?')
	{
		temp = ft_itoa(msh->exit_error);
		if (temp == NULL)
			exit_cleanup("Malloc Failed\n", msh, errno, 2);
		copy_input_mod(msh, temp, 0, ft_strlen(temp));
		free(temp);
	}
	else
	{
		temp = expand_env(msh, i, 0);
		if (temp == NULL)
			exit_cleanup("NO TEMP\n", msh, errno, 2);
		copy_input_mod(msh, temp, 0, ft_strlen(temp));
		free (temp);
	}
}

// If single quote, prints all as char. In double quote checks for $ and expands
static void	handle_quote(t_msh *msh, int *i)
{
	int	start;
	int	flag;

	flag = 0;
	start = (*i)++;
	if (msh->input[(*i) - 1] == '\'')
	{
		while (msh->input[*i] != '\'' && msh->input[*i] != '\0')
			(*i)++;
		copy_input_mod(msh, &msh->input[start], start, (*i));
	}
	if (msh->input[(*i) - 1] == '\"')
	{
		while (msh->input[*i] != '\"' && msh->input[*i] != '\0')
		{
			while (msh->input[*i] != '\"' && msh->input[*i] != '\0')
			{
				if (msh->input[*i] == '$')
				{
					copy_input_mod(msh, &msh->input[start], start, (*i) - 1);
					flag = 1;
					break ;
				}
				(*i)++;
			}
			if (flag == 0)
				copy_input_mod(msh, &msh->input[start], start, (*i));
			if (msh->input[(*i)] == '$')
			{
				expand_dollars(msh, i);
				flag = 0;
			}
			start = (*i);
		}
	}
	(*i)++;
}
// printf("The string in handle quote is %s\n\n %d\n %d\n\n", 
//&msh->input[start], start, *i);

// Checks for special characters and direct them to their own functions
static void	check_character(t_msh *msh, t_parse *pars, int *i, t_type type)
{
	if (type == HEREDOC || type == INFILE || type == APPEND || type == OUTFILE)
		handle_redir(msh, pars, i, type);
	else if (type == PIPE)
		handle_pipes(msh, pars, type);
	else if (type == AND || type == OR)
		handle_logic(msh, pars, i, type);
	else if (type == L_PAR || type == R_PAR)
		handle_paran(msh, pars, type);
	else if (type == WILDCARD)
		handle_wild_character(msh, i);
	(*i)++;
}

// static int	check_for_wild(t_msh *msh, char *str, int *i, int *flag)
// {
// 	int	k;

// 	k = *i;
// 	while ((str[*i] == ' ' || str[*i] == '\t') && str[*i] != '\0')
// 		(*i)++;
// 	copy_input_mod(msh, &msh->input[k], k, *i - 1);
// 	k = *i;
// 	while (str[k] != ' ' && str[k] != '\t' && str[k] != '\0')
// 	{
// 		if (check_special(str, &k) == WILDCARD)
// 		{
// 			*flag = 1;
// 			return (1);
// 		}
// 		k++;
// 	}
// 	return (0);
// }

// Checks for $, ' and ". Otherwise just copy everything to modified char *
void	input_to_modified(t_msh *msh, t_parse *pars)
{
	int		start;
	int		i;
	t_type	type;

	start = 0;
	i = 0;
	while (msh->input[i] != '\0')
	{
		type = check_special(msh->input, &i);
		if (type == DOLLAR)
			expand_dollars(msh, &i);
		else if (type == S_QT || type == D_QT)
			handle_quote(msh, &i);
		else if (type == REGULAR)
		{
			start = i;
			while (msh->input[i] != '\0' && \
					check_special(msh->input, &i) == REGULAR)
				i++;
			copy_input_mod(msh, &msh->input[start], start, i - 1);
		}
		else
			check_character(msh, pars, &i, type);
	}
}

// Main function to create the modified string
void	create_modified(t_msh *msh, t_parse *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (msh->input[i] != '\0')
	{
		if (check_special(msh->input, &i) != REGULAR)
			j++;
		i++;
	}
	pars->poi = malloc(sizeof(int *) * (j + 2));
	if (pars->poi == NULL)
		exit_cleanup("Malloc Failed", msh, errno, 2);
	i = 0;
	while (i <= j)
		pars->poi[i++] = NULL;
	pars->size_modified = 0;
	pars->modified = malloc (sizeof(char) * (pars->size_modified + 1));
	if (pars->modified == NULL)
		exit_cleanup ("Malloc Failed", msh, errno, 2);
	pars->modified[pars->size_modified] = '\0';
	input_to_modified(msh, pars);
}
