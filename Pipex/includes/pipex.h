/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:26:08 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/03 17:31:10 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libs/libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void	error_exit(char *str, int status);
void	child_process(int *fd, char **argv, char **envp);
void	execute_cmd(char *argv, char **envp);
char	*get_path(char *cmd, char **envp);
int		execve_test(void);

#endif
