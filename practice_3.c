#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	int				deposit;
	int				*balance;
	pthread_mutex_t	*mutex;
}					t_data;

void	*ft_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(data->mutex);
	*(data->balance) += data->deposit;
	pthread_mutex_unlock(data->mutex);
	free(data);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_num[2];
	pthread_mutex_t	mutex;
	t_data	*data;
	int	balance;
	int	i;

	balance = 0;
	printf("Before : %d\n", balance);
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 2)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (printf("Erreur d'allocation de mémoire\n"), 1);
		data->deposit = (i + 1) * 100;
		data->balance = &balance;
		data->mutex = &mutex;
		pthread_create(&thread_num[i], NULL, ft_thread, data);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(thread_num[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Before : %d\n", balance);
	return (0);
}