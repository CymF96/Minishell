/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/23 12:16:13 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <stddef.h>
# include <linux/limits.h>
# include "./LIBFT/libft.h"
# include "./PARSE/parse.h"

#define FIELD_OFFSET(type, field) offsetof(type, field)

typedef struct s_child //fork and pipe
{
	int		fd_in;
	int		fd_out;
	char	**commands;
}	t_child;

typedef struct s_parent //fork and pipe
{
	int		fd_in;
	int		fd_out;
	int		num_of_child;
	char	*heredoc; // start 
	char	*heredoc_delim; //end when same delimiter word
	pid_t	*pids;
	t_child	*children;
}	t_parent;

typedef struct s_pexe
{
	int				type;
	char			*cmd;
	char			**option;
	int				group_id;
	int				p_index;
	int				*fd;
	struct s_pexe	*prev;
	struct s_pexe	*next;
}	t_pexe;

typedef struct s_msh //master structure 'minishell'
{
	char		*input;
	int			exit_code;
	//char		**parsed_args; // needed for execution
	char		**envp; // keep the array in the structure to be sure to print all env var if env builtin function is called?
	int			*fd;
	t_parse		*parse;
	t_pexe		*pexe; //args structure for execution
	t_parent	*parent_str;
}	t_msh;

typedef enum e_type
{
	COMMAND,
	STRING,
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	
};

/***********TYPE_SUMMARY*********/
/* 1. builtin command			*/
/* 2. string					*/
/* 3. path						*/
/* 4. execution					*/
/* 5. $?						*/
/* 6. redirection				*/
/* 7. filename				*/
/* 8. */
/* 9. signal					*/
/* 10. */
/********************************/

/*------- INPUT_VALIDATE -------*/
void	input_validate(int ac, char **envp);

/*------- INITIALIZE -------*/
void	clean_initialize(t_msh *msh);
void	clean_init_parse(t_parse *pars);
void	clean_init_token_node(t_token *tkn);
void	clean_init_pexe_node(t_pexe *pexe);

/*------- EXECUTION -------*/
void	check_if_exit(t_msh msh);
int		execution(t_msh *msh);
void	check_builtin_cmd(t_msh *msh, char *cmd);
void	check_exit_status_cmd(t_msh *msh, char *cmd);
void	cmd_exit(t_msh *msh);
void	cmd_echo(t_msh *msh);
void	cmd_pwd(t_msh *msh);
void	cmd_cd(t_msh *msh);
void	cmd_env(t_msh *msh);
void	find_exe(t_msh *msh, char *cmd);

/*------- PARSE USER INPUT -------*/
int		parse_main(t_msh *msh);
void	parse_malloc(t_msh *msh, t_parse *prs);
t_token	*token_malloc(t_msh *msh, t_parse *prs);
t_pexe	*pexe_malloc(t_msh *msh, t_parse *prs);
void	add_node(void **head, void *node, size_t next_off, size_t prev_off);
void	parse_tokenize(t_msh *msh, t_parse *prs);
void	expand_dollars(t_msh *msh, t_parse *pars, int flag);
void	handle_quotes(char *input, int *i);


/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag);
void	free_parse(t_msh *msh);
void	free_pexe(t_msh *msh);
void	free_mallocs(void *s_ptr, void **d_ptr);

#endif