/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/08/30 10:50:46 by mcoskune         ###   ########.fr       */
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
# include <dirent.h>
# include <linux/limits.h>
# include <stdbool.h>
# include "./LIBFT/libft.h"
# include "./PARSE/parse.h"

# define FIELD_OFFSET(type, field) offsetof(type, field)
# define SIGINT_FLAG 0x01	// 0001
# define SIGQUIT_FLAG 0x02	// 0010

typedef enum s_type
{
	COMMAND,
	STRING,
	PATH,
	EXE,
	EXIT_ERROR,
	PIPE,
	WILDCARD,
	FNAME,
	SIGNAL,
	HEREDOC,
	INFILE,
	OUTFILE,
	APPEND,
}	t_type;

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
	int			exit_error; // initialise only one time to keep track of exit error code
	volatile sig_atomic_t signal_flags;
	t_parse		*parse;
	t_pexe		*pexe; //args structure for execution
	pid_t		main_child;
}	t_msh;



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
int	input_validate(int ac, char **envp);

/*------- INITIALIZE -------*/
void	clean_init_chds(t_pipex *chds);
void	clean_init_parse(t_parse *pars);
void	clean_init_token_node(t_token *tkn);
void	clean_init_pexe_node(t_pexe *pexe);
void	clean_msh_init(t_msh *msh);

/*------- UTILS -------*/
void	adding_var(t_msh *msh, char *new_var, char **env_struct);
void	set_var_name(char *cmd, char *var_name);
int	updating_var(char **env_struct, char *var_name, char *cmd);

/*------- EXECUTION -------*/
void	execution(t_msh *msh);
void	check_type(t_msh *msh);
void	check_builtin_cmd(t_msh *msh, char *cmd);
void	check_exit_status_cmd(t_msh *msh, char *cmd);
void	double_red_right(t_msh *msh);
void	red_left(t_msh *msh);
void	red_right(t_msh *msh);
void	ft_pipex(t_msh *msh);
void	signals_handler(int sig, siginfo_t *info, void *context);
void	signal_handler_init(t_msh *msh);
void	chd1_fork(t_msh *msh, t_pipex *chds);
void	mdlchd_fork(t_msh *msh, t_pipex *prev_chds, t_pipex *chds);
void	lstchd_fork(t_msh *msh, t_pipex *prev_chds, t_pipex *chds);
void	kill_children(t_pipex **chds);
void	closing(t_msh *msh, t_pipex **chds);
int		node_strlen(t_pexe *node);
int		struct_strlen(char **array);
void	append_args(t_msh *msh, t_pexe *current, int len_group, int len_option);
void	find_exe(t_msh *msh, char *cmd);
void	sigint(t_msh *msh);
void	sigeof(t_msh *msh);
void	sigquit(t_msh *msh);
void    cmd_exit(t_msh *msh);
void    cmd_echo(t_msh *msh, int g);
void	cmd_pwd(t_msh *msh);
void	cmd_cd(t_msh *msh, int g);
void	cmd_env(t_msh *msh, int g);
void	check_update_tempenv(t_msh *msh, char *cmd);
void	cmd_export(t_msh *msh, int g);
void	check_remove_tempenv(t_msh *msh, char *cmd);
int		remove_var(t_msh *msh, char	*var_name);
void	cmd_unset(t_msh *msh, int g);

/*------- PARSE USER INPUT -------*/
int		parse_main(t_msh *msh);
void	parse_malloc(t_msh *msh);
t_token	*token_malloc(t_msh *msh); //t_parse *prs
t_pexe	*pexe_malloc(t_msh *msh); //t_parse *prs
void	add_node(void **head, void *node, size_t next_off, size_t prev_off);
void	parse_tokenize(t_msh *msh, t_parse *prs);
void	create_modified(t_msh *msh, t_parse *pars);
int		check_quote_ending(char *input, int i);
char	*expand_env(t_msh *msh, int *i, int *j);
void	quote_token(char *temp, int *i);
void	handle_redir(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_pipes(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_logic(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_paran(t_msh *msh, t_parse *pars, int *i, int *j);
void	handle_heredoc(t_msh *msh, t_parse *pars, int *i , int *j);
void	handle_wildcard(t_msh *msh, t_parse *pars, int *i, int *j);
void	make_pexe(t_msh *msh, t_parse *pars);
void	handle_wild_character(t_msh *msh, t_parse *pars, int *i, int *j);
char	*remove_quotes(char *str, int len);
void	update_pexe_main(t_msh *msh, t_pexe *pexe);

/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag, int check);
void	free_parse(t_msh *msh);
void	free_pexe(t_msh *msh);
void	free_mallocs(void *s_ptr, void **d_ptr);
void	free_pipex(t_pipex **children);
void	clear_msh(t_msh *msh, int check, char *msg);

/*-------MINISHELL-------*/
void	check_if_exit(t_msh *msh);
void	minishell_running(t_msh *msh);
void	minishell_start(t_msh *msh, int ac, char **av, char **envp);

#endif