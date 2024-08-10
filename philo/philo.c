// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   philo.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/04 19:33:11 by csouita           #+#    #+#             */
// /*   Updated: 2024/08/06 18:26:53 by csouita          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// void *print_message_function( void *ptr )
// {
//      char *message;
//      message = (char *) ptr;
//      printf("%s \n", message);
//      return NULL;
// }

// int main()
// {
//      pthread_t thread1, thread2;
//      char *message1 = "Thread 1";
//      char *message2 = "Thread 2";
//      int  iret1, iret2;

//     /* Create independent threads each of which will execute function */

//      iret1 = pthread_create( &thread1, NULL, print_message_function, NULL);
//      iret2 = pthread_create( &thread2, NULL, print_message_function, NULL);

//      /* Wait till threads are complete before main continues. Unless we  */
//      /* wait we run the risk of executing an exit which will terminate   */
//      /* the process and all threads before the threads have completed.   */

//      pthread_join( thread1, NULL);
//      pthread_join( thread2, NULL); 

//      printf("Thread 1 returns: %d\n",iret1);
//      printf("Thread 2 returns: %d\n",iret2);
//      exit(0);
// }


// #include <pthread.h>
// #include <stdio.h>

// pthread_mutex_t lock;
// int shared_data = 0;

// void *thread_function(void *arg) {
//     pthread_mutex_lock(&lock);
//     // Critical section
//     shared_data++;
//     printf("Thread %ld: shared_data = %d\n", (long)arg, shared_data);
//     pthread_mutex_unlock(&lock);
//     return NULL;
// }

// int main() {
//     pthread_t threads[2];
//     pthread_mutex_init(&lock, NULL);

//     for (long i = 0; i < 2; i++) {
//         pthread_create(&threads[i], NULL, thread_function, (void *)i);
//     }
//     for (int i = 0; i < 2; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     pthread_mutex_destroy(&lock);
//     return 0;
// }

// #include <pthread.h>
// #include <stdio.h>

// #define NUM_THREADS 5
// #define NUM_INCREMENTS 100000

// pthread_mutex_t counter_mutex;
// int counter = 0;

// void *increment_counter(void *arg)
// {
//      (void)*arg;
//     for (int i = 0; i < NUM_INCREMENTS; i++) {
//         pthread_mutex_lock(&counter_mutex);
//         counter++;
//         pthread_mutex_unlock(&counter_mutex);
//     }
//     return NULL;
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     pthread_mutex_init(&counter_mutex, NULL);

//     // Create threads
//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_create(&threads[i], NULL, increment_counter, NULL);
//     }

//     // Wait for all threads to finish
//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     // Clean up
//     pthread_mutex_destroy(&counter_mutex);

//     printf("Final counter value: %d\n", counter);
//     return 0;
// }


#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

atomic_int acnt;
int cnt;

int f(void* thr_data)
{
    (void)thr_data;
    for(int n = 0; n < 1000; ++n) {
        ++cnt;
        ++acnt;
        // for this example, relaxed memory order is sufficient, e.g.
        // atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
    }
    return 0;
}

int main(void)
{
    thrd_t thr[10];
    for(int n = 0; n < 10; ++n)
        thrd_create(&thr[n], f, NULL);
    for(int n = 0; n < 10; ++n)
        thrd_join(thr[n], NULL);

    printf("The atomic counter is %u\n", acnt);
    printf("The non-atomic counter is %u\n", cnt);
}