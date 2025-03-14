#include "../includes/philo.h"

int	check_digit_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	check_input(int argc, char **argv)
{
	int		i;
	long	num;
	char	*message;

	i = 1;
	message = "Invalid arguments.\n";
	while (i < argc)
	{
		if (check_digit_input(argv[i]) == 1)
			return (exit_with_error(message, 2));
		num = ft_atoi(argv[i]);
		if (i == 1 && (num < 1 || num > PHILO_MAX_COUNT))
			return (exit_with_error(message, 2));
		else if (i == 5 && (num < 0 || num > INT_MAX))
			return (exit_with_error(message, 2));
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			return (exit_with_error(message, 2));
		i++;
	}
	return (SUCCESS);
}
