/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:57:39 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/08 17:20:36 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

void	make_pipe(char *cmd, char **envp);
void	child_process(int *fd, char *cmd, char **envp);
void	parent_process(int *fd);
void	error_exit(char *str, int status);

void	execute_cmd(char *argv, char **envp);
char	*get_path(char *cmd, char **envp);
void	free_split(char **str);

#endif
