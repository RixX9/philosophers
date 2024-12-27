#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_data
{
	int				deposit;
	int				*balance;
	pthread_mutex_t	*mutex;
}				t_data;

void *deposit(void *amount)
{
  t_data	*data;

  data = (t_data *)amount;
  pthread_mutex_lock(data->mutex);
  *(data->balance) += data->deposit;
  pthread_mutex_unlock(data->mutex);
  free(data);
  return (NULL);
}

int main()
{
  pthread_t thread[2];
  pthread_mutex_t	mutex;
  t_data	*data;
  int	i;
  int	balance;

  balance = 0;
  printf("Before: %d\n", balance);
  pthread_mutex_init(&mutex, NULL);
  i = 0;
  while (i < 2)
  {
    data = malloc(sizeof(t_data));
    if (!data)
      return (printf("Erreur d'allocation de mémoire\n"), 1);
    data->deposit = (i + 1) * 200;
    data->balance = &balance;
    data->mutex = &mutex;
    pthread_create(&thread[i], NULL, deposit, data);
    i++;
  }
  i = 0;
  while (i < 2)
  {
  	pthread_join(thread[i], NULL);
	  i++;
  }
  pthread_mutex_destroy(&mutex);
  printf("After: %d\n", balance);
  return 0;
}