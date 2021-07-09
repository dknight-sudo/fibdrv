#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

static long long fib_sequence(long long k)
{
    /* FIXME: use clz/ctz and fast algorithms to speed up */
    long long f[k + 2];

    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= k; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    printf("fib[%lld] = %lld\n",k,f[k]);
    return f[k];
}

long elapse(struct timespec start, struct timespec end)
{
    return ((long) 1.0e+9 * end.tv_sec + end.tv_nsec) -
           ((long) 1.0e+9 * start.tv_sec + start.tv_nsec);
}

static long long fast_doubling(long long k)
{
    int k_len = 31- __builtin_clz(k);
    printf("k: %lld, k_len: %d\n",k,k_len);
    long long a = 0;
    long long b = 1;
    long long t1, t2;
    long long c = k;

    for (int i = k_len; i >= 0; i--){
        t1 = a * (2 * b - a);
        t2 = b*b + a*a;
        a = t1;
        b = t2;
        if ((k & (1 << i))>0) {
            t1 = a + b;
            a = b;
            b = t1;
        }
    }
    printf("fib[%lld] = %lld\n",c,a);
    return a;
}

int main(){
    struct timespec t1, t2;
    for (int i = 2; i < 93; i++){
        
        clock_gettime (CLOCK_REALTIME, &t1);
        (void) fib_sequence(i);
        clock_gettime (CLOCK_REALTIME, &t2);
        printf("%d ", i);
        printf("%ld ",elapse(t1,t2));
        

        clock_gettime (CLOCK_REALTIME, &t1);
        (void) fast_doubling(i);
        clock_gettime (CLOCK_REALTIME, &t2);
        printf("%d ", i);
        printf("%ld\n",elapse(t1,t2));
    }
}