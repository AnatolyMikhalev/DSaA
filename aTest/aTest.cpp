
#include <conio.h>
#include <stdio.h>
#include <windows.h>
int main(void)
{
    /* Display message until key is pressed. */
    while (!_kbhit())
    {
        _cputs("Hit me!! ");
        Sleep(200);
    }
    /* Use _getch to throw key away. */
    printf("\nKey struck was '%c'\n", _getch());
}