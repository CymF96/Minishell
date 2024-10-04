/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcoskune <mcoskune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/10/04 11:36:40 by mcoskune         ###   ########.fr       */
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

typedef enum s_type
{
	BUILTIN,
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
	L_PAR,
	R_PAR,
	OR,
	AND,
	DOLLAR,
	REGULAR,
	S_QT,
	D_QT,
	TEMP,
}	t_type;

typedef struct s_pipex
{
	int		fd[2];
	pid_t	pid;
}	t_pipex;

typedef struct s_token
{
	char			*token;
	int				start_pos;
	int				end_pos;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char	*modified;
	int		size_modified;
	int		no_poi;
	int		l_count;
	int		r_count;
	int		pip_count;
	int		**poi;
	int		here_fd;
	char	*temp;
	int		**wilds;
	t_token	*head;
}	t_parse;

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

typedef struct s_msh
{
	char		*input;
	char		*path;
	char		**envp;
	int			fd[2];
	char		*text;
	char		*heredoc; //not needed I think
	int			envp_flag;
	int			pipe_nb;
	int			flag;
	int			exit_error;
	int			child;
	t_parse		*parse;
	t_pexe		*pexe;
	t_pipex		**chds;
}	t_msh;

/*------- MAIN/CONTROL FUNCTIONS -------*/
void	minishell_start(t_msh *msh, int ac, char **envp);
void	minishell_running(t_msh *msh);
void	check_if_exit(t_msh *msh);

/*------- INPUT_VALIDATE -------*/
int		input_validate(int ac, char **envp);

/*------- INITIALIZE -------*/
void	clean_init_chds(t_pipex *chds);
void	clean_init_parse(t_parse *pars);
void	clean_init_token_node(t_token *tkn);
void	clean_init_pexe_node(t_pexe *pexe);
void	clean_msh_init(t_msh *msh);

/*------- UTILS -------*/
void	copy_envp(t_msh *msh, char **envp);
char	*get_path(char **envp);
char	*set_var_name(char *cmd);
int		updating_var(char **env_struct, char *var_name, char *cmd);
char	*find_executable_path(t_msh *msh);
void	move_group(t_msh *msh);
int		move_node(t_msh *msh);

/*------- EXECUTION -------*/
void	command(t_msh *msh, char *cmd);
void	exe(t_msh *msh);
void	execution(t_msh *msh);
void	check_type(t_msh *msh);
void	check_exit_status_cmd(t_msh *msh, char *cmd);
void	double_red_right(t_msh *msh);
void	red_left(t_msh *msh);
void	red_right(t_msh *msh);
void	ft_pipex(t_msh *msh);
void	signals_handler(int sig);
void	signal_handler_init(t_msh *msh);
void	chd1_fork(t_msh *msh, int nb_chds);
void	mdlchd_fork(t_msh *msh, int i, int nb_chds);
void	last_fork(t_msh *msh, int i, int nb_chds);
void	kill_children(t_msh *msh);
void	closing(t_msh *msh, int nb_chds);
void	close_fds(t_msh *msh, int nb_chds, int current);
int		node_strlen(t_pexe *node);
void	append_args(t_msh *msh, t_pexe *current, int len_group);
void	sigeof(t_msh *msh);
void	cmd_echo(t_msh *msh);
void	cmd_pwd(t_msh *msh);
void	cmd_cd(t_msh *msh);
void	cmd_env(t_msh *msh);
void	adding_var(t_msh *msh, char *new_var);
void	cmd_export(t_msh *msh);
int		remove_var(t_msh *msh, char	*var_name);
void	cmd_unset(t_msh *msh);

/*------- PARSE USER INPUT -------*/
int		parse_main(t_msh *msh);
void	parse_malloc(t_msh *msh);
t_token	*token_malloc(t_msh *msh);
t_pexe	*pexe_malloc(t_msh *msh);
int		analyse_input(t_msh *msh, t_parse *pars);
void	request_more_input(t_msh *msh, t_parse *pars);
t_type	check_special(char *str, int *i);
t_type	check_if_qt(char *str, int *i);
int		check_quote_ending(char *input, int i);
void	create_modified(t_msh *msh, t_parse *pars);
void	input_to_modified(t_msh *msh, t_parse *pars);
void	copy_input_mod(t_msh *msh, char *to_copy, int start, int end);
void	expand_dollars(t_msh *msh, int *i);
char	*expand_env(t_msh *msh, int *i, int flag);
void	handle_paran(t_msh *msh, t_parse *pars, t_type type);
void	handle_logic(t_msh *msh, t_parse *pars, int *i, t_type type);
void	handle_pipes(t_msh *msh, t_parse *pars, t_type type);
void	handle_redir(t_msh *msh, t_parse *pars, int *i, t_type type);
void	handle_wild_character(t_msh *msh, int *i);
void	addnode(void *node, void **head, size_t offs_next, size_t offs_prev);
void	parse_tokenize(t_msh *msh, t_parse *prs);
void	handle_heredoc(t_msh *msh, int *i);
void	get_here_doc(t_msh *msh, char *delim, int flag);
void	remove_quotes(char *str, int len, char *delim);
void	check_for_here_dollar(t_msh *msh, char *gnl, int fd_temp, int flag);
void	make_pexe(t_msh *msh, t_parse *pars);
void	free_parse(t_msh *msh);
void	sort_pexe(t_msh *msh);

/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag, int check);
void	free_parse(t_msh *msh);
void	free_pexe(t_msh *msh);
void	free_mallocs(void *s_ptr, void **d_ptr);
void	free_pipex(t_msh *msh);
void	clear_msh(t_msh *msh, int check, char *msg);
t_pexe	*head(t_pexe *current);
void	handle_message(int check, char *msg);

#endif
