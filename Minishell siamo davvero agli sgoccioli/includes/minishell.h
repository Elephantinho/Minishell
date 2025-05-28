/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshahein <mshahein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:34:34 by mshahein          #+#    #+#             */
/*   Updated: 2025/05/28 16:38:09 by mshahein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "../parsing/parsing.h"
# include <signal.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

extern int	g_exit_status;

typedef struct s_tk_division
{
	int		i;
	int		prev_is_whitespace;
	int		start;
	int		quotes_open;
	char	*s;
	int		*arr;
	t_token	*token_list;
}			t_str_tk_division;

typedef struct s_expand_dollar
{
	char	*s;
	int		i;
	t_token	*first;
	int		quotes_open;
	int		i_before_dollar;
	int		deleted_quotes_until;
	t_token	*prev;
	int		start;
	char	*env_content;
	char	*new_tok;
}			t_str;

typedef struct s_execution
{
	int		i;
	int		j;
	int		count;
	int		flag;
	int		cpipe[2];
	int		prevpipe;
	pid_t	pids[256];
	t_token	**first;
	int		heredoc_alredy_done;
	int		heredoc_pipes[2][256];
	int		fd;
}			t_exec;

typedef struct s_exec_no_pipes
{
	char	***env;
	t_token	**token_list;
	int		*exit_code;
	char	*s;
	char	**cmnds;
	int		save_fd_in;
	int		save_fd_out;
	int		heredoc_alredy_done;
	int		fd;
}			t_exec_no_pipes;

// env
char	**copy_env(char **envp);
char	**ft_addenv(char *name, char *value, char ***env);
char	*ft_getenv(char *name, char **env);
void	ft_setenv(char *name, char *value, char ***env);
void	print_env(char **env);
void	free_env(char **env);
int		ft_env_size(char **env);

//cd
void	ft_cd_pars(char **args, char ***envp);
void	ft_cd_null_path(char ***envp);
char	*find_home_path(char **envp);
void	print_cd_error(const char *path);

// builtins
void	ft_export(char **args, char ***env);
void	ft_env(char **env);
void	ft_unset(char **args, char ***env);
void	ft_cd(char *path, char ***envp);
void	handle_minus_n(int *i, int *put_n, char **args);
void	ft_echo(char **args);
void	ft_pwd(void);

//unset
int		is_valid_identifier(char *str);
int		match_env_var(char *env_var, char *name);
int		is_duplicate(char **args, int index);
int		should_remove_var(char *env_var, char **args);
int		count_new_env_size(char **env, char **args);
int		copy_filtered_env(char **env, char **args, char **new_env);
char	**build_new_env(char **env, char **args);
void	print_invalid_identifiers(char **args);

//export
void	print_export(char **env);
void	print_export_error(char *arg);
void	handle_assignment(char *arg, char ***env);
void	handle_no_assignment(char *arg, char ***env);
void	copy_without_quotes(char *dst, char *src);
char	*form_str(char *str);
void	swap(char **a, char **b);
void	sort_env(char **env);
char	**ft_copy_matrix(char **matrix);
int		verify(char *str);
int		count_clean_length(char *str);
void	free_mat(char **mat);
void	print_export_line(char *var);

//exit
void	close_fds_for_exit_no_pipes(t_exec_no_pipes *st);
int		check_if_arg_of_exit_is_numeric(char ***args, \
								t_token **arr_of_lists, char **env, int j);
void	ft_exit(char ***args, t_token **arr_of_lists, \
											char **env, int *exit_code);
int		check_if_arg_of_exit_is_numeric_no_pipes(char ***args, \
										t_exec_no_pipes *st, char **env, int j);
void	ft_exit_no_pipes(char ***args, t_exec_no_pipes *st, char **env, \
																int *exit_code);

//check ambig redirection
void	check_ambig_redirect(t_token **tokens, char **env);
void	check_ambig_redirect_h(char *s, int i, t_token **tks, char **env);

void	expand_dollar(t_token **tks, char **env);

//create token
void	create_token(char *s, t_token **token_list, int token_type, \
												t_str_tk_division *strct);
void	check_synt_err_free(char *s, t_token **token_list, int *arr);
void	check_synt_err_redirect(char *s, int i, t_token **token_list, int *arr);
void	check_synt_err_pipe(char *s, int i, t_token **token_list, int *arr);
void	check_quotes(char *s, int i, int *quotes_open);

//tk_division
void	heredoc_case(t_str_tk_division *strct, t_token **token_list);
void	redirect_input_case(t_str_tk_division *strct, t_token **token_list);
void	syntax_error_at_beginning(char *s, t_token **token_list, int *arr);

void	create_token_base_case(t_str_tk_division *strct, t_token **token_list);
void	base_case(t_str_tk_division *strct);
void	pipe_case(t_str_tk_division *strct, t_token **token_list);
void	append_case(t_str_tk_division *strct, t_token **token_list);
void	redirect_output_case(t_str_tk_division *strct, t_token **token_list);

//take_out_quotes
void	take_out_quotes_h(char **new_tk, int *i, int *len, int *end_of_doll_st);
void	take_out_quotes(char **new_tok, int i, int len, int *end_of_doll_st);

//dollar_special_cases
int		get_last_exit_code(char **env);
void	double_dollar_case(t_str *st, char **env);
void	dollar_qmark_case(t_str *st, char **env);
int		special_cases(t_str *st, char **env);

//get_var_from_env
void	get_variable_from_env(t_str *st, char **env, char *temp);
void	get_part_before_the_dollar(t_str *st, char **env);
int		get_part_after_the_dollar(t_str *st, char **env, char *temp);
char	*expand_dollar_h(t_str *st, char **env);

//expand_dollar
void	expand_dollar_sec_h(t_str *st, t_token **tks);
void	expand_dollar_first_h(t_str *st, t_token **tks, char **env);
void	expand_dollar(t_token **tks, char **env);

//create_arr_of_matrx
/* int		count_n_of_matrx(t_token *token);
int		count_n_of_lines(t_token *tokens);
int		arr_of_matrx_h(t_token **tokens, t_token **first, \
										char ****arr_of_matrx, int *i);
char	***create_array_of_matrix(char *s, char **env, t_token *tokens); */

//free_vari
//void	ft_lstclear_mod_arr_lst(t_token **lst);
void	free_for_exit_no_pipes(char ***args, char **env, t_exec_no_pipes *st);
void	free_for_exit(char ***args, t_token **arr_of_lists, char **env);
void	close_basic_fds_and_exit(int exit_code);
void	ft_lstclear_tok_mod(t_token **lst);
void	free_cmnds(char ***cmnds);
/* void	arr_of_matrx_h_free(t_token **tokens, t_token **first, \
											char ****arr_of_matrx);
void	arr_of_matrx_free(char *s, char **env); */

//parsing_forks
void	second_fork_failed(char *s, int *arr, char **env, int exit_code);
void	second_fork_worked(char *s, int *arr, char **env, t_token **tokens);
t_token	**first_fork_worked(char *s, char **env, int i);
void	second_fork_parsing(char *s, int *arr, char **env, t_token **tokens);
void	first_fork_parsing(char *s, char **env);

int		transl_exit_code(int exit_code);
void	modify_exitcode(char ***env, int exit_code);

/* //signal
void	estat(int i);
void	cntrl_c(int sig);
void	signal_handler_heredoc(int sig); */

//arr_of_lists
int		count_n_of_lists(t_token *token);
void	arr_of_lists_h(t_token **tokens, t_token **first, \
							t_token ***arr_of_lists, int *i);
t_token	**create_arr_of_lists(char *s, t_token **tokens);

//redirections
int		handle_heredoc(char *limiter, char **env);
int		handle_heredocs(t_token **tokens, int *fd, char **env);
void	remove_redir_tokens(t_token **tokens, t_token *prev, t_token *curr);
int		handle_redirections(t_token **tokens, int *heredoc_alredy_done, \
															int *exit_code);
void	free_heredoc_tokens(t_token **tokens);
void	update_heredoc_alredy_done(t_token *tokens, int *heredoc_alredy_done);
int		handle_heredocs(t_token **tokens, int *fd, char **env);
int		handle_heredoc(char *limiter, char **env);

//handle_pipes_and_free_for_execution
void	free_arr_of_lists(t_token **arr_of_lists, int count, int flag);
void	init_hereoc_pipes(t_exec *st);
void	close_heredoc_pipes_first(t_exec *st);
void	close_heredoc_pipes(t_exec *st, int flag);
void	upd_pipe_in_exec(t_token **arr_of_lists, t_exec *st);

//execution_child
void	execute_mod(char **cmds, char ***env, int *exit_code);
void	built_in_or_execute_h(char ***env, t_token **arr_of_lists, \
									char	**cmnds, int *exit_code);
char	**built_in_or_execute(char ***env, t_token **arr_of_lists, \
									t_token **tokens, int *exit_code);
void	free_arr_of_lists(t_token **arr_of_lists, int count, int flag);
void	child_in_execution(t_token **arr_of_lists, t_exec *st, \
											char ***env, int *status);

//execution.c
int		do_heredoc(t_token **arr_of_lists, t_exec *st, char ***env);
int		exec_part_before_fork(t_token **arr_of_lists, t_exec *st, int *status);
void	init_t_exec(t_token **arr_of_lists, t_exec *st);
void	ft_execution_h(t_token **arr_of_lists, t_exec *st, \
											char ***env, int *status);
void	ft_execution(t_token **tokens, char ***env, int *status);

//execution without pipe
char	**built_in_or_execute_no_pipes(char ***env, t_token **tokens, \
														int *exit_code);
void	execute_mod_no_pipes_case(char ***cmds, char ***env, int *exit_code, \
														t_exec_no_pipes *s);

//pipe
void	write_no_such_file_or_dir(char *cmd, int *exit_code);
int		is_directory(char *path, char *cmd, int *exit_code);
char	*find_path(char *cmd, char ***env, int *exit_code);
char	*getenv_path(char **env);
void	free_paths(char **paths);
char	*build_path(char *dir, char *cmd, int *exit_code);
char	**get_paths_from_env(char ***env, char *cmd, int *exit_code);
char	*find_command_in_paths(char *cmd, char **paths, int *exit_code);
char	*check(char *full_path, char *cmd, char **paths, int *exit_code);

t_token	**parsing(char *s, char ***env, int *exit_code_pars);

//create_matrix
char	**create_matrix_and_free_list(t_token **tokens, \
							t_token **first, char ***matrx, char ***env);

//signals
void	sigquit_handler(int sig);
void	sigint_handler(int sig);
void	sigint_handler_second(int sig);

//execute_no_pipe_h
void	init_built_in_of_exec_no_pipes(char ***env, t_token **token_list, \
										int *exit_code, t_exec_no_pipes *st);
void	handle_cntrl_c_in_exec_no_pipe(t_exec_no_pipes *st);
void	reset_stdin_stdout_in_exec_no_pipe(t_exec_no_pipes *st);

#endif
