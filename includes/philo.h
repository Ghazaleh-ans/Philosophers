#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define PHILO_MAX_COUNT 200
# define SUCCESS 0
# define ERROR 1

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	bool			is_eating;
	long long		last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	meal_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_limit;
	bool			simulation_running;
	long long		start_time;
	t_philo			*philos;
	t_fork			*forks;
	pthread_t		*threads;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
}	t_data;

/* init.c */
bool		init_data(t_data *data, int argc, char **argv);
bool		init_mutexes(t_data *data);
bool		init_philos(t_data *data);
bool		init_threads(t_data *data);

/* utils.c */
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		print_status(t_philo *philo, char *status);
void		clean_up(t_data *data);
bool		is_simulation_running(t_data *data);
int			exit_with_error(char *text, int signal);
size_t		ft_strlen(const char *s);
int		check_input(int argc, char **argv);

/* time.c */
long long	get_time_in_ms(void);
void		precise_sleep(long long ms);
long long	time_since_start(t_data *data);

/* philo.c */
void		*philo_routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* monitor.c */
void		*monitor_routine(void *arg);
bool		check_if_philo_died(t_philo *philo);
bool		all_philos_ate_enough(t_data *data);

#endif
