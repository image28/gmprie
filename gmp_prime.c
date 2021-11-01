// #gcc gmp_prime.c -O3 -lgmp -lm -o gmp_prime
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <gmp.h>

#define THREADS 8
#define DEBUG 0

int manager(pid_t *pids, int *count);

int main(int argc, char *argv[])
{
    mpz_t res;
    mpz_init (res);
    mpz_t start;
    mpz_init (start);
    mpz_t range;
    mpz_init (range);
    unsigned int check[] = {2, 4, 2, 4, 6, 2, 6, 4};
    unsigned int check2[] = {2, 6, 4, 2, 4, 2};
    mpz_t next;
    mpz_init (next);
    int cur=0;
    int cur2=0;
    unsigned long offset=12;
    int count = 0; // This countiable is created on the stack
    pid_t pids[THREADS];
    int ismanager=0;
    int i=0;
    int e=0;


    if ( argc < 2)
        exit(1);

    mpz_set_str (start,argv[1],0);
    mpz_add_ui(range,range,10);
    for(i=0; i < offset;i++)
    {
        mpz_mul_ui(range,range,10);
    }

    ismanager=manager(&pids[0], &count);

    mpz_mul_ui(range,range,count+1);
    mpz_add(start,start,range);
    mpz_add(range,range,start);

    while( mpz_cmp(res,range) <  0)
    {
        mpz_set(next,start);
        mpz_nextprime (res, start);
        mpz_add_ui(next,next,check[cur]);
        //gmp_printf("%#Zu\n%#Zu\n\n",res,next);

        if ( mpz_cmp(res,next) == 0 )
        {
        #ifdef DEBUG
            printf(".");
        #endif
            cur++;
        }else{
            cur=0;
        }

        mpz_set(next,start);
        mpz_add_ui(next,next,check2[cur2]);

        if ( mpz_cmp(res,next) == 0 )
        {
        #ifdef DEBUG
            printf(".");
        #endif
            cur2++;
        }else{
        #ifdef DEBUG
            if ( cur2 > 0 )
            {
                printf("\n");
            }
        #endif
            cur2=0;
        }

        if ( ( cur == 6 ) || ( cur2 == 6 ) )
        {
            gmp_printf("7 Tuple found %#Zx\n",res);
            exit(0);
        }

        mpz_set(start,res);
    }

    if ( ( ismanager ) && ( count == THREADS ) )
    {

        for(i=0; i < THREADS; i++)
        {
            mpz_set_str (start,argv[1],0);
            mpz_set_str (range,"0",0);
            mpz_add_ui(range,range,10);
            for(e=0; e < offset;e++)
            {
                mpz_mul_ui(range,range,10);
            }
            mpz_mul_ui(range,range,i);
            mpz_add(start,start,range);
            mpz_add(range,range,start);
            gmp_printf("Thread:\n%d\nStart:\n%Zd\nEnd:\n%Zd\n",i,start,range);
        }
        printf("\n");
        waitpid(-1,NULL,0);
    }

    gmp_printf("Limit Reached %#Zd\nThread %d exited\n\n",res,count);

    return(0);
}

int manager(pid_t *pids, int *count)
{
    if ((*(pids+*(count)) = fork()) < 0) {
        perror("Fork failed");
        return(-1);
    }else if (*(pids+*(count)) != 0) {
        *(count)=*(count)+1;
        if ( *(count) < THREADS )
        {
            manager(pids, count);
            return(1);
        }
    }else{
        //printf("%d ",*(count));
        return(0);
    }
}
