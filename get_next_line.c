/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-c <aldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:06:37 by aldiaz-c          #+#    #+#             */
/*   Updated: 2022/10/10 14:08:19 by aldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_new_stash(char *stash)
{
	int		index;
	int		y;
	char	*str;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (!stash[index])
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stash) - index + 1));
	if (!str)
		return (NULL);
	index++;
	y = 0;
	while (stash[index])
		str[y++] = stash[index++];
	str[y] = '\0';
	free(stash);
	return (str);
}

char	*ft_get_line(char *stash)
{
	int		index;
	char	*str;

	index = 0;
	if (!stash[index])
		return (NULL);
	while (stash[index] && stash[index] != '\n')
		index++;
	str = malloc(sizeof(char) * (index + 2));
	if (!str)
		return (NULL);
	index = 0;
	while (stash[index] && stash[index] != '\n')
	{
		str[index] = stash[index];
		index++;
	}
	if (stash[index] == '\n')
	{
		str[index] = stash[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		rdd_bytes;

	rdd_bytes = 1;
	buffer = malloc((BUFFER_SIZE +1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && rdd_bytes > 0)
	{
		rdd_bytes = read(fd, buffer, BUFFER_SIZE);
		if (rdd_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rdd_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_new_stash(stash);
	return (line);
}

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("1 line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("2 line [%02d]: %s", i, line);
// 		free(line);
// 		line = get_next_line(fd3);
// 		printf("3 line [%02d]: %s\n", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
