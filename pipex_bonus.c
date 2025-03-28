/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 14:11:43 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/23 21:13:21 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	here_doc(char **av, char **env)
{
	char	*container;
	char	*tmp;
	int		input_fd;
	int		len;

	(1) && (input_fd = open_file(av[2], 1, 0), len = ft_strlen(av[2]));
	ft_printf("here_doc> ");
	(1) && (container = NULL, tmp = get_next_line(0));
	while (tmp && (ft_strncmp(tmp, av[2], len) || tmp[len] != '\n'))
	{
		if (container)
			container = ft_strjoin(container, tmp);
		else
			container = ft_strdup(tmp);
		free(tmp);
		ft_printf("here_doc> ");
		tmp = get_next_line(0);
	}
	free(tmp);
	if (container)
	{
		print_str(container, input_fd);
		(free(container), close(input_fd));
	}
	cat_and_execute(av + 1, env, 1);
}

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		return (ft_printf("At least 5 arguments are required\n"), 0);
	if (!ft_strncmp(av[1], "here_doc", 9) && ac >= 6)
	{
		here_doc(av, env);
		return (0);
	}
	else if (!ft_strncmp(av[1], "here_doc", 9) && ac < 6)
		return (ft_printf("Usage: ./pipex here_doc LIMITER cmd cmd1 file\n"), 0);
	cat_and_execute(av, env, 0);
	return (0);
}
