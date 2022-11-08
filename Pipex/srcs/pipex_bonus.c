/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:56 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/08 17:51:04 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include <sys/types.h>

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	infile;
	int	outfile;

	if (argc < 5)
		error_exit("program must have more than five arguments\n", 1);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1 || outfile == -1)
		error_exit("open error\n", 1);
	if (dup2(infile, STDIN_FILENO) == -1) // 표준입력을 infile로 변경
		error_exit("dup2 error\n", 1);
	close(infile);
	// if (dup2(outfile, STDOUT_FILENO) == -1) // 표준출력을 outfile로 변경
	// 	error_exit("dup2 error\n", 1);
	close(outfile);
	i = 2;
	while (i < argc - 2)
	{
		fprintf(stderr, "[start] make pipe '%s'\n", argv[i]);
		make_pipe(argv[i], envp);
		fprintf(stderr, "[end] make pipe '%s'\n\n", argv[i]);
		i++;
	}
	fprintf(stderr, "[start] make last pipe '%s'\n\n", argv[argc - 2]);
	printf("[in_parent last pipe] pid : %d \t ppid : %d\n", getpid(), getppid());
	execute_cmd(argv[argc - 2], envp);
	return (0);
}

void	make_pipe(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe error\n", 1);
	fprintf(stderr, "fd[0] : %d \t fd[1] : %d\n", fd[0], fd[1]);
	pid = fork();
	if (pid == -1)
		error_exit("fork error\n", 1);
	if (pid == 0)
	{
		fprintf(stderr, "child start [cmd : '%s']\n", cmd);
		child_process(fd, cmd, envp);
	}
	waitpid(pid, NULL, WNOHANG);
	fprintf(stderr, "waitpid pid : %d\n", pid);
	fprintf(stderr, "parent start [cmd = '%s']\n", cmd);
	parent_process(fd);
}

void	child_process(int *fd, char *cmd, char **envp)
{
	printf("==================== [in_child] pid : %d \t ppid : %d\n", getpid(), getppid());
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 error\n", 1);
	close(fd[1]);
	fprintf(stderr, "[in_child] execve '%s'", cmd);
	execute_cmd(cmd, envp);
}

void	parent_process(int *fd)
{
	printf("[in_parent] pid : %d \t ppid : %d\n", getpid(), getppid());
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
