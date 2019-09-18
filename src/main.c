#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char dome[255];
    while (strcmp(dome, "quit\n"))
    {

        printf("OS-Simulator: ");
        fgets(dome, 255, stdin);
        if (!strcmp("clear\n", dome))
        {
            system("cls");
            continue;
        }

        if (!strcmp("memory\n", dome))
        {
            printf("%d out of %d used\n", 4021, 4096);
            continue;
        }
        if (strcmp(dome, "quit\n"))
        {
            printf("Unknown Command enter Help to see all commands\n");
        }
    }
}