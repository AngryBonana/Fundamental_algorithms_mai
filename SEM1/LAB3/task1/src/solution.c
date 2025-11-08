#include "../include/solution.h"

int minus (int num)
{
    return sum(~num, 1);
}

int sum (int x, int y)
{
    int res = x | y;
    int trans = x & y;
    while (trans != 0)
    {
        int res_p = res;
        res = res ^ trans;
        trans = (res_p & trans) << 1;
    }

    return res;
}

int sub (int x, int y)
{
    return sum(x, minus(y));
}

unsigned int div2 (unsigned int x, unsigned int pow_of_two)
{
    return x >> pow_of_two;
}

unsigned int rem2 (unsigned int x, unsigned int pow_of_two)
{
    int move = sub(32, (int)pow_of_two);
    return (x << move) >> move;
}


int mult (int x, int y)
{
    int copy_x = x;
    int copy_y = y;
    if (copy_y < 0)
    {
        copy_y = minus(copy_y);
        copy_x = minus(copy_x);
    }
    int res = 0;
    for (int i = 0; i < copy_y; i = sum(i, 1))
    {
        res = sum(res, copy_x);
    }

    return res;
}


void convert (const unsigned int num, const unsigned int r, char * buf)
{
    if (r < 1 || r > 5)
    {
        buf[0] = 'N';
        buf[1] = 'a';
        buf[2] = 'N';
        buf[3] = '\0';
        return;
    }

    if (num == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    unsigned int copy_num = num;

    int pos = 0;
    while (copy_num != 0)
    {
        unsigned int rem = rem2(copy_num, r);
        copy_num = div2(copy_num, r);
        

        if (rem > 9)
        {
            buf[pos] = (char)sum(sub(rem, 10), (int)'A');
        }
        else 
        {
            buf[pos] = (char)sum(rem, (int)'0');
        }
        pos = sum(pos, 1);
    }
    buf[pos] = '\0';
    pos = sub(pos, 1);
    for (int i = 0; i < div2(sum(pos, 1), 1); i = sum(i, 1))
    {
        char tmp = buf[i];
        buf[i] = buf[sub(pos, i)];
        buf[sub(pos, i)] = tmp;
    }
}