/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:26:14 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/10 19:03:57 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		error_exit("argument error\n", 1);
	if (pipe(fd) == -1)
		error_exit("pipe error\n", 1);
	pid = fork();
	if (pid == -1)
		error_exit("fork error\n", 1);
	else if (pid == 0)
		child_process(fd, argv, envp);
	waitpid(pid, NULL, WNOHANG);
	parent_process(fd, argv, envp);
	return (0);
}

void	child_process(int *fd, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error_exit("open error\n", 1);
	close(fd[0]); // 사용하지 않는 fd close
	if (dup2(infile, STDIN_FILENO) == -1) // 표준입력을 infile로 변경
		error_exit("dup2 error\n", 1);
	close(infile);
	if (dup2(fd[1], STDOUT_FILENO) == -1) // 표준출력을 pipe로 변경
		error_exit("dup2 error\n", 1);
	close(fd[1]);
	execute_cmd(argv[2], envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		error_exit("open error\n", 1);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1) // 표준입력을 pipe로 변경 
		error_exit("dup2 error\n", 1);
	close(fd[0]);
	if (dup2(outfile, STDOUT_FILENO) == -1) // 표준출력을 outfile로 변경
		error_exit("dup2 error\n", 1);
	close(outfile);
	execute_cmd(argv[3], envp);
}

void	error_exit(char *str, int status)
{
	ft_putstr_fd(str, 2);
	exit(status);
}
