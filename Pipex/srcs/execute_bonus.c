/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:50:38 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/08 17:08:25 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	execute_cmd(char *argv, char **envp)
{
	char	**split_cmd;
	char	*cmd;
	char	*path;

	split_cmd = ft_split(argv, ' ');
	cmd = ft_strjoin("/", split_cmd[0]);
	path = get_path(cmd, envp);
	if (!path)
		error_exit("path error\n", 1);
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
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
		{
			free_split(split_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(split_path);
	return (NULL);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
