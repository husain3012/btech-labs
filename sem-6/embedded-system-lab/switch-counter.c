// #include <p89v51rx2.h>
#include <stdio.h>
#include <math.h>

void delay(unsigned int dela)
{
    unsigned int i, j;
    for (i = 0; i <= 1000; i++)
    {
        for (j = 0; j <= dela; j++)
        {
        }
    }
}

void intToBin(int n, int binary[4])
{
    for (int i = 3; i >= 0; i--)
    {
        binary[i] = n % 2;
        n = n / 2;
    }
}

void counter_1(int n_bit)
{
    // RxD = 0;
    // TxD = 0;
    // WR = 1;
    // RD = 1;
    int binary[4] = {0, 0, 1, 1};
    for (int i = 0; i < (1 << n_bit); i++)
    {
        delay(50);
        intToBin(i, binary);
        printf("%d%d%d%d\n", binary[0], binary[1], binary[2], binary[3]);

        // RxD = mask[0];
        // TxD = mask[1];
        // WR = !mask[2];
        // RD = !mask[3];
        delay(50);
    }
}

void counter(int n_bit)
{
    // 4 LEDs
    for (int i = 0; i < (1 << n_bit); i++)
    {

        delay(50);
        RXD = i & 0x8 ? 1 : 0;
        TXD = i & 0x4 ? 1 : 0;
        WR = i & 0x2 ? 0 : 1;
        RD = i & 0x1 ? 0 : 1;
        delay(50);
    }
}

void main(void)
{
    // while (1)
    // {
    //     if (INT0 == 0)
    //         counter(1);
    //     if (INT1 == 0)
    //         counter(2);
    //     if (T0 == 1)
    //         counter(3);
    //     if (T1 == 1)
    //         counter(4);
    // }

    for (int i = 0; i < 4; i++)
    {
        printf("counter %d\n", i + 1);
        counter(i + 1);
    }
}