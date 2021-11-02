// #gcc gmp_prime.c -O3 -lgmp -lm -o gmp_prime
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <gmp.h>

#define THREADS 8

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
    unsigned long offset=9;
    int count = 0; // This countiable is created on the stack
    pid_t pids[THREADS];
    int ismanager=0;
    int i=0;
    int e=0;
    uint8_t byte=0;

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

    while(1) // mpz_cmp(res,range) <  0)
    {
        mpz_nextprime (res, start);
        mpz_set(next,res);
        // mpz_export (void *rop, size_t *countp, int order, size_t size, int endian, size_t nails, const mpz_t op)
        mpz_mod_ui(next,next,100);
        mpz_export (&byte, NULL, -1, 1, 0, 0, next);
        //gmp_printf("%u %#Zd\n",byte,res);
        mpz_set(next,start);

        /*  for e in `primesieve -p3 1 900000 | awk -F',' '{print $1}' |cut -c 2- |rev | cut -c1-2 | rev | sort -g | uniq | grep -Ev "^.$" | sed -e s/"^0"/""/`;
            do
                echo -en "( byte%100 == $e ) || ";
            done > primetuples-3300.gmprie */
        if ( ( byte%100 == 1 ) || ( byte%100 == 3 ) || ( byte%100 == 7 ) || ( byte%100 == 11 ) || ( byte%100 == 13 ) || ( byte%100 == 17 ) || ( byte%100 == 21 ) || ( byte%100 == 23 ) || ( byte%100 == 27 ) || ( byte%100 == 31 ) || ( byte%100 == 33 ) || ( byte%100 == 37 ) || ( byte%100 == 41 ) || ( byte%100 == 43 ) || ( byte%100 == 47 ) || ( byte%100 == 51 ) || ( byte%100 == 53 ) || ( byte%100 == 57 ) || ( byte%100 == 61 ) || ( byte%100 == 63 ) || ( byte%100 == 67 ) || ( byte%100 == 71 ) || ( byte%100 == 73 ) || ( byte%100 == 77 ) || ( byte%100 == 81 ) || ( byte%100 == 83 ) || ( byte%100 == 87 ) || ( byte%100 == 91 ) || ( byte%100 == 93 ) || ( byte%100 == 97 ) )
        {
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
                gmp_printf("BLOCK:%#Zd\n",res);
                //exit(0);
                cur=0;
                cur2=0;
            }
        }

        mpz_set(start,res);

    }

    /*if ( ( ismanager ) && ( count == THREADS ) )
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
    }*/

    //gmp_printf("Limit Reached %#Zd\nThread %d exited\n\n",res,count);

    waitpid(-1,NULL,0);

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
