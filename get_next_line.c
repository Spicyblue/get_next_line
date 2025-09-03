/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okochulo <okochulo@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:41:39 by okochulo          #+#    #+#             */
/*   Updated: 2025/09/03 16:42:32 by okochulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_fill_line_buff(int fd, char *left_char, char *buff);
static char	*_set_line(char *line);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*left_char;
	char		*line;
	char		*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_char);
		free(buff);
		left_char = NULL;
		buff = NULL;
		return (NULL);
	}
	if (!buff)
		return (NULL);
	line = _fill_line_buff(fd, left_char, buff);
	free(buff);
	if (!line)
		return (NULL);
	left_char = _set_line(line);
	return (line);
}

static char	*_set_line(char *line_buff)
{
	char	*left_char;
	ssize_t	i;

	i = 0;
	while (line_buff[i] != '\n' && line_buff[i] != '\0')
		i++;
	if (line_buff[i] == 0 || line_buff[1] == 0)
		return (NULL);
	left_char = ft_substr(line_buff, i + 1, ft_strlen(line_buff) - i);
	if (*left_char == 0)
	{
		free(left_char);
		left_char = NULL;
	}
	line_buff[i + 1] = '\0';
	return (left_char);
}

static char	*_fill_line_buff(int fd, char *left_char, char *buff)
{
	ssize_t	buff_reads;
	char	*tmp;

	buff_reads = 1;
	while (buff_reads > 0)
	{
		buff_reads = read(fd, buff, BUFFER_SIZE);
		if (buff_reads == -1)
		{
			free(left_char);
			return (NULL);
		}
		else if (buff_reads == 0)
			break ;
		buff[buff_reads] = 0;
		if (!left_char)
			left_char = ft_strdup("");
		tmp = left_char;
		left_char = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (left_char);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			chr;

	chr = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == chr)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == chr)
		return ((char *) &s[i]);
	return (NULL);
}
