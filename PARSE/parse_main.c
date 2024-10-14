/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:25:00 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/11 13:06:53 by mcoskune         ###   ########.fr       */
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
		if (msh->input[j] != '\0' && (msh->input[j] == ' ' || msh->input[j] == '\t'))
		{
			j++;
			continue ;
		}
		else if (type != REGULAR && type != DOLLAR && \
				type != S_QT && type != D_QT)
			return (1);
		else if (type == REGULAR && msh->input[j] != '\0')
			return (0);
		j++;
	}
	return (1);
}

// int	request_more_input(t_msh *msh, t_parse *pars)
// {
// 	// char	*gnl_temp;
// 	// // int		fd[2];
// 	// char	*temp;
// 	char	test[100];
// 	(void) msh;
// 	clean_init_parse(pars);
// 	write (1, "> ", 2);
// 	// if (pipe(fd) == -1)
// 	// 	exit_cleanup("Pipe Failed\n", msh, errno, 0);
// 	int	i = read(0, test, 100);
// 	test[i] = '\0';
// 	printf("TEST IS %s\n", test);
// 	msh->input = ft_strjoin(msh->input, " ");
// 	msh->input = ft_strjoin(msh->input, test);
// 	// temp = get_next_line(STDIN_FILENO);
// 	if (msh->interrupted)
// 	{
// 		if (msh->input != NULL)
// 			free(msh->input);
// 		msh->input = NULL;
// 		return (1);
// 	}
// 	// gnl_temp = ft_strjoin(" ", temp);
// 	// free(temp);
// 	// msh->text = ft_strjoin(msh->input, gnl_temp);
// 	// free (gnl_temp);
// 	// free (msh->input);
// 	// msh->input = msh->text;
// 	// msh->text = NULL;
// 	return (0);
// }

int	request_more_input(t_msh *msh, t_parse *pars)
{
	char	*gnl_temp;
	int		i;
	char	*temp;

	clean_init_parse(pars);
	i = write (1, "> ", 2);
	(void) i;
	temp = get_next_line(STDIN_FILENO, msh);
	if (msh->interrupted || temp == NULL)
	{
		if (temp != NULL)
			free(temp);
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

int	analyse_input(t_msh *msh, t_parse *pars)
{
	int		i;
	t_type	tye;

	i = -1;
	(void)pars;
	while (msh->input[++i] != '\0')
	{
		tye = check_special(msh->input, &i);
		if (tye == HEREDOC || tye == APPEND || tye == INFILE || tye == OUTFILE)
		{
			if (check_something_exists(msh, &i, tye) != 0)
			{
				write(2, "Syntax Error Near Special Character\n", 37);
				return (1);
			}
			i--;
		}
		else if (tye == PIPE)
		{
			if (check_something_exists(msh, &i, tye) != 0)
				return (2);
		}
		else if (tye == D_QT || tye == S_QT)
		{
			if (check_quote_ending(msh->input, i) == -1)
				return (2);
			i = check_quote_ending(msh->input, i);
		}
	}
	return (0);
}

int	parse_main(t_msh *msh)
{
	int	flag;

	if (msh == NULL || msh->input == NULL || msh->input[0] == '\0')
		return (1);
	parse_malloc(msh);
	flag = analyse_input(msh, msh->parse);
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
		flag = analyse_input(msh, msh->parse);
	}
	if (create_modified(msh, msh->parse) == 1)
		return (1);
	if (msh->parse->modified[0] == '|')
		return (1);
	if (handle_wilds(msh, msh->parse) == 1)
		return (1);
	// printf("Modified string is: %s\n", msh->parse->modified);
	
	parse_tokenize(msh, msh->parse);

	
	// t_token	*tkn = msh->parse->head;
	// while (tkn)
	// {
	// 	int	j = 0;
	// 	while (tkn->token[j] != '\0')
	// 	{
	// 		if (tkn->token[j] == ' ')
	// 			tkn->token[j] = '#';
	// 		j++;
	// 	}
	// 	printf("Token is: %s\n", tkn->token);
	// 	tkn = tkn->next;
	// }


	make_pexe(msh, msh->parse);

	// t_pexe *temp = msh->pexe;
	// while (temp != NULL)
	// {
	// 	int	i = 0;
	// 	while (temp->cmd[i] != '\0')
	// 	{
	// 		if (temp->cmd[i] == ' ')
	// 			temp->cmd[i] = '#';
	// 		i++;
	// 	}
	// 	printf("PEXE-TYPE: %d\n", temp->type);
	// 	printf("PEXE-CMD: %s\n", temp->cmd);
	// 	printf("PEXE-GROUP_ID: %d\n", temp->group_id);
	// 	printf("PEXE-PRIORITY: %d\n", temp->p_index);
	// 	printf("PEXE-MUK_NOTE: %d\n", temp->muk_note);
	// 	printf("PEXE-TEMP: %s\n\n", temp->temp);

	// 	temp = temp->next;
	// }

	return (0);
}