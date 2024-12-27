#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_mutex {
	int	thread_num;
	pthread_mutex_t	*mutex;
}	t_mutex;


void	*ft_pthread(void *arg)
{
	t_mutex	*data;

	data = (t_mutex *)arg;
	pthread_mutex_lock(data->mutex);
	printf("Thread %d en cours d'exécution\n", data->thread_num);
	pthread_mutex_unlock(data->mutex);
	free(data);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_id[2];
	pthread_mutex_t	mutex;
	t_mutex	*data;
	int	i = 0;
	
	pthread_mutex_init(&mutex, NULL);
	while (i < 2)
	{
		data = malloc(sizeof(t_mutex));
		if (!data)
			return (printf("Erreur d'allocation de mémoire\n"), 1);
		data->thread_num = i + 1;
		data->mutex = &mutex;
		pthread_create(&thread_id[i], NULL, ft_pthread, data);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (printf("Thread terminé\n"), 0);
}