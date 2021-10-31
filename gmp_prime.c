// #gcc gmp_prime.c -O3 -lgmp -lm -o gmp_prime
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

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

    if ( argc < 3)
        exit(1);

    mpz_set_str (start,argv[1],0);
    mpz_set_str (range,argv[2],0);


    while( mpz_cmp(res,range) <  0)
    {
        mpz_set(next,start);
        mpz_nextprime (res, start);
        mpz_add_ui(next,next,check[cur]);
        //gmp_printf("%#Zu\n%#Zu\n\n",res,next);

        if ( mpz_cmp(res,next) == 0 )
        {
            printf(".");
            cur++;
        }else{
            cur=0;
        }

        mpz_set(next,start);
        mpz_add_ui(next,next,check2[cur2]);

        if ( mpz_cmp(res,next) == 0 )
        {
            printf(".");
            cur2++;
        }else{
            if ( cur2 > 0 )
            {
                printf("\n");
            }
            cur2=0;
        }

        if ( ( cur == 5 ) || ( cur2 == 5 ) )
        {
            gmp_printf("7 Tuple found %#Zx\n",res);
            exit(0);
        }

        mpz_set(start,res);
    }

    return(0);
}

