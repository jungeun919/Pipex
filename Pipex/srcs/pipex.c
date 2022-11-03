/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:26:14 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/03 18:16:33 by jungchoi         ###   ########.fr       */
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

	execute_cmd(argv[2], envp);
	
	return (0);
}

void	execute_cmd(char *argv, char **envp)
{
	char	**split_cmd;
	char	*cmd;
	char	*path;

	split_cmd = ft_split(argv, ' ');
	cmd = ft_strjoin("/", split_cmd[0]);
	printf("cmd : %s\n", cmd); // ls
	path = get_path(cmd, envp);
	if (!path)
		error_exit("path error\n", 1);
	printf("path : %s\n", path); // /bin/ls
	if (execve(path, split_cmd, envp) == -1)
		error_exit("execve error\n", 127);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**split_path;
	char	*path;
	
	i = 0;
	while (envp[i] && (ft_strncmp("PATH", envp[i], 4) != 0))
		i++;
	// /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		printf("split_path[%d] : %s\n", i, split_path[i]);
		path = ft_strjoin(split_path[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	child_process(int *fd, char **argv, char **envp)
{
	return ;
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		error_exit("open error\n", 1);
	close(fd[0]);
	*envp = 0;
}

void	error_exit(char *str, int status)
{
	ft_putstr_fd(str, 2);
	exit(status);
}

int	execve_test(void)
{
	char *arg1 = "-al";
	char *arg2 = "/etc";
	char *file = "ls";
	char *argv[] = { file, arg1, arg2, NULL };

	execve("/bin/ls", argv, NULL);
	return (0);
}
