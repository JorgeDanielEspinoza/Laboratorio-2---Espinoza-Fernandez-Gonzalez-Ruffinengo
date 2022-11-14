#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "auto.h"

int validarNum() // valida numeros positivos
{
    int opcion=0;
    do
    {
        printf("\n\n[Ingrese opcion]: ");
        scanf("%i", &opcion);
        if(opcion<0)
        {
            printf("\n\n*Opcion INCORRECTA*\n");
            system("pause");
            system("cls");
        }
    }
    while(opcion<0);
    return opcion;
}
/// MENU AUTOS
void menuAutos()
{
    printf("\n[1. Chevrolet]\n[2. Fiat]\n[3. Nissan]\n[4. Peugeot]\n");
    printf("[5. Ford]\n[6. Citroen]\n[7. Mercedes-Benz]\n[8. Renault]\n");
    printf("[9. Toyota]\n[10. Volkswagen]\n");
}
/// menu para 'que modificar'
void queModificar()
{
    printf("\n[1. Modificar MODELO]\n[2. Modificar KILOMETROS]\n[3. Modificar ANIO]\n");
    printf("[4. Modificar PRECIO]\n[5. Modificar PATENTE]\n[6. Modificar COMBUSTIBLE]\n\n[0. ATRAS]\n");
    printf("\nOpcion: ");
}
/// menu principal (borrador)
void menu1()
{
    printf("\nBienvenido. Que desea hacer?");
    printf("\n---------------------------------------------------------------------\n");
    printf("  1- Vista administrador.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  2- Vista usuario.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  0- SALIR.");
    printf("\n\nOpcion: ");
}
void menuAdm()
{
    printf("\nQue desea hacer?");
    printf("\n---------------------------------------------------------------------\n");
    printf("  1- Cargar un vehiculo.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  2- Ver vehiculos.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  3- Ver ventas.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  4- Ver Clientes.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  5- Modificar Autos.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  6- Modificar Clientes.");
    printf("\n---------------------------------------------------------------------\n");
    printf("  7- Ver resultados por anio.");
    printf("\n---------------------------------------------------------------------\n\n");
    printf("  0- Atras.\n");
    printf("\nOpcion: ");
}
void menuUsuario()
{
    printf("\n  Que desea hacer?\n");
    printf("\n      1- Ver todos los vehiculos.\n");
    printf("\n      2- Ver vehiculos con filtros.\n");
    printf("\n\n      0- Atras...\n");
    printf("\nIngrese el numero correspondiente a la accion que desea realizar: ");
}
void UsuarioFiltros()
{
    printf("\n  Que quiere hacer?\n");
    printf("\n      1- Ver vehiculos por rango de kilometros.\n");//ver por rango de kilometraje
    printf("\n      2- Ver vehiculos mismo combustible\n");
    printf("\n      3- Ver vehiculos misma marca\n");
    printf("\n      4- Ver vehiculos por rango de precios\n");
    printf("\n\n      0- Atras...\n");
    printf("\nIngrese el numero correspondiente a la accion que desea realizar: ");
}
void menuVentas()
{
    printf("\n  Que quiere hacer?");
    printf("\n---------------------------------------------------------------------\n");
    printf("  1- Ver vehiculos\n");
    printf("\n---------------------------------------------------------------------\n");
    printf("  2- Comprar un vehiculo\n");
    printf("\n---------------------------------------------------------------------\n");
    printf("\n\n    0- Atras...\n");
    printf("\nIngrese el numero correspondiente a la accion que desea realizar: ");
}
void VerVentas()
{
    printf("\n  Que desea hacer?\n");
    printf("      1- Ver todas las ventas.\n");
    printf("      2- Ver ventas por empleado.\n\n");
    printf("      0- Atras\n");
}
void VerVentasPorAnio()
{
    printf("\n  Que desea hacer?\n");
    printf("      1- Ganancia por anio.\n");
    printf("      2- Cantidad de ventas por idEmpleado\n");
    printf("      3- Ganancia por comision por idEmpleado\n");
    printf("\n      0- Atras...\n");
}
void menuClientes()
{
    system("cls");
    printf("\n1- Ver todos los clientes.\n");
    printf("2- Buscar un cliente.\n");
    printf("\n0- Atras.\n");
}
/// MENU AUTOS SWITCH 2
void menuAutosMostrar()
{
    system("cls");
    printf("\n---------------------------------------------------------------------\n");
    printf("\n  Que quiere hacer?\n");
    printf("\n      1- Ver todos los vehiculos.\n");
    printf("\n      2- Ver vehiculos con filtros.\n");
    printf("\n      3- Buscar vehiculo por patente.\n");
    printf("\n      4- Ver vehiculos vendidos.\n");
    printf("\n      5- Ver vehiculos en venta.\n");
    printf("\n---------------------------------------------------------------------\n\n");
    printf("  0- Atras.\n");
    printf("\nOpcion: ");
}
/// MENU FILTROS (switch case autos)
void menuMostrar()
{
    system("cls");
    printf("\n---------------------------------------------------------------------\n");
    printf("\n  Que quiere hacer?\n");
    printf("\n      1- Ver vehiculos misma marca.\n");
    printf("\n      2- Ver vehiculos mismo modelo.\n");
    printf("\n      3- Ver vehiculos misma anio.\n");
    printf("\n      4- Ver vehiculos mismo combustible.\n");
    printf("\n---------------------------------------------------------------------\n\n");
    printf("  0- Atras.\n");
    printf("\nOpcion: ");
}










