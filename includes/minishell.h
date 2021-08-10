#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <term.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/param.h>
# include <string.h>
# include <stddef.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_term
{
	char			**for_perror;
	char			*buf;
	char			**envp;
	char			**argv;
	int				old_status;
	int				error_st;
	int				**pipes;
	int				pipe_total;
	int				fd_file;
	int				fd_in;
	int				fd_out;
	int				fd_here;
	int				is_pipe;
	int				no_pipe;
	int				red_flag;
	int				*pids;
	int				shell_lvl;
	char			**built_in;
	int				err;
	int				status;
}					t_terminal;
int				g_stat_errno;

void			rl_replace_line(char *s, int i);
int				ft_strcmp(char *s1, char *s2);
void			ft_print_errors(t_terminal *terminal, char *s);
char			*ft_save_buf(char *save, char *buf);
void			ft_read_term(t_terminal *terminal);
void			ft_exit_check(t_terminal *terminal, char *s);
void			ft_daughter_execute(t_terminal *terminal, char *save,
					char **s1);
void			ft_check_stat(t_terminal *terminal, char *check_s);
void			ft_first_pipe(t_terminal *terminal, char **s1);
void			ft_middle_pipe(t_terminal *terminal, char **s2, int i);
void			ft_last_pipe(t_terminal *terminal, char **s3);
int				ft_check_builtin(t_terminal *terminal, char **s1);
void			ft_redirects(t_terminal *terminal, int fd_1, int fd_0);
void			ft_exit_status(t_terminal *terminal, int status);
void			ft_cleaner_mass(char **ans);
void			my_handler(int sig);
void			ft_sig_ign(int sig);
void			ft_close_fds(t_terminal *terminal);
char			*ft_strjoin_f(char const *s1, char const *s2);
int				ft_check_red(t_terminal *t, char *save);
void			ft_set_term(int i);
void			ft_echo(char *print, int fd);
void			ft_parser(char *line, t_terminal *a);
void			ft_pwd(int fd);
void			ft_export(t_terminal *a, char *print, int fd);
void			ft_env(t_terminal *a, int fd);
void			ft_unset(t_terminal *a, char *print);
int				ft_spec_char(char c);
void			ft_cd(t_terminal *a, char *print);
void			ft_exit(void);
char			*ft_search(char **env, char *var);
void			ft_call(char *builtin, char *str, t_terminal *a);
int				ft_strcmp(char *s1, char *s2);
void			ft_shlvl(t_terminal *a, int nbr);
int				ft_parse_env(t_terminal *a, char **s, char *line);
void			ft_append(char **s, char c);
int				ft_parse_dquotes(t_terminal *a, char **s, char *line);
int				ft_parse_squotes(char **s, char *line);
int				ft_parse_out(char *line, t_terminal *a);
int				ft_here_redir(t_terminal *a, char *line);
int				ft_parse_in(char *line, t_terminal *a);
void			ft_add_pipe(char *func, char *str, t_terminal *a);
int				ft_parse_arg(char *builtin, char *line, t_terminal *a);
void			ft_parse_pipe(t_terminal *a, char *line);
int				ft_check_here(t_terminal *a);
char			*ft_check_pipe(t_terminal *a, char *line);
#endif
