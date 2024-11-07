/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coline <coline@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:39:17 by mcoskune          #+#    #+#             */
/*   Updated: 2024/11/07 14:11:47 by coline           ###   ########.fr       */
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
	int		w_count;
	int		**w_pos;
	char	**w_str;
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
	char		*heredoc;
	char		*hd_temp;
	int			envp_flag;
	int			pipe_nb;
	int			flag;
	int			exit_error;
	int			interrupted;
	int			child;
	t_parse		*parse;
	t_pexe		*pexe;
	t_pipex		**chds;
}	t_msh;

/*------- MAIN/CONTROL FUNCTIONS -------*/
void	minishell_start(t_msh *msh, int ac, char **envp);
void	minishell_running(t_msh *msh);
int		check_if_exit(t_msh *msh);

/*------- INITIALIZE -------*/
void	clean_init_chds(t_pipex *chds);
void	clean_init_parse(t_parse *pars);
void	clean_init_token_node(t_token *tkn);
void	clean_init_pexe_node(t_pexe *pexe);
void	clean_msh_init(t_msh *msh);

/*------- UTILS -------*/
int		input_validate(int ac, char **envp);
void	create_path(t_msh *msh, char *exe_cmd);
char	*get_path(char **envp);
char	**set_paths_envp(t_msh *msh);
char	*find_executable_path(t_msh *msh);
char	*set_var_name(char *cmd);
int		input_validate(int ac, char **envp);
void	copy_envp(t_msh *msh, char **envp);
void	remove_node(t_msh *msh, int heredoc, int g);
t_msh	*get_msh_instance(t_msh *new_msh);
int		node_strlen(t_pexe *node);
int		move_node(t_msh *msh);
void	move_group(t_msh *msh);
int		updating_var(char **env_struct, char *var_name, char *cmd);
void	swap(t_pexe *node_a, t_pexe *node_b);
void	check_remove_heredoc(t_msh *msh, int heredoc, int infile, int g);
void	check_heredoc_infile(t_msh *msh);
void	check_double_heredoc(t_msh *msh);
int		check_swapping(t_pexe *current, t_pexe *next);
void	sort_pexe(t_msh *msh);
t_pexe	*head(t_pexe *current);

/*------- EXECUTION -------*/
void	execution(t_msh *msh);
void	check_type(t_msh *msh);
void	command(t_msh *msh, char *cmd);
void	cmd_env(t_msh *msh);
void	cmd_cd(t_msh *msh);
void	cmd_pwd(t_msh *msh);
void	cmd_echo(t_msh *msh);
void	print_echo(t_msh *msh, int flag);
void	cmd_unset(t_msh *msh);
int		remove_var(t_msh *msh, char	*var_name);
void	cmd_export(t_msh *msh);
void	adding_var(t_msh *msh, char *new_var);
int		updating_var(char **env_struct, char *var_name, char *cmd);
void	exe(t_msh *msh);
void	pipe_exe(t_msh *msh, t_pexe *head);
void	clean_child(t_msh *msh);
int		check_wc(t_msh *msh, t_pexe *head);
void	append_args(t_msh *msh, t_pexe *head, int len_group);
void	check_exit_status_cmd(t_msh *msh, int flag);
void	exit_error_addition(t_msh *msh);
void	exit_error_message(t_msh *msh, int len, char *num, char *ex_code);
int		count(t_msh *msh);
int		dollar_expansion(t_msh *msh, int *i, t_type type);
void	closing(t_msh *msh, int nb_chds);
int		kill_children(t_msh *msh, int status, int i);
void	last_fork(t_msh *msh, int i, int nb_chds);
void	mdlchd_fork(t_msh *msh, int i, int nb_chds);
void	chd1_fork(t_msh *msh, int nb_chds);
void	signal_handler_init(t_msh *msh);
void	signals_handler(int sig);
void	sig_do(t_msh *msh, int sig, int i);
void	sigquit(t_msh *msh, int i);
void	sigeof(t_msh *msh);
void	ft_pipex(t_msh *msh);
void	create_pipes(t_msh *msh);
int		create_children(t_msh *msh);
void	close_fds(t_msh *msh, int nb_chds, int current);
void	red_right(t_msh *msh);
void	red_left(t_msh *msh);
void	double_red_right(t_msh *msh);
int		open_heredoc(t_msh *msh);
void	close_redirection(t_msh *msh, int save_sdtout);

/*------- PARSE USER INPUT -------*/
int		parse_main(t_msh *msh);
int		analyse_input(t_msh *msh);
int		request_more_input_cont(t_msh *msh, char *temp);
int		create_modified(t_msh *msh, t_parse *pars);
int		input_to_modified(t_msh *msh);
int		handle_dquote(t_msh *msh, int *i, int *start, int *flag);
char	*expand_env(t_msh *msh, int *i, int flag);
int		expand_dollars(t_msh *msh, int *i);
int		dollar_error(t_msh *msh, int *i);
int		request_more_input(t_msh *msh, t_parse *pars);
int		get_here_doc(t_msh *msh, char *delim, int flag);
void	check_for_here_dollar(t_msh *msh, char *gnl, int fd_temp, int flag);
int		handle_heredoc(t_msh *msh, int *i);
void	remove_quotes(char *str, int len, char *delim);
char	*heredoc_name(t_msh *msh, int *num);
void	parse_malloc(t_msh *msh);
t_token	*token_malloc(t_msh *msh);
t_pexe	*pexe_malloc(t_msh *msh);
void	wild_malloc(t_msh *msh, t_parse *pars);
void	wild_cleanup(t_parse *pars);
void	remove_nodes(t_msh *msh);
int		handle_quote(t_msh *msh, int *i);
void	make_pexe(t_msh *msh, t_parse *pars);
void	handle_pipes(t_msh *msh, t_parse *pars, t_type type);
int		handle_redir(t_msh *msh, t_parse *pars, int *i, t_type type);
void	parse_tokenize(t_msh *msh, t_parse *prs);
void	quote_token(char *temp, int *i);
t_type	check_special(char *str, int *i);
t_type	check_if_qt(char *str, int *i);
int		check_quote_ending(char *input, int i);
void	copy_input_mod(t_msh *msh, char *to_copy, int start, int end);
void	addnode(void *node, void **head, size_t offs_next, size_t offs_prev);

/*------- CLEANUP -------*/
void	exit_cleanup(char *msg, t_msh *msh, int flag, int check);
void	free_parse(t_msh *msh);
void	free_pexe(t_msh *msh);
void	free_mallocs(void *s_ptr, void **d_ptr);
void	free_pipex(t_msh *msh);
void	clear_msh2(t_msh *msh);
void	clear_msh(t_msh *msh, int check, char *msg);
void	handle_message(int check, char *msg);
void	free_envp(t_msh *msh);

#endif
