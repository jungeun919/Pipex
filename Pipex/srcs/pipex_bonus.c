/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:59:56 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/14 12:35:42 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;

	set_infile_and_outfile(argc, argv, &info);
	if (dup2(info.infile, STDIN_FILENO) == -1)
		error_exit("dup2 error\n", 1, &info);
	close(info.infile);
	unlink(".here_doc_temp");
	while (info.idx < argc - 2)
	{
		make_pipe(argv[info.idx], envp);
		info.idx++;
	}
	if (dup2(info.outfile, STDOUT_FILENO) == -1)
		error_exit("dup2 error\n", 1, NULL);
	execute_cmd(argv[argc - 2], envp);
	return (0);
}

void	set_infile_and_outfile(int argc, char **argv, t_info *info)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			error_exit("argument error\n", 1, NULL);
		info->is_heredoc = 1;
		get_infile(argv[2], info);
		info->infile = open(".here_doc_temp", O_RDONLY);
		info->outfile = open(argv[argc - 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (info->infile == -1 || info->outfile == -1)
			error_exit("open error\n", 1, info);
		info->idx = 3;
	}
	else
	{
		if (argc < 5)
			error_exit("arguments error\n", 1, NULL);
		info->is_heredoc = 0;
		info->infile = open(argv[1], O_RDONLY);
		info->outfile = open(argv[argc - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (info->infile == -1 || info->outfile == -1)
			error_exit("open error\n", 1, info);
		info->idx = 2;
	}
}

void	make_pipe(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe error\n", 1, NULL);
	pid = fork();
	if (pid == -1)
		error_exit("fork error\n", 1, NULL);
	if (pid == 0)
		child_process(fd, cmd, envp);
	waitpid(pid, NULL, WNOHANG);
	parent_process(fd);
}

void	child_process(int *fd, char *cmd, char **envp)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit("dup2 error\n", 1, NULL);
	close(fd[1]);
	execute_cmd(cmd, envp);
}

void	parent_process(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit("dup2 error\n", 1, NULL);
	close(fd[0]);
}
