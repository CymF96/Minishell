/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/27 12:16:25 by mcoskune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

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
# include <stdbool.h>
# include "./LIBFT/libft.h"
# include "./PARSE/parse.h"

# define FIELD_OFFSET(type, field) offsetof(type, field)
# define SIGINT_FLAG 0x01	// 0001
# define SIGQUIT_FLAG 0x02	// 0010
# define SIGEOF_FLAG 0x04	// 0100

volatile sig_atomic_t signal_flags = 0;

typedef struct s_pipex
{
	int		fd[2];
	pid_t	pid;
}	t_pipex;

typedef struct s_pexe
{
	int				type;
	char			*cmd;
	char			**option;
	int				group_id;
	int				p_index;
	t_type			muk_note;
	char			*temp;
	struct s_pexe	*prev;
	struct s_pexe	*next;
}	t_pexe;

typedef struct s_msh //master structure 'minishell'
{
	char		*input;
	char		**envp; // keep the array in the structure to be sure to print all env var if env builtin function is called?
	int			fd[2];
	int			pipe_nb;
	int			flag;
	int			exit_error;
	int			exit_parent;
	t_parse		*parse;
	t_pexe		*pexe; //args structure for execution
	pid_t		main_child;
}	t_msh;

typedef enum e_type
{
	COMMAND,
	STRING,
	PATH,
	EXE,
	EXIT_ERROR,
	PIPE,
	WILDCARD,
	INFILE,
	FNAME,
	SIGNAL,
	HEREDOC,
	INFILE,
	OUTFILE,
	APPEND,
}	t_type;

/***********ERROR_TYPE***********/
/* 1. command not found			*/
/* 2. SIGEOF					*/
/* 3. syntax error?				*/
/* 4. allocation error			*/
/* 5. File/directory not found	*/
/* 6. Signals error				*/
/* 7. filename					*/
/* 8. pipe						*/
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
void	create_modified(t_msh *msh, t_parse *pars);
int		check_quote_ending(char *input, int i);
char	*expand_env(t_msh *msh, t_parse *pars, int *i, int *j);
void	quote_token(char *temp, int *i);
void	handle_redir(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_pipes(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_logic(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_paran(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_wildcard(t_msh *msh, t_parse *pars, int *i, int *j);
void	make_pexe(t_msh *msh, t_parse *pars);

/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag);
void	free_parse(t_msh *msh);
void	free_pexe(t_msh *msh);
void	free_mallocs(void *s_ptr, void **d_ptr);

#endif