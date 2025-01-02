/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:47:48 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/02 09:35:56 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	close_all(int *pipefd, int input_fd, int output_fd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(input_fd);
	close(output_fd);
}

char	*find_path(char **env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char *paths)
{
	int		i;
	char	**s_paths;

	if (!paths || !cmd)
		return (NULL);
	s_paths = ft_split(paths, ':');
	i = 0;
	while (s_paths[i])
	{
		s_paths[i] = ft_strjoin(s_paths[i], "/");
		s_paths[i] = ft_strjoin(s_paths[i], cmd);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (access(s_paths[i], X_OK | F_OK) == 0)
			return (s_paths[i]);
		i++;
	}
	ft_printf("command not found: %s\n", cmd);
	exit(127);
	return (NULL);
}

int	execute_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	if (!cmd || !env)
		return (0);
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		exit((ft_printf("command not found: \n"), 127));
	path = get_path(args[0], find_path(env));
	execve(path, args, env);
	exit(0);
}
