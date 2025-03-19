/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:47:48 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/17 14:34:40 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

char	*get_path(char **cmd, char *paths)
{
	int		i;
	char	*tmp;
	char	**s_paths;

	if (!paths || !*cmd)
		return (NULL);
	(1) && (s_paths = ft_split(paths, ':'), i = 0);
	while (s_paths[i])
	{
		s_paths[i] = ft_strjoin(s_paths[i], "/");
		s_paths[i] = ft_strjoin(s_paths[i], *cmd);
		i++;
	}
	i = 0;
	while (s_paths[i])
	{
		tmp = ft_strdup(s_paths[i]);
		if (access(tmp, X_OK | F_OK) == 0)
			return (free_split(s_paths), tmp);
		(free(tmp), i++);
	}
	ft_printf("command not found: %s\n", *cmd);
	(1) && (free_split(cmd), free_split(s_paths));
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
		exit((free_split(args), ft_printf("permission denied: \n"), 0));
	path = get_path(args, find_path(env));
	execve(path, args, env);
	free_split(args);
	exit(127);
}

void	print_error(char *msg, char *arg)
{
	if (arg)
		ft_printf(msg, arg);
	else
		ft_printf(msg);
	ft_printf("\n");
	exit(1);
}
