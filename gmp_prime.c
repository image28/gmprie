#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

//0, 2, 4, 2, 4, 6, 2, 6, 4

int main(int argc, char *argv[])
{
    mpz_t res;
    mpz_init (res);
    mpz_t start;
    mpz_init (start);
    mpz_t range;
    mpz_init (range);
    int check[] = {0, 2, 4, 2, 4, 6, 2, 6, 4};
    mpz_t next;
    mpz_init (next);
    int cur=0;

    if ( argc < 3)
        exit(1);

    mpz_set_str (start,argv[1],0);
    mpz_set_str (range,argv[2],0);
    mpz_set(next,start);

    while( mpz_cmp(res,range) <  0)
    {

        mpz_nextprime (res, start);

        mpz_add_ui(next,next,check[cur]);
        if ( mpz_cmp(res,next) == 0 )
            cur++;
        else
            cur=0;

        if ( cur == 7 )
        {
            gmp_printf("7 Tuple found %#Zx\n",res);
            exit(0);
        }

        mpz_set(next,res);
        mpz_set(start,res);
    }

    return(gmp_printf("Reached limit %#Zx\n",res));
}

