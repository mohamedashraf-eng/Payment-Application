#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "Application/application.h"

int main(void)
{
    /** @def: Run the program forever. */
    static uint8_t machine_program_state = 0;

    while(1)
    {
        printf("\n 1. Make new transaction.");
        printf("\n 2. Exit.");
        printf("\n [>]: ");
        machine_program_state = getch();

        switch(machine_program_state)
        {
            case '1': 
                    system("cls");
                    fflush(stdin);
                    appStart(); 
                break;
            case '2': 
                system("cls");
                return 1;   
            default: 
                    system("cls");
                    printf("\n Invalid input.");
                break;
        }
    }

    printf("\n Thanks for using the application.");
    printf("\n Copyrights (c) Mohamed Ashraf Fathy\n");
    return 0;
}