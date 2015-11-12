/************************************************************/
/*                                                          */
/* Created by Ryan Collins 2012-2015, use at your own risk. */
/*                                                          */
/************************************************************/

#include <stdio.h>
#include "calculator.h"

#include <stdlib.h>
#include <time.h>

static const char operators[] = {
    '+', '-', '*', '/', '^', 'R',
};

const op_ptr functions[] = {
    add,
    subtract,
    multiply,
    divide,

    power,
    root,
};

int main(void)
{
    size_t i;
    double num1, num2;

    srand(time(NULL));
    for (;;)
    {
        fputs("Please enter a number:  ", stdout);
        num1 = carry_in();

        fputs("Please enter another number:  ", stdout);
        num2 = carry_in();

        for (i = 0; i < sizeof(functions) / sizeof(op_ptr); i++)
            printf(
                "%g %c %g = %g\n",
                num1, operators[i], num2,
                functions[i](num1, num2)
            );

        if (num1 < 0)
            puts("Error: cannot find the square root of a number less than 0");
        else
            printf("The square root of %g is %g.\n", num1, root(num1, 2));

        if (num2 < 0)
            puts("Error: cannot find the square root of a number less than 0");
        else
            printf("The square root of %g is %g.\n", num2, root(num2, 2));

/*
 * integer-precision factorials
 */
        if (num1 >= 0)
            printf(
                "The factorial of %lu is %lu.\n",
                (unsigned long)num1,
                factorial((unsigned long)num1)
            );
        if (num2 >= 0)
            printf(
                "The factorial of %lu is %lu.\n",
                (unsigned long)num2,
                factorial((unsigned long)num2)
            );

        printf("%g to the power of %g is %g.\n", num2, num1, power(num2, num1));

        if (num1 == num2)
            puts("The two numbers are equal");
        if (num1 > num2)
            printf("%g is larger than %g.\n", num1, num2);
        if (num1 < num2)
            printf("%g is larger than %g.\n", num2, num1);

        printf("Random number of the day is:  %i\n", rand());
        puts("----------------------------------");
    }
    return 0;
}

static double carry_in(void)
{
    static char temp_buffer[32];
    size_t i;

    for (i = 0; i < sizeof(temp_buffer); i++)
    {
        int character;

        character = getchar();
        if (character == '\n')
            break;
        if (character == EOF)
        {
            fputs("scan_long:  unexpected EOF\n", stderr);
            break;
        }
        temp_buffer[i] = (char)character;
    }

    if (i >= sizeof(temp_buffer))
    {
        fputs("scan_long:  evaded buffer overrun\n", stderr);
        i = sizeof(temp_buffer) - 1;
    }
    temp_buffer[i] = '\0';
    return strtod(temp_buffer, NULL);
}