#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define REDUCTION 0.25 //reduction amount for each award

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int available = 4000; //keeps track of how much scholarship money is left
static int totalGiven = 0; //keeps track of how much money has been awarded
static void *award(void *data); //function to allocate funds

struct Data {
  const char *id;
};

int main() {
	pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
  struct Data a = { "A" };
  struct Data b = { "B" };
  struct Data c = { "C" };

  pthread_create(&tid1, NULL, award, &a);
  pthread_create(&tid2, NULL, award, &b);
  pthread_create(&tid3, NULL, award, &c);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

	printf("Total given out: %d\n", totalGiven);
  return 0;
}

static void *award(void *val) {
    struct Data *data = val;
    float res;
    while (available > 0) {
        sleep(2);
        pthread_mutex_lock(&mutex); //starts thread protection
        res = ceil(available * REDUCTION);
        totalGiven += res;
        available -= res;
        if (res >= 1)
            printf("%s = %.2f\n", data->id, res);
        pthread_mutex_unlock(&mutex); //ends thread protection
    }

    return 0;
}
