/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:56 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/10 17:33:56 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	infile;
	int	outfile;

	if (argc < 5)
		error_exit("program must have more than five arguments\n", 1);
	
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		get_infile(argv[2]);
		infile = open("here_doc_temp", O_RDONLY);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (infile == -1 || outfile == -1)
			error_exit("open error\n", 1);
		i = 3;
	}
	else
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (infile == -1 || outfile == -1)
			error_exit("open error\n", 1);
		i = 2;
	}
	
	if (dup2(infile, STDIN_FILENO) == -1)
		error_exit("dup2 error\n", 1);
	close(infile);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_exit("dup2 error\n", 1);

	while (i < argc - 2)
	{
		make_pipe(argv[i], envp);
		i++;
	}
	execute_cmd(argv[argc - 2], envp);
	return (0);
}

void	get_infile(char *limiter)
{
	int		infile;
	char	*line;

	infile = open("here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		error_exit("open error\n", 1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(infile, line, ft_strlen(line));
		write(infile, "\n", 1);
		free(line);
	}
	close(infile);
}

void	make_pipe(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe error\n", 1);
	pid = fork();
	if (pid == -1)
		error_exit("fork error\n", 1);
	if (pid == 0)
		child_process(fd, cmd, envp);
	waitpid(pid, NULL, WNOHANG);
	parent_process(fd);
}

void	child_process(int *fd, char *cmd, char **envp)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 error\n", 1);
	close(fd[1]);
	execute_cmd(cmd, envp);
}

void	parent_process(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit("dup2 error\n", 1);
	close(fd[0]);
}

void	error_exit(char *str, int status)
{
	ft_putstr_fd(str, 2);
	exit(status);
}
