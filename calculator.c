/************************************************************/
/*                                                          */
/* Created by Ryan Collins 2012-2015, use at your own risk. */
/*                                                          */
/************************************************************/

#include <float.h>
#include <math.h>

#include <signal.h>
#include "calculator.h"

real add(real m, real n)
{
    return (m + n);
}
real subtract(real m, real n)
{
    return (m - n);
}
real multiply(real m, real n)
{
    return (m * n);
}
real divide(real m, real n)
{
    int recovered_from_exception;

    signal(SIGFPE, FPU_exception);
    recovered_from_exception = setjmp(CPU_state);
    if (recovered_from_exception) {
        signal(SIGFPE, FPU_exception);
        n = DBL_MIN; /* smallest positive real number */
        m = (m < 0) ? -DBL_MAX : +DBL_MAX;
    } /* Geometric graphs of x/0 look prettiest this way. */
    return (m / n);
}

real power(real m, real n)
{
    return pow(m, n);
}
real root(real radicand, real index)
{
    real mantissa; /* index * 10^x, until it becomes an integer */
    integer i;

    if (radicand == 0)
        return 0; /* divide(0, 0) is too abstract and could be anything. */
    if (index == 0)
        return divide(radicand, 0);

    mantissa = index;
    while (mantissa != (real)((integer)mantissa))
        mantissa *= 10;
    i = (integer)mantissa;

    if (radicand < 0 && i % 2 != 0) /* odd-roots of negative numbers */
        return -power(-radicand, 1 / index);
    return power(radicand, 1 / index);
}

real greatest_common_divisor(real m, real n)
{
    whole a, b;
    whole i, j;
    whole answer;

 /* We don't need to consider negative integers for the factors. */
    m = (m < 0) ? -m : +m;
    n = (n < 0) ? -n : +n;

    a = (whole)m;
    b = (whole)n;
    if (m != a || n != b)
        return 1; /* Non-integers:  We'll guess the GCF is 1. */

    if (a == b)
        return (a);
    j = (a < b) ? b : a;

    answer = 1;
    for (i = 1; i < j; i++)
        if (a % i == 0 && b % i == 0)
            answer = i;
    return (answer);
}
real least_common_multiple(real m, real n)
{
    whole a, b;
    whole answer;

    m = (m < 0) ? -m : +m;
    n = (n < 0) ? -n : +n;

    a = (whole)m;
    b = (whole)n;
    if (m != a || n != b)
        return 1;

    if (a == 0 || b == 0)
        return divide(1, 0);
    answer = (a < b) ? b : a;

    while (answer % a != 0 || answer % b != 0)
        if (++answer == 0)
            return divide(1, 0); /* Attempt to represent positive overflow. */
    return (answer);
}

whole factorial(whole n)
{
    whole answer, old_answer;
    whole i;

    answer = 1;
    for (i = 1; i < n + 1; i++)
    {
        old_answer = answer;
        answer *= i;
        if (answer < old_answer) /* unsigned overflow */
            return 0; /* `n' is too large to store the correct factorial for. */
    }
    return (answer);
}
