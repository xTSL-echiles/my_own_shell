/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoddish <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 19:28:02 by eoddish           #+#    #+#             */
/*   Updated: 2021/07/03 17:44:33 by eoddish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_redir(int sig)
{
	(void)sig;
	g_stat_errno = 1;
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	write(1, "  ", 2);
	write(1, "\r", 1);
	rl_redisplay();
}

void	ft_here_redir_3(t_terminal *a, char *buf, int is_expand, int fd)
{
	int		j;
	char	*newbuf;

	j = 0;
	while (buf && buf[j])
	{
		if (buf[j] == '$' && !is_expand)
		{
			newbuf = 0;
			j += ft_parse_env(a, &newbuf, buf + j);
			write(fd, newbuf, ft_strlen(newbuf));
			free(newbuf);
		}
		else
			write(fd, buf + j++, 1);
	}
	write(fd, "\n", 1);
}

void	ft_here_redir_2(t_terminal *a, char *finish, int is_expand)
{
	int		ret;
	int		fd;
	char	*buf;

	ret = 1;
	buf = NULL;
	fd = open("temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		signal(SIGINT, ft_sig_redir);
		free(buf);
		buf = NULL;
		buf = readline("> ");
		if (!buf || !ft_strcmp(finish, buf) || g_stat_errno == 1)
		{
			free(buf);
			break ;
		}
		ft_here_redir_3(a, buf, is_expand, fd);
	}
	signal(SIGINT, ft_sig_ign);
	close(fd);
	if (a->fd_here > 0)
		close(a->fd_here);
	a->fd_here = open("./temp.txt", O_RDONLY);
}

void	ft_here_redir_4(char *line, int *is_expand, int i, char **finish)
{
	if (line[i] == '\"' || line[i] == '\'')
		*is_expand = 1;
	else
		ft_append(finish, line[i]);
}

int	ft_here_redir(t_terminal *a, char *line)
{
	int		i;
	int		is_expand;
	char	*finish;

	i = 0;
	is_expand = 0;
	g_stat_errno = 0;
	while (line && line[i] == ' ')
		i++;
	finish = 0;
	while (line && line[i] && line[i] != ' ')
		ft_here_redir_4(line, &is_expand, i++, &finish);
	if (!finish)
	{
		printf("%s\n",
			"minishell: syntax error near unexpected token `newline'");
		return (i);
	}
	ft_here_redir_2(a, finish, is_expand);
	free (finish);
	return (i);
}
