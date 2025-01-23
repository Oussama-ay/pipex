/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:18 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/23 21:13:13 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	fork_and_execute(t_pipe_data *data, char *cmd, char **env, int next_in)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		dup2(data->input_fd, STDIN_FILENO);
		dup2(data->output_fd, STDOUT_FILENO);
		close(data->input_fd);
		close(data->output_fd);
		if (next_in != -1)
			close(next_in);
		execute_cmd(cmd, env);
	}
	else
	{
		close(data->input_fd);
		close(data->output_fd);
	}
	return (cpid);
}

int	open_file(char *file, int flag, int bonus)
{
	int	fd;

	if (flag == 0)
	{
		if (access(file, F_OK) == -1)
			return (ft_printf("no such file or directory: %s\n", file), -1);
		if (access(file, R_OK) == -1)
			return (ft_printf("permission denied: %s\n", file), -1);
		fd = open(file, O_RDONLY);
	}
	else
	{
		if (access(file, F_OK) != -1)
		{
			if (access(file, W_OK) == -1)
				return ((ft_printf("permission denied: %s\n", file), -1));
			if (bonus)
				fd = open(file, O_WRONLY | O_APPEND);
			else
				fd = open(file, O_WRONLY | O_TRUNC);
		}
		else
			fd = open(file, O_WRONLY | O_CREAT, 0644);
	}
	return (fd);
}

static void	handle_last_command(t_pipe_data *data, char **av, char **env, int b)
{
	int		out_error;
	int		status;
	pid_t	last_pid;

	data->output_fd = open_file(av[1], 1, b);
	if (data->output_fd == -1)
	{
		data->output_fd = open("/dev/null", O_WRONLY);
		out_error = 1;
	}
	else
		out_error = 0;
	last_pid = fork_and_execute(data, av[0], env, -1);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (out_error)
		exit(1);
	exit(WEXITSTATUS(status));
}

void	cat_and_execute(char **av, char **env, int b)
{
	t_pipe_data	data;
	int			pipefd[2];
	int			i;

	data.input_fd = open_file(av[1], 0, b);
	if (data.input_fd == -1)
		data.input_fd = open("/dev/null", O_RDONLY);
	i = 2;
	while (av[i + 2] != NULL)
	{
		pipe(pipefd);
		data.output_fd = pipefd[1];
		fork_and_execute(&data, av[i], env, pipefd[0]);
		data.input_fd = pipefd[0];
		i++;
	}
	if (b)
		unlink(av[1]);
	handle_last_command(&data, av + i, env, b);
}
