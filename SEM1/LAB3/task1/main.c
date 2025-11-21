#include "include/solution.h"
#include <stdio.h>
#include <string.h>

void test (char * name, unsigned int num, int r, char *buf, char * waited)
{
    convert(num, r, buf);
    printf("Test: %-20s : ", name);
    if (!strcmp(buf, waited))
    {
        printf("OK\n");
    }
    else  
    {
        printf("FAILED! waited: %s\t got: %s\n", waited, buf);
    }
}

void test2 ()
{
    char buf[33];
    test("0 to 2", 0, 1, buf, "0");
    test("1 to 2", 1, 1, buf, "1");
    test("-1 to 2", -1, 1, buf, "-1");
    test("2 to 2", 2, 1, buf, "10");
    test("100 to 2", 100, 1, buf, "1100100");
    test("137 to 2", 137, 1, buf, "10001001");
    test("6982 to 2", 6982, 1, buf, "1101101000110");
    printf("\n");
}

void test4 ()
{
    char buf[33];
    test("0 to 4", 0, 2, buf, "0");
    test("1 to 4", 1, 2, buf, "1");
    test("-1 to 4", -1, 2, buf, "-1");
    test("4 to 4", 4, 2, buf, "10");
    test("100 to 4", 100, 2, buf, "1210");
    test("137 to 4", 137, 2, buf, "2021");
    test("6982 to 4", 6982, 2, buf, "1231012");
    printf("\n");
}

void test8 ()
{
    char buf[33];
    test("0 to 8", 0, 3, buf, "0");
    test("1 to 8", 1, 3, buf, "1");
    test("-1 to 8", -1, 3, buf, "-1");
    test("8 to 8", 8, 3, buf, "10");
    test("100 to 8", 100, 3, buf, "144");
    test("137 to 8", 137, 3, buf, "211");
    test("6982 to 8", 6982, 3, buf, "15506");
    printf("\n");
}

void test16 ()
{
    char buf[33];
    test("0 to 16", 0, 4, buf, "0");
    test("1 to 16", 1, 4, buf, "1");
    test("-1 to 16", -1, 4, buf, "-1");
    test("16 to 16", 16, 4, buf, "10");
    test("100 to 16", 100, 4, buf, "64");
    test("137 to 16", 137, 4, buf, "89");
    test("6982 to 16", 6982, 4, buf, "1B46");
    printf("\n");
}


void test32 ()
{
    char buf[33];
    test("0 to 32", 0, 5, buf, "0");
    test("1 to 32", 1, 5, buf, "1");
    test("-1 to 32", -1, 5, buf, "-1");
    test("32 to 32", 32, 5, buf, "10");
    test("100 to 32", 100, 5, buf, "34");
    test("137 to 32", 137, 5, buf, "49");
    test("6982 to 32", 6982, 5, buf, "6Q6");
    printf("\n");
}


void test_dop ()
{
    char buf[33];
    test("r = 0", 12, 0, buf, "NaN");
    test("r = 16", 12, 16, buf, "NaN");
    test("-123 to 2", -123, 1, buf, "-1111011");
    test("2^31-1 to 2", 2147483647, 1, buf, "1111111111111111111111111111111");
    test("2^31-1 to 4", 2147483647, 2, buf, "1333333333333333");
    test("2^31-1 to 8", 2147483647, 3, buf, "17777777777");
    test("2^31-1 to 16", 2147483647, 4, buf, "7FFFFFFF");
    test("2^31-1 to 32", 2147483647, 5, buf, "1VVVVVV");

    printf("\n");
}

int main (void)
{
    printf("TESTING\n\n");
    
    test2();
    test4();
    test8();
    test16();
    test32();
    test_dop();

    printf("END OF TESTING\n");

    return 0;
}