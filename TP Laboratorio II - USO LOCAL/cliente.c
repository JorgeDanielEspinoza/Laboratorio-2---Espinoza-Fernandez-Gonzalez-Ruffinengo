#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "ventas.h"
#include "empleado.h"
#include "auto.h"
stCliente cargarCliente(stCliente nuevoCliente)
{
    printf("Nombre: \n");
    fflush(stdin);
    scanf("%s",nuevoCliente.nombre);
    printf("Apellido: \n");
    fflush(stdin);
    scanf("%s",nuevoCliente.apellido);
    printf("Dni: \n");
    fflush(stdin);
    scanf("%s",nuevoCliente.dni);
    printf("Telefono: \n");
    fflush(stdin);
    scanf("%s",nuevoCliente.telefono);
    printf("Domicilio: \n");
    fflush(stdin);
    scanf("%s",nuevoCliente.domicilio);
    printf("Altura: \n");
    fflush(stdin);
    scanf("%s",nuevoCliente.altura);

    return nuevoCliente;
}
/// PASAR DE ARCHIVO A ARREGLO DE CLIENTES
int archToArrListaCliente(char nombArch[], celdaClientes arr[], int dimension)
{
    system("cls");
    stVentas aux;
    int validos=0;
    FILE* buffer= fopen(nombArch, "rb");
    if(buffer==NULL)
    {
        printf("No se pudo abrir el archivo :( \n");
    }
    else
    {
        while(fread(&aux, sizeof(stVentas), 1, buffer)>0)
        {
            validos=altaDatos(arr, aux, validos);
        }
    }
    fclose(buffer);
    return validos;
}
int altaDatos(celdaClientes arr[], stVentas datos, int validos)
{
    nodoVenta *aux=crearNodo(datos);
    int pos=buscarPosCliente(arr, datos.cliente.dni, validos);
    if(pos==-1)
    {
        validos=agregarCliente(arr, datos, validos);
        pos=validos-1;
    }
    arr[pos].lista=agregarPrinc(arr[pos].lista, aux);
    return validos;
}
int buscarPosCliente(celdaClientes arr[], char datos[], int validos)
{
    int rta=-1;
    int i=0;
    while(i<validos && rta==-1)
    {
        if(strcmp(arr[i].cliente.dni, datos)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}
int agregarCliente(celdaClientes arr[], stVentas datos, int validos)
{
    arr[validos].cliente=datos.cliente;
    arr[validos].lista=inicLista();
    validos++;
    return validos;
}
void buscarClienteXDni(celdaClientes arr[], int validos, char dni[])
{
    int pos=buscarPosCliente(arr, dni, validos);
    if(pos!=-1)
    {
        mostrarCliente2(arr[pos].cliente);
        mostrarLista(arr[pos].lista);
    }
    else
    {
        printf("\n[NO SE ENCONTRO CLIENTE CON ESE DNI]\n");
    }
}
/// modificar clientes
int posicion2(char nombre[]) // le pregunto que auto quiere modificar
{
    system("cls");
    int pos = 1;
    int flag = 0;
    int size = 0;
    stCliente aux;
    printf("\n\t[ELIJA UNA OPCION]\n\n");
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(stCliente), 1, buffer) > 0)
        {
            printf("\t[OPCION %d]\n", pos);
            mostrarClientes(aux);
            pos++;
        }
        size = sizes2(nombre);
        fclose(buffer);
        printf("\n\t[OPCION 0]: Volver atras.\n");
    }
    else
    {
        printf("\t[ARCHIVO INEXISTENTE]");
        flag = 1;
    }
    while(flag == 0)
    {
        printf("\t\t\nOpcion: ");
        scanf("%d", &pos);
        if(pos <= size && pos > -1)
        {
            flag = 1;
        }
        else
        {
            printf("Opcion incorrecta, ingrese otra.\n");
        }
    }
    return pos;
}
int sizes2(char nombre[]) // consigo cantidad de registros
{
    int size=0;
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        fseek(buffer, 0, SEEK_END);
        size = ftell(buffer) / sizeof(stCliente);
        fclose(buffer);
    }
    return size;
}
//modificaciones:
void elegirQueModificarCliente(char nombre[], int pos)
{
    int select = 0;
    char seguir = 's';
    int flag = 0;
    system("cls");
    if(pos != 0)
    {
        do
        {
            system("cls");
            queModificarCliente();
            scanf("%d", &select);
            switch(select)
            {
            case 1:
            {
                flag = 0;
                system("cls");
                modificarNombre(nombre, pos-1);
                break;
            }
            case 2:
            {
                flag = 0;
                system("cls");
                modificarApellido(nombre, pos-1);
                break;
            }
            case 3:
            {
                flag = 0;
                system("cls");
                modificarDNI(nombre, pos-1);
                break;
            }
            case 4:
            {
                flag = 0;
                system("cls");
                modificarTelefono(nombre, pos-1);
                break;
            }
            case 5:
            {
                flag = 0;
                system("cls");
                modificarDomicilio(nombre, pos-1);
                break;
            }
            case 6:
            {
                flag = 0;
                system("cls");
                modificarAltura(nombre, pos-1);
                break;
            }
            case 0:
            {
                flag = 1;
                seguir = 'n';
                break;
            }
            default:
            {
                flag = 1;
                printf("\nOpcion incorrecta, ingrese otra.\n");
                system("pause");
                break;
            }
            }
            if(flag == 0)
            {
                printf("\n\tDesea modificar otro dato? (s/n): ");
                fflush(stdin);
                scanf("%c", &seguir);
            }
        }
        while(seguir == 's');
    }
}
void modificarNombre(char nombre[], int pos)
{
    stCliente aux;
    stCliente correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stCliente)*pos, SEEK_SET);
        fread(&aux, sizeof(stCliente), 1, buffer);
        printf("\nNombre: %s", aux.nombre);
        printf("\nNombre nuevo: ");
        fflush(stdin);
        gets(correcciones.nombre);
        strcpy(aux.nombre, correcciones.nombre);
        fseek(buffer, sizeof(stCliente)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stCliente), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarClientes(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarApellido(char nombre[], int pos)
{
    stCliente aux;
    stCliente correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stCliente)*pos, SEEK_SET);
        fread(&aux, sizeof(stCliente), 1, buffer);
        printf("\nApellido: %s", aux.apellido);
        printf("\nApellido nuevo: ");
        fflush(stdin);
        gets(correcciones.apellido);
        strcpy(aux.apellido, correcciones.apellido);
        fseek(buffer, sizeof(stCliente)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stCliente), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarClientes(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarDNI(char nombre[], int pos)
{
    stCliente aux;
    stCliente correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stCliente)*pos, SEEK_SET);
        fread(&aux, sizeof(stCliente), 1, buffer);
        printf("\nDNI: %s", aux.dni);
        printf("\nDNI nuevo: ");
        fflush(stdin);
        gets(correcciones.dni);
        strcpy(aux.dni, correcciones.dni);
        fseek(buffer, sizeof(stCliente)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stCliente), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarClientes(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarTelefono(char nombre[], int pos)
{
    stCliente aux;
    stCliente correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stCliente)*pos, SEEK_SET);
        fread(&aux, sizeof(stCliente), 1, buffer);
        printf("\nTelefono: %s", aux.telefono);
        printf("\nTelefono nuevo: ");
        fflush(stdin);
        gets(correcciones.telefono);
        strcpy(aux.telefono, correcciones.telefono);
        fseek(buffer, sizeof(stCliente)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stCliente), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarClientes(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarDomicilio(char nombre[], int pos)
{
    stCliente aux;
    stCliente correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stCliente)*pos, SEEK_SET);
        fread(&aux, sizeof(stCliente), 1, buffer);
        printf("\nDomicilio: %s", aux.domicilio);
        printf("\nDomicilio nuevo: ");
        fflush(stdin);
        gets(correcciones.domicilio);
        strcpy(aux.domicilio, correcciones.domicilio);
        fseek(buffer, sizeof(stCliente)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stCliente), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarClientes(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarAltura(char nombre[], int pos)
{
    stCliente aux;
    stCliente correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stCliente)*pos, SEEK_SET);
        fread(&aux, sizeof(stCliente), 1, buffer);
        printf("\nAltura: %s", aux.altura);
        printf("\nAltura nueva: ");
        fflush(stdin);
        gets(correcciones.altura);
        strcpy(aux.altura, correcciones.altura);
        fseek(buffer, sizeof(stCliente)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stCliente), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarClientes(aux);
        system("pause");
        fclose(buffer);
    }
}
void queModificarCliente()
{
    printf("\n[1. Modificar NOMBRE]\n[2. Modificar APELLIDO]\n[3. Modificar DNI]\n");
    printf("[4. Modificar TELEFONO]\n[5. Modificar DOMICILIO]\n[6. Modificar ALTURA]\n\n[0. ATRAS]\n");
    printf("\nOpcion: ");
}
//Funciones de muestra
void mostrarClientes(stCliente cliente)
{
    printf("\n[Nombre]: %s", cliente.nombre);
    printf("\n[Apellido]: %s", cliente.apellido);
    printf("\n[DNI]: %s", cliente.dni);
    printf("\n[Telefono]: %s", cliente.telefono);
    printf("\n[Domicilio]: %s", cliente.domicilio);
    printf("\n[Altura]: %s", cliente.altura);
    printf("\n--------------------------------------------\n");
}
void mostrArchivo(char nombArch[])
{
    FILE* buffer=fopen(nombArch, "rb");
    stVentas aux;
    if(buffer==NULL)
    {
        printf("No se pudo abrir el archivo :( \n");
    }
    else
    {
        while((fread(&aux, sizeof(stVentas), 1, buffer))>0)
        {
            printf("-----------------ID VENTA %i // ANIO: %s-------------------- \n", aux.idVenta, aux.anioDeVenta);
            printf("\n");
            mostrarDatos(aux);
        }
    }
    fclose(buffer);
}
void mostrarDatos(stVentas dato)
{
    printf("-------------------------AUTOMOVIL------------------------------\n");
    printf("Marca: %s \n", dato.automovil.Marca);
    printf("Modelo: %s \n", dato.automovil.Modelo);
    printf("Km: %i \n", dato.automovil.Km);
    printf("Anio: %i \n", dato.automovil.Anio);
    printf("Precio: $ %i \n", dato.automovil.PrecioDeVenta);
    printf("Patente: %s \n", dato.automovil.Patente);
    printf("Combustible: %s \n", dato.automovil.Combustible);
    printf("-------------------------EMPLEADO------------------------------\n");
    printf("ID: %i \n", dato.empleado.idEmpleado);
    printf("Nombre: %s \n", dato.empleado.nombre);
    printf("Apellido: %s \n", dato.empleado.apellido);
    printf("DNI: %i \n", dato.empleado.dni);
    printf("\n");
}
void mostrarCliente2(stCliente dato)
{
    //printf("-------------------------CLIENTE------------------------------\n");
    printf("Nombre: %s \n", dato.nombre);
    printf("Apellido: %s \n", dato.apellido);
    printf("DNI: %s \n", dato.dni);
    printf("Telefono: %s \n", dato.telefono);
    printf("Domicilio: %s \n", dato.domicilio);
    printf("Altura: %s \n", dato.altura);
}
void mostrarArrListaCliente(celdaClientes arr[], int validos)
{
    int i=0;
    while(i<validos)
    {
        printf("-------------------------------%iº CLIENTE------------------------------ \n", i+1);
        mostrarCliente2(arr[i].cliente);
        mostrarLista(arr[i].lista);
        printf("------------------------------------------------------------------------ \n\n");
        i++;
    }
}
void verCliente (stCliente aux)
{
    printf("Nombre: %s\n",aux.nombre);
    printf("Apellido: %s\n",aux.apellido);
    printf("Dni: %s\n",aux.dni);
    printf("Telefono: %s\n",aux.telefono);
    printf("Domicilio: %s\n",aux.domicilio);
    printf("Altura: %s\n",aux.altura);
}
void mostrarCliente (char nombre_archivo[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    stCliente aux;
    if(archivo)
    {
        while(fread(&aux,sizeof(stCliente),1,archivo)>0)
        {
            verCliente(aux);
        }
        fclose(archivo);
    }
}
void mostrarLista(nodoVenta *lista)
{
    nodoVenta *seg=lista;
    int i=1;
    while(seg!=NULL)
    {
        printf("----------------------------------%iº VENTA-------------------------------- \n\n", i);
        mostrarDatos(seg->venta);
        i++;
        seg=seg->sig;
    }
}


