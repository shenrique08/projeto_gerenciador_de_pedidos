#include "usuario.h"
#include "restaurante.h"
#include <stdio.h>
#include <stdlib.h>



char menu()
{
    char operando;
    do {
        printf("\n========== RESTAURANTES =========\n\n");
        printf("[1] ;;;;;;\n");
        printf("[2] ;;;;;;\n");
        printf("[3] ;;;;;;\n");
        printf("[4] ;;;;;;\n");
        scanf("%c", &operando);
        getchar();

        if (operando == '4')
            break;

        switch (operando) {
            case '1':
            case '2':
            case '3':
            case '4':
            default:
                break;
                
        }

    } while (operando != '4');


    return operando;
}