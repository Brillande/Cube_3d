/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:44:55 by emedina-          #+#    #+#             */
/*   Updated: 2023/05/31 12:13:40 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *txt)
{
	char	*line;
	int		i;

	i = 0;
	if (!txt[i])
		return (NULL);
	while (txt[i] && txt[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (txt[i] && txt[i] != '\n')
	{
		line[i] = txt[i];
		i++;
	}
	if (txt[i] == '\n')
	{
		line[i] = txt[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_delete_first_line(char *txt)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	while (txt[i] && txt[i] != '\n')
		i++;
	if (!txt[i])
	{
		free(txt);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(txt) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (txt[i])
		str[j++] = txt[i++];
	str[j] = '\0';
	free(txt);
	return (str);
}

char	*ft_read_txt(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(left_str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	str = ft_read_txt(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_delete_first_line(str);
	return (line);
}
/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("prueba.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
}  */
