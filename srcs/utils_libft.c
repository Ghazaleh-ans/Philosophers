#include "../includes/philo.h"

int ft_atoi(const char *str)
{
	int result;
	int sign;
	int i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void ft_putstr_fd(char *s, int fd)
{
	int i;

	if (!s)
		return;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

int exit_with_error(char *text, int signal)
{
	char *message;

	if (text)
		write(2, text, ft_strlen(text));
	if (signal == 1)
		return (SUCCESS);
	else if (signal == 2)
		return (ERROR);
	else
	{
		message = "Unexpected singal: exit with Signal code\n";
		write(2, message, ft_strlen(message));
		return (ERROR);
	}
}
