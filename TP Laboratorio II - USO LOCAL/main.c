#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "auto.h"
#include "empleado.h"
#include "ventas.h"
#include "cliente.h"

int main()
{
    char patente[6];
    nodoAutos* lista = inicLista();
    int select = 0;
    char seguir = 's';
    celda arreglo[50];
    int validos=0;
    celdaEmpleado adl[50];
    int validosEmpleado=0;
    char archiVenta[]= {"Ventas.bin"}; //Archivo Ventas
    char archiEmpleados[]= {"Empleados.bin"}; //Archivo Empleados
    char archiClientes[]= {"Clientes.bin"}; //Archivo Clientes
    int dimension=100;
    celdaClientes arrayClientes[dimension];
    int validos2=0;
    char dni[9];

    do
    {
        menu1(); // Menu Principal
        scanf("%d", &select);
        switch(select)
        {
        case 1:
        {
            system("cls");
            int flag = 0;
            char seguir2 = 's';
            int select2 = 0;
            do
            {
                menuAdm(); //Menu Administrador
                scanf("%d", &select2);
                switch(select2)
                {
                case 1: //Carga de autos
                {
                    lista = cargarLista(lista);
                    listaArchivo("Autos.bin", lista);
                    break;
                }
                case 2: //Ver autos
                {
                    lista = inicLista();
                    lista = archivoLista(lista, "Autos.bin");
                    char seguir3 = 's';
                    do
                    {
                        menuAutosMostrar();
                        scanf("%d", &select2);
                        switch(select2)
                        {
                        case 1:
                        {
                            mostrarArchivoAutos("Autos.bin");
                            break;
                        }
                        case 2:
                        {
                            elegirFiltro(lista);//muestra por filtro
                            break;
                        }
                        case 3:
                        {
                            printf("Ponga una patente \n");
                            fflush(stdin);
                            gets(patente);
                            buscarAutoPorPatente(lista, patente);
                            break;
                        }
                        case 4:
                        {
                            verVehiculosVendidos(lista);
                            break;
                        }
                        case 5:
                        {
                            verVehiculosEnVenta(lista);
                            break;
                        }
                        case 0:
                        {
                            seguir3 = 'n';
                            break;
                        }
                        default:
                        {
                            printf("\nOpcion incorrecta, ingrese otra.\n");
                            break;
                        }
                        }
                        system("pause");
                        system("cls");
                    }
                    while(seguir3 == 's');
                    break;
                }
                case 3: //Ver ventas
                {
                    system("cls");
                    char seguirCase3='s';
                    int eleccion3;
                    nodoVenta*listaVenta=NULL;
                    do
                    {
                        VerVentas();
                        printf("\n\nIngrese la opcion que desea: \n");
                        scanf("%d",&eleccion3);

                        switch(eleccion3)
                        {
                        case 1:
                            listaVenta=archiVenta_a_lista("Ventas.bin",listaVenta);
                            mostrarListaVenta(listaVenta);
                            break;
                        case 2:
                            validosEmpleado=pasar_de_archivo_a_adl_Empleado(adl,validosEmpleado,"Ventas.bin");
                            mostrarAdlEmpleadoVenta(adl,validosEmpleado);
                            break;
                        case 0:
                        {
                            seguirCase3 = 'n';
                            break;
                        }
                        default:
                            printf("\nOpcion incorrecta, ingrese otra.\n");
                            break;
                        }
                        system("pause");
                        system("cls");
                    }
                    while(seguirCase3=='s');
                    break;
                }
                case 4: //Ver clientes
                {
                    char seguirCase4 = 's';
                    do
                    {
                        menuClientes();
                        scanf("%d", &select2);
                        switch(select2)
                        {
                        case 1:
                        {
                            validos2 = archToArrListaCliente("Ventas.bin", arrayClientes, dimension);
                            mostrarArrListaCliente(arrayClientes, validos2);
                            break;
                        }
                        case 2:
                        {
                            system("cls");
                            printf("Ingrese un dni para buscar: \n");
                            fflush(stdin);
                            gets(dni);
                            system("cls");
                            validos2 = archToArrListaCliente("Ventas.bin", arrayClientes, dimension);
                            buscarClienteXDni(arrayClientes, validos2, dni);
                            break;
                        }
                        case 0:
                        {
                            seguirCase4 = 'n';
                            break;
                        }
                        default:
                        {
                            printf("\nOpcion incorrecte, ingrese otra...\n");
                            break;
                        }
                        }
                        system("pause");
                        system("cls");
                    }
                    while(seguirCase4 == 's');
                    break;
                }
                case 5: //Modificar autos
                {
                    elegirQueModificar("Autos.bin", posicion("Autos.bin"));
                    break;
                }
                case 6: //Modificar clientes
                {
                    elegirQueModificarCliente("Clientes.bin", posicion2("Clientes.bin"));
                    break;
                }
                case 7://Ver resultados por año
                {
                    system("cls");
                    nodoVenta*lista=NULL;
                    lista=archiVenta_a_lista("Ventas.bin",lista);
                    char seguirCase7='s';
                    int Case7;
                    int resultado;
                    char anio[5];
                    int cantidad;
                    int cantRegistro;
                    int id;
                    do
                    {
                        VerVentasPorAnio();
                        printf("\n\nIngrese la opcion que desea: ");
                        scanf("%d",&Case7);

                        switch(Case7)
                        {
                        case 1:
                            system("cls");
                            printf("ingrese anio de venta\n");
                            fflush(stdin);
                            scanf("%s",anio);
                            resultado=sumatoriaPorAnio(lista,anio);
                            if(resultado==0)
                            {
                                printf("No se adjudicaron ventas a este anio\n");
                            }
                            else
                            {
                                printf("El resultado del anio fue de: %d\n",resultado);
                            }
                            break;
                        case 2:
                            system("cls");
                            cantRegistro=sizesEmpleado("Empleados.bin");
                            printf("Ingrese el ID del empleado a buscar\n");
                            scanf("%d",&id);
                            while(id>cantRegistro)
                            {
                                printf("Error! Ingrese otro ID del 1 al %d\n",cantRegistro);
                                scanf("%d",&id);
                            }
                            validosEmpleado=pasar_de_archivo_a_adl_Empleado(adl,validosEmpleado,"Ventas.bin");
                            cantidad=cantidadVentaxID (adl,validosEmpleado,id);
                            if(cantidad>0)
                            {
                                printf("\nCantidad de ventas:%d\n\n",cantidad);
                            }
                            else
                            {
                                printf("\nEl empleado buscado no tiene ventas\n");
                            }
                            break;
                        case 3:
                            system("cls");
                            cantRegistro=sizesEmpleado("Empleados.bin");
                            printf("Ingrese el ID del empleado a buscar\n");
                            scanf("%d",&id);
                            while(id>cantRegistro)
                            {
                                printf("Error! Ingrese otro ID del 1 al %d\n",cantRegistro);
                                scanf("%d",&id);
                            }
                            validosEmpleado=pasar_de_archivo_a_adl_Empleado(adl,validosEmpleado,"Ventas.bin");

                            float premio=comision(adl,validosEmpleado,id);

                            printf("La comision por ventas del id:%d es de:%.2f\n",id,premio);

                            break;
                        case 0:
                        {
                            seguirCase7 = 'n';
                            break;
                        }
                        default:
                            printf("\nOpcion incorrecta, ingrese otra.\n");
                            break;
                        }
                        system("pause");
                        system("cls");
                    }
                    while(seguirCase7=='s');

                    break;
                }
                case 0:
                {
                    seguir2 = 'n';
                    break;
                }
                default:
                {
                    printf("\nOpcion incorrecta, ingrese otra.\n");
                    break;
                }
                }
                system("pause");
                system("cls");
            }
            while(seguir2 == 's');
            break;
        }
        case 2: //Menu Usuario
        {
            system("cls");
            char seguir3='s';
            int select3=0;
            do
            {
                menuVentas();//ver vehiculos y comprar vehiculo
                scanf("%d",&select3);
                switch(select3)
                {
                case 1://ver vehiculos
                {
                    system("cls");
                    char seguir4='s';
                    int select4=0;
                    do
                    {
                        menuUsuario();
                        scanf("%d",&select4);

                        switch(select4)
                        {
                        case 1:
                        {
                            //ver todos los vehiculos
                            mostrarArchivoAutosEnVenta("Autos.bin");
                            break;
                        }
                        case 2:
                        {
                            //ver vehiculos por filtros
                            system("cls");
                            char seguir5 = 's';
                            int select5=0;
                            do
                            {
                                UsuarioFiltros();//1 ver por categoria - 2 combustible - 3 marca - 4 modelo
                                scanf("%d",&select5);
                                switch(select5)
                                {
                                case 1:
                                {
                                    system("cls");
                                    int km1,km2;
                                    printf("\n\nIngrese kilometraje minimo: ");
                                    scanf("%d",&km1);
                                    printf("\n\nIngrese kilometraje maximo: ");
                                    scanf("%d",&km2);
                                    lista=pasar_de_archivo_a_lista_doble("Autos.bin",lista);
                                    RangoKm(lista,km1,km2);
                                    break;
                                }
                                case 2:
                                {
                                    system("cls");
                                    int combustible;
                                    puts("1 - Nafta\n");
                                    puts("2 - Gasoil\n");
                                    puts("3 - Electrico");
                                    printf("Ingrese el numero deseado: ");
                                    scanf("%d",&combustible);
                                    switch(combustible)
                                    {
                                    case 1:
                                    {
                                        system("cls");
                                        validos=pasar_de_archivo_a_adl(arreglo,50,"Autos.bin");
                                        mostrarlistaCombustible(arreglo,validos,"Nafta");
                                        break;
                                    }
                                    case 2:
                                    {
                                        system("cls");
                                        validos=pasar_de_archivo_a_adl(arreglo,50,"Autos.bin");
                                        mostrarlistaCombustible(arreglo,validos,"Gasoil");
                                        break;
                                    }
                                    case 3:
                                    {
                                        system("cls");
                                        validos = pasar_de_archivo_a_adl(arreglo, 50, "Autos.bin");
                                        mostrarlistaCombustible(arreglo, validos, "Electrico");
                                        break;
                                    }
                                    default:
                                    {
                                        printf("\nOpcion incorrecta, ingrese otra.\n");
                                        break;
                                    }
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                                case 3:
                                {
                                    system("cls");
                                    menuAutos();
                                    printf("\nInserte la opcion de la marca que desea ver\n");
                                    int marca;
                                    scanf("%d",&marca);
                                    validos=pasar_de_archivo_a_adl_Marca(arreglo,50,"Autos.bin");
                                    marcaElegida(arreglo,validos,marca);
                                    break;
                                }
                                case 4:
                                {
                                    system("cls");
                                    int a,b;
                                    printf("Ingrese precio minimo: ");
                                    scanf("%d",&a);
                                    printf("Ingrese precio maximo: ");
                                    scanf("%d",&b);
                                    lista=pasar_de_archivo_a_lista_doble("Autos.bin",lista);
                                    Rango(lista,a,b);
                                    break;
                                }
                                case 0:
                                {
                                    seguir5 = 'n';
                                    break;
                                }
                                default:
                                {
                                    printf ("\nOpcion incorrecta, ingrese otra.\n");
                                    break;
                                }
                                }
                                system("pause");
                                system("cls");
                            }
                            while(seguir5 == 's');
                        }
                        case 0:
                        {
                            seguir4 = 'n';
                            break;
                        }
                        }
                        system("pause");
                        system("cls");
                    }
                    while(seguir4=='s');
                    break;
                }
                case 2://comprar un auto
                {
                    system("cls");
                    int buscar;
                    char confirmacion;
                    int flag;
                    lista=NULL;
                    lista=Cargarlista("Autos.bin",lista);
                    if(lista!=NULL)
                    {
                        mostrarAutos(lista);
                        printf("\nIngrese el numero del vehiculo que desea comprar: ");
                        scanf("%d",&buscar);
                        flag=busqueda(lista,buscar);
                        if(flag==1)
                        {
                            printf("Confirmar la compra s/n:\n");
                            fflush(stdin);
                            scanf("%c",&confirmacion);
                            if(confirmacion=='s')
                            {
                                //aca ocurre la venta
                                int flag2;
                                char dni[30];
                                printf("Ingrese su DNI para verificar si es cliente\n");
                                fflush(stdin);
                                scanf("%s",dni);
                                flag2=buscardni("Clientes.bin",dni);
                                if(flag2==1)
                                {
                                    ventaClienteViejo("Autos.bin","Empleados.bin","Ventas.bin","Clientes.bin",lista,buscar,dni);
                                }
                                else
                                {
                                    ventaNuevoCliente("Autos.bin","Empleados.bin","Ventas.bin","Clientes.bin",lista,buscar);
                                }
                            }
                            else
                            {
                                printf("Intente nuevamente...\n");
                            }
                        }
                        else
                        {
                            printf("El numero no es el correcto, intente nuevamente\n");
                        }
                    }
                    else
                    {
                        printf("Lo sentimos, en este momento no hay vehiculos a la venta...\n");
                    }
                    break;
                }
                case 0:
                {
                    seguir3 = 'n';
                    break;
                }
                default:
                {
                    printf ("\nOpcion incorrecta, ingrese otra.\n");
                    break;
                }
                }
                system("pause");
                system("cls");
            }
            while (seguir3=='s');
            break;
        }
        case 0:
        {
            return 0;
            break;
        }
        default:
        {
            printf("\nOpcion incorrecta, ingrese otra.\n");
            break;
        }
        }
        system("pause");
        system("cls");
    }
    while(seguir == 's');

    return 0;
}


