/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:42:46 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/23 21:13:43 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <wait.h>
# include "ft_printf.h"

typedef struct s_pipe_data
{
	int		input_fd;
	int		output_fd;
	int		is_last;
}	t_pipe_data;

/*  utils_strings.c  */
char	**ft_split(char const *s, char c);
int		free_split(char **result);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);

/*  utils_1.c  */
char	*find_path(char **env);
int		execute_cmd(char *cmd, char **env);
void	print_error(char *msg, char *arg);

/*  utils_2.c  */
int		open_file(char *file, int flag, int b);
void	cat_and_execute(char **av, char **env, int bonus);

#endif
