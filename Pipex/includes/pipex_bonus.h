/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:57:39 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/10 16:55:30 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

void	get_infile(char *limiter);
void	make_pipe(char *cmd, char **envp);
void	child_process(int *fd, char *cmd, char **envp);
void	parent_process(int *fd);
void	error_exit(char *str, int status);

void	execute_cmd(char *argv, char **envp);
char	*get_path(char *cmd, char **envp);
void	free_split(char **str);

// gnl
# define BUFFER_SIZE 10
# define OPEN_MAX 256

void	free_ptr(char **ptr);
char	*ret_line(char **backup);
char	*cut_backup(char **backup);
char	*read_buff(int fd, char **backup);
char	*get_next_line(int fd);

#endif
