/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:00 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/15 22:32:34 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// valgrind --suppressions=./OTHER/debugging/rl.supp --leak-check=full --show-
//leak-kinds=all --track-origins=yes --verbose 
//--log-file=valgrind-out.txt ./minishell

static int	check_something_exists(t_msh *msh, int *i, t_type tye)
{
	int		j;
	t_type	type;

	if (tye == HEREDOC || tye == APPEND)
		*i += 2;
	else
		(*i)++;
	j = *i;
	while (j < (int)ft_strlen(msh->input) && msh->input[j] != '\0')
	{
		type = check_special(msh->input, &j);
		if (msh->input[j] != '\0' && (msh->input[j] == ' ' || \
			msh->input[j] == '\t'))
		{
			j++;
			continue ;
		}
		else if (type != REGULAR && type != DOLLAR && type != S_QT && \
			type != D_QT && type != INFILE && type != OUTFILE && \
			type != HEREDOC && type != APPEND)
			return (1);
		else if (type == REGULAR && msh->input[j] != '\0')
			return (0);
		j++;
	}
	return (1);
}

int	request_more_input(t_msh *msh, t_parse *pars)
{
	char	*gnl_temp;
	char	*temp;

	clean_init_parse(pars);
	write (1, "> ", 2);
	temp = get_next_line(STDIN_FILENO, msh);
	if (msh->interrupted || temp == NULL)
	{
		while (temp != NULL)
		{
			free(temp);
			temp = get_next_line(STDIN_FILENO, msh);
		}
		// if (temp != NULL)
		// 	free(temp);
		temp = NULL;
		if (msh->input != NULL)
			free(msh->input);
		msh->input = NULL;
		return (1);
	}
	gnl_temp = ft_strjoin(" ", temp);
	free(temp);
	msh->text = ft_strjoin(msh->input, gnl_temp);
	free (gnl_temp);
	free (msh->input);
	msh->input = msh->text;
	msh->text = NULL;
	return (0);
}

static int	analyse_helper(t_msh *msh, int *i, t_type tye)
{
	if (tye == HEREDOC || tye == APPEND || tye == INFILE || tye == OUTFILE)
	{
		if (check_something_exists(msh, i, tye) != 0)
		{
			write(2, "Syntax Error Near Special Character\n", 37);
			return (1);
		}
		(*i)--;
	}
	else if (tye == PIPE)
	{
		if (check_something_exists(msh, i, tye) != 0)
			return (2);
	}
	else if (tye == D_QT || tye == S_QT)
	{
		if (check_quote_ending(msh->input, *i) == -1)
			return (2);
		*i = check_quote_ending(msh->input, *i);
	}
	return (0);
}

int	analyse_input(t_msh *msh)
{
	int		i;
	int		check;
	t_type	tye;

	i = -1;
	check = 0;
	while (msh->input[++i] != '\0')
	{
		tye = check_special(msh->input, &i);
		check = analyse_helper(msh, &i, tye);
		if (check != 0)
			return (check);
	}
	return (0);
}

int	parse_main(t_msh *msh)
{
	int	flag;

	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return (1);
	parse_malloc(msh);
	flag = analyse_input(msh);
	if (flag == 1)
		return (1);
	while (1)
	{
		if (msh->parse->l_count == msh->parse->r_count && flag == 0)
			break ;
		if (flag == 1)
			return (1);
		if ((request_more_input(msh, msh->parse)))
			return (1);
		flag = analyse_input(msh);
	}
	if (create_modified(msh, msh->parse) == 1)
		return (1);
	if (msh->parse->modified[0] == '|' || handle_wilds(msh, msh->parse) == 1)
		return (1);
	parse_tokenize(msh, msh->parse);
	make_pexe(msh, msh->parse);
	return (0);
}
