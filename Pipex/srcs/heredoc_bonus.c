/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungchoi <jungchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:56:26 by jungchoi          #+#    #+#             */
/*   Updated: 2022/11/14 12:38:47 by jungchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	get_infile(char *limiter, t_info *info)
{
	int		infile;
	char	*line;

	infile = open(".here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		error_exit("open error\n", 1, info);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (line)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			{
				free(line);
				break ;
			}
			write(infile, line, ft_strlen(line));
			write(infile, "\n", 1);
			free(line);
		}
		else
			break ;
	}
	close(infile);
}
