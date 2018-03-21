#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: recover filename");
        return 1;
    }
    FILE *f_in = fopen(argv[1], "rb");
    FILE *f_out;
    int res;
    char buf[512];
    char r1 = 0xff;
    char r2 = 0xd8;
    char mask = 0xe0;
    int ind = -1;
    char fname[10];


    while (!feof(f_in))
    {
        res = fread(buf, 1, 512, f_in);
        char cmp = buf[2] & mask;

        if ((buf[0] == r1) && (buf[1] == r2) && (cmp == mask))
        {
            printf("ok");
            ind++;
            sprintf(fname, "%03d.jpg", ind);
            printf("%s\n", fname);
            if (ind > 0)
            {
                fclose(f_out);
            }
            f_out = fopen(fname, "wb");
        }
        if (ind > -1)
        {
            fwrite(buf, 1, res, f_out);
        }
    }
    fclose(f_in);
    fclose(f_out);
    printf("%s\n", argv[1]);

    return 0;
}