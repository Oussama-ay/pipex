/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:29:33 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/05 08:28:25 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		return (ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n"), 0);
	cat_and_execute(av, env, 0);
	return (0);
}
