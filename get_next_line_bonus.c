#include "get_next_line_bonus.h"

int	read_rs(int fd, char *buf, char *l, int rs)
{
	rs = read(fd, buf, BUFFER_SIZE);
	if (rs == -1)
	{
		if (l)
			free(l);
		return (ft_check_rs(buf, rs));
	}
	buf[rs] = '\0';
	return (rs);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*l[10240];
	int			rs;

	rs = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || !line || BUFFER_SIZE <= 0 || fd < 0)
		return (ft_check_rs(buf, -1));
	while (rs)
	{
		if (ft_strchr(l[fd], '\n') != NULL)
			break ;
		rs = read_rs(fd, buf, l[fd], rs);
		if (rs == -1)
			return (-1);
		l[fd] = ft_strjoin(l[fd], buf);
		if (!l[fd])
			return (ft_check_rs(buf, -1));
	}
	*line = ft_substr(l[fd], 0, strl(l[fd], '\n'), 0);
	l[fd] = ft_substr(l[fd], strl(l[fd], '\n') + 1,
			(strl(l[fd], '\0') - strl(l[fd], '\n')), 1);
	if (!l[fd] && rs)
		return (ft_check_rs(buf, -1));
	return (ft_check_rs(buf, rs));
}
