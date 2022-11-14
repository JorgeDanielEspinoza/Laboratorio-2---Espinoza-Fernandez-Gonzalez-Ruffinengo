#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_MAX 50
#include "auto.h"
#include "menu.h"

//funciones de muestra

void mostrarArchivoAutos(char nombre[])
{
    system("cls");
    stAutos aux;
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(stAutos), 1, buffer) > 0)
        {
            mostrarAuto(aux);
        }
    }
}
void mostrarAuto(stAutos auto1)
{
    printf("\n[Marca]: %s", auto1.Marca);
    printf("\n[Modelo]: %s", auto1.Modelo);
    printf("\n[Kilometraje]: %d", auto1.Km);
    printf("\n[Anio]: %d", auto1.Anio);
    printf("\n[Precio de venta]: %d", auto1.PrecioDeVenta);
    printf("\n[Patente]: %s", auto1.Patente);
    printf("\n[Combustible]: %s", auto1.Combustible);
    if(auto1.Estado==1)
    {
        printf("\n[Estado]: EN VENTA");
    }
    else
    {
        printf("\n[Estado]: VENDIDO");
    }
    printf("\n--------------------------------------------\n");
}
void mostrarlistaCombustible(celda arreglo[],int validos,char combustible[])
{
    system("cls");
    int pos=buscarCombustible(arreglo,validos,combustible);
    if(pos != -1)
    {
        nodoLista*seg=arreglo[pos].lista;
        while(seg!=NULL)
        {
            mostrarCoche(seg->vehiculo);
            seg=seg->sig;
        }
    }
    else
    {
        printf("\n\nNo se encuentran vehiculos a la venta con ese tipo de combustible...\n");
    }
}
void mostrarCoche (coche autito)
{
    printf("\n[Marca]: %s", autito.Marca);
    printf("\n[Modelo]: %s", autito.Modelo);
    printf("\n[Kilometraje]: %d", autito.Km);
    printf("\n[Anio]: %d", autito.Anio);
    printf("\n[Precio de venta]: %d", autito.PrecioDeVenta);
    printf("\n[Patente]: %s", autito.Patente);
    printf("\n-------------------------------\n");
}
void mostrarlistaMarca(celda arreglo[],int validos,char marca[])
{
    system("cls");
    int pos=buscarMarca(arreglo,validos,marca);

    if(pos==-1)
    {
        puts("No hay autos de esta marca\n");
    }
    else
    {
        nodoLista*seg=arreglo[pos].lista;
        printf("\n---MARCA: %s---\n",arreglo[pos].tipo.Marca);
        seg=arreglo[pos].lista;
        while(seg!=NULL)
        {
            mostrarCoche(seg->vehiculo);
            seg=seg->sig;
        }
    }
}
void mostrarArchivoAutosEnVenta(char nombre[])
{
    system("cls");
    stAutos aux;
    FILE* fp = fopen(nombre, "rb");
    if(fp)
    {
        while(fread(&aux, sizeof(stAutos), 1, fp) > 0)
        {
            if(aux.Estado == 1)
            {
                mostrarAuto(aux);
            }
        }
        fclose(fp);
    }
}
//Funciones de pasajes de Archivo a Estructuras Compuestas
int pasar_de_archivo_a_adl (celda arreglo[],int dimension,char nombre_archivo[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    stAutos aux;
    coche vehiculo;
    int validos=0;
    if(archivo)
    {
        while(fread(&aux,sizeof(stAutos),1,archivo)>0 && validos <= dimension)
        {
            if(aux.Estado == 1)
            {
                vehiculo=cargarcoche(aux.Marca,aux.Modelo,aux.Km,aux.Anio,aux.PrecioDeVenta,aux.Patente,aux.Estado);
                validos=altaTipos(arreglo,validos,vehiculo,aux.Combustible,aux.Marca,aux.Modelo);
            }
        }
        fclose(archivo);
    }
    return validos;
}
int altaTipos(celda arreglo[],int validos,coche vehiculo,char combustible[],char marca[],char modelo[])
{
    nodoLista*nuevonodo=crearnodoL(vehiculo);
    int pos=buscarCombustible(arreglo,validos,combustible);
    if(pos==-1)
    {
        validos=agregarCombustible(arreglo,validos,combustible);
        pos=validos-1;
    }
    arreglo[pos].lista=agregaralfinalL(arreglo[pos].lista,nuevonodo);
    return validos;
}
coche cargarcoche(char marca[],char modelo[],int km, int anio, int precio, char patente[],int estado)
{
    coche nuevo;
    strcpy(nuevo.Marca,marca);
    strcpy(nuevo.Modelo,modelo);
    nuevo.Km=km;
    nuevo.Anio=anio;
    nuevo.PrecioDeVenta=precio;
    strcpy(nuevo.Patente,patente);
    nuevo.Estado=estado;
    return nuevo;
}
nodoLista*agregaralfinalL(nodoLista*lista,nodoLista*nuevonodo)
{
    nodoLista*ultimo;
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        ultimo=buscarultimoL(lista);
        ultimo->sig=nuevonodo;
    }
    return lista;
}
nodoLista*buscarultimoL(nodoLista*lista)
{
    nodoLista*seg=lista;
    while(seg->sig!=NULL)
    {
        seg=seg->sig;
    }
    return seg;
}
int agregarCombustible(celda arreglo[],int validos,char combustible[])
{
    strcpy(arreglo[validos].tipo.Combustible,combustible);
    arreglo[validos].lista=NULL;
    validos++;
    return validos;
}
int buscarCombustible(celda arreglo[],int validos,char combustible[])
{
    int pos=-1;
    int i=0;
    while(i<validos&&pos==-1)
    {
        if(strcmpi(arreglo[i].tipo.Combustible,combustible)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}
nodoLista*crearnodoL(coche vehiculo)
{
    nodoLista*nuevonodo=(nodoLista*)malloc(sizeof(nodoLista));
    nuevonodo->vehiculo=vehiculo;
    nuevonodo->sig=NULL;
    return nuevonodo;
}
/////////////////////////////////////////////////////////////////////////////////////////
int pasar_de_archivo_a_adl_Marca (celda arreglo[],int dimension,char nombre_archivo[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    stAutos aux;
    coche vehiculo;
    int validos=0;
    if(archivo)
    {
        while(fread(&aux,sizeof(stAutos),1,archivo)>0&&validos<dimension)
        {
            if(aux.Estado == 1)
            {
                vehiculo=cargarcoche(aux.Marca,aux.Modelo,aux.Km,aux.Anio,aux.PrecioDeVenta,aux.Patente,aux.Estado);
                validos=altaMarca(arreglo,validos,vehiculo,aux.Combustible,aux.Marca,aux.Modelo);
            }
        }
        fclose(archivo);
    }
    return validos;
}
int altaMarca(celda arreglo[],int validos,coche vehiculo,char combustible[],char marca[],char modelo[])
{
    nodoLista*nuevonodo=crearnodoL(vehiculo);
    int pos=buscarMarca(arreglo,validos,marca);
    if(pos==-1)
    {
        validos=agregarMarca(arreglo,validos,marca);
        pos=validos-1;
    }
    arreglo[pos].lista=agregaralfinalL(arreglo[pos].lista,nuevonodo);
    return validos;
}
int buscarMarca(celda arreglo[],int validos,char marca[])
{
    int pos=-1;
    int i=0;
    while(i<validos&&pos==-1)
    {
        if(strcmpi(arreglo[i].tipo.Marca,marca)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}
int agregarMarca(celda arreglo[],int validos,char marca[])
{
    strcpy(arreglo[validos].tipo.Marca,marca);
    arreglo[validos].lista=NULL;
    validos++;
    return validos;
}
/// de archivo a lista
nodoAutos* archivoLista(nodoAutos* lista, char nombre[])
{
    stAutos aux;
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(stAutos), 1, buffer) > 0)
        {
            lista = agrgarPpioAuto(lista, crearNodoAuto(aux));
        }
        fclose(buffer);
    }
    return lista;
}
/// de lista a archivo
void listaArchivo(char nombre[], nodoAutos* lista)
{
    FILE* buffer = fopen(nombre, "ab");
    if(buffer)
    {
        while(lista)
        {
            fwrite(&lista->autos, sizeof(stAutos), 1, buffer);
            lista = lista->siguiente;
        }
        fclose(buffer);
    }
}
/// carga de lista directamente
nodoAutos* cargarLista(nodoAutos* lista)
{
    char seguir = 's';

    while(seguir == 's')
    {
        lista = agrgarPpioAuto(lista, crearNodoAuto(datosAuto()));
        printf("\nSi desea seguir cargando presione 's': ");
        fflush(stdin);
        scanf("%c", &seguir);
    }
    return lista;
}
//Funciones de interaccion
void marcaElegida(celda arreglo[],int validos,int eleccion)
{
    switch(eleccion)
    {
    case 1:
        mostrarlistaMarca(arreglo,validos,"chevrolet");
        break;
    case 2:
        mostrarlistaMarca(arreglo,validos,"fiat");
        break;
    case 3:
        mostrarlistaMarca(arreglo,validos,"nissan");
        break;
    case 4:
        mostrarlistaMarca(arreglo,validos,"peugeot");
        break;
    case 5:
        mostrarlistaMarca(arreglo,validos,"ford");
        break;
    case 6:
        mostrarlistaMarca(arreglo,validos,"citroen");
        break;
    case 7:
        mostrarlistaMarca(arreglo,validos,"mercedes-benz");
        break;
    case 8:
        mostrarlistaMarca(arreglo,validos,"renault");
        break;
    case 9:
        mostrarlistaMarca(arreglo,validos,"toyota");
        break;
    case 10:
        mostrarlistaMarca(arreglo,validos,"volkswagen");
        break;
    default:
        printf("La opcion solicitada no existe\n");
        break;
    }
}
/// modificar datos del archivo
int posicion(char nombre[]) // le pregunto que auto quiere modificar
{
    system("cls");
    int pos = 1;
    int flag = 0;
    int size = 0;
    stAutos aux;
    printf("\n\t[ELIJA UNA OPCION]\n\n");
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(stAutos), 1, buffer) > 0)
        {
            printf("\t[OPCION %d]\n", pos);
            mostrarAuto(aux);
            pos++;
        }
        size = sizes(nombre);
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
/// FUNCION CORE MODIFICAR
void elegirQueModificar(char nombre[], int pos)
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
            queModificar();
            scanf("%d", &select);
            switch(select)
            {
            case 1:
            {
                flag = 0;
                system("cls");
                modificarModelo(nombre, pos-1);
                break;
            }
            case 2:
            {
                flag = 0;
                system("cls");
                modificarKm(nombre, pos-1);
                break;
            }
            case 3:
            {
                flag = 0;
                system("cls");
                modificarAnio(nombre, pos-1);
                break;
            }
            case 4:
            {
                flag = 0;
                system("cls");
                modificarPrecio(nombre, pos-1);
                break;
            }
            case 5:
            {
                flag = 0;
                system("cls");
                modificarPatente(nombre, pos-1);
                break;
            }
            case 6:
            {
                flag = 0;
                system("cls");
                modificarCombustible(nombre, pos-1);
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
stAutos datosAuto()
{
    int select = 0; // para marcas
    char continuar = 's';

    //int select2 = 0; // para modelos

    stAutos auto1;

    system("cls");
    printf("\n\t\t[DATOS DEL AUTO]\n\n");
    printf("Marca: ");
    do
    {
        menuAutos();
        scanf("%i", &select);
        switch(select)
        {
        case 1:
        {
            strcpy(auto1.Marca, "Chevrolet");
            continuar = 'n';
            break;
        }
        case 2:
        {
            strcpy(auto1.Marca, "Fiat");
            continuar = 'n';
            break;
        }
        case 3:
        {
            strcpy(auto1.Marca, "Nissan");
            continuar = 'n';
            break;
        }
        case 4:
        {
            strcpy(auto1.Marca, "Peugeot");
            continuar = 'n';
            break;
        }
        case 5:
        {
            strcpy(auto1.Marca, "Ford");
            continuar = 'n';
            break;
        }
        case 6:
        {
            strcpy(auto1.Marca, "Citroen");
            continuar = 'n';
            break;
        }
        case 7:
        {
            strcpy(auto1.Marca, "Mercedes-Benz");
            continuar = 'n';
            break;
        }
        case 8:
        {
            strcpy(auto1.Marca, "Renault");
            continuar = 'n';
            break;
        }
        case 9:
        {
            strcpy(auto1.Marca, "Toyota");
            continuar = 'n';
            break;
        }
        case 10:
        {
            strcpy(auto1.Marca, "Volkswagen");
            continuar = 'n';
            break;
        }
        default:
        {
            printf("\n[Opcion incorrecta, ingrese otra]: ");
            break;
        }
        }
        system("pause");
        system("cls");
    }
    while(continuar == 's');

    printf("\nModelo: ");
    fflush(stdin);
    gets(auto1.Modelo);

    printf("\nKilometros: ");
    scanf("%d", &auto1.Km);

    printf("\nAnio: ");
    scanf("%d", &auto1.Anio);

    printf("\nPrecio de venta: ");
    scanf("%d", &auto1.PrecioDeVenta);

    printf("\nPatente: ");
    fflush(stdin);
    gets(auto1.Patente);

    printf("\nCombustible: ");
    fflush(stdin);
    gets(auto1.Combustible);

    auto1.Estado = 1;

    return auto1;
}
/// MODIFICACIONES
void modificarModelo(char nombre[], int pos)
{
    stAutos aux;
    stAutos correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        printf("\nModelo: %s", aux.Modelo);
        printf("\nModelo nuevo: ");
        fflush(stdin);
        gets(correcciones.Modelo);
        strcpy(aux.Modelo, correcciones.Modelo);
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarAuto(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarKm(char nombre[], int pos)
{
    stAutos aux;
    int kmnuevo = 0;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        printf("\nKilometraje: %d", aux.Km);
        printf("\nKilometraje nuevo: ");
        scanf("%d", &kmnuevo);
        aux.Km = kmnuevo;
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarAuto(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarAnio(char nombre[], int pos)
{
    stAutos aux;
    int anioNuevo;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        printf("\nAnio: %d", aux.Anio);
        printf("\nAnio nuevo: ");
        scanf("%d", &anioNuevo);
        aux.Anio = anioNuevo;
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarAuto(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarPrecio(char nombre[], int pos)
{
    stAutos aux;
    int precio;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        printf("\nPrecio de venta: %d", aux.PrecioDeVenta);
        printf("\nPrecio de venta nuevo: ");
        scanf("%d", &precio);
        aux.PrecioDeVenta = precio;
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarAuto(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarPatente(char nombre[], int pos)
{
    stAutos aux;
    stAutos correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        printf("\nPatente: %s", aux.Patente);
        printf("\nPatente nueva: ");
        fflush(stdin);
        gets(correcciones.Patente);
        strcpy(aux.Patente, correcciones.Patente);
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarAuto(aux);
        system("pause");
        fclose(buffer);
    }
}
void modificarCombustible(char nombre[], int pos)
{
    stAutos aux;
    stAutos correcciones;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        printf("\nCombustible: %s", aux.Combustible);
        printf("\nCombustible nuevo: ");
        fflush(stdin);
        gets(correcciones.Combustible);
        strcpy(aux.Combustible, correcciones.Combustible);
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);
        printf("\n\t\t[ARCHIVO MODIFICADO CORRECTAMENTE]\n");
        mostrarAuto(aux);
        system("pause");
        fclose(buffer);
    }
}
//Pasaje de archivo a lista doble
nodoAutos*pasar_de_archivo_a_lista_doble(char nombre_archivo[],nodoAutos*lista)
{
    FILE*archivo=fopen(nombre_archivo,"rb");

    stAutos aux;
    nodoAutos*nuevonodo;
    if(archivo)
    {
        while(fread(&aux,sizeof(stAutos),1,archivo)>0)
        {
            if(aux.Estado == 1)
            {
                nuevonodo=crearNodoAuto(aux);
                lista=agrgarPpioAuto(lista,nuevonodo);
            }
        }
        fclose(archivo);
    }
    return lista;
}
//vista por rangos
void Rango(nodoAutos*lista,int rangoA, int rangoB)
{
    nodoAutos*seg=lista;

    while(seg!=NULL)
    {
        if((seg->autos.PrecioDeVenta>=rangoA)&&(seg->autos.PrecioDeVenta<=rangoB))
        {
            mostrarAuto(seg->autos);
        }
        seg=seg->siguiente;
    }
}
void RangoKm(nodoAutos*lista,int rangoA, int rangoB)
{
    nodoAutos*seg=lista;

    while(seg!=NULL)
    {

        if((seg->autos.Km>=rangoA)&&(seg->autos.Km<=rangoB))
        {

            mostrarAuto(seg->autos);
        }
        seg=seg->siguiente;
    }
}
/// SWITCH CASE 2--VER AUTOS CON FILTROS
void elegirFiltro(nodoAutos *listaAutos)
{
    int option=0;
    char seguir='s';
    char datoChar[30];
    int datoInt=0;
    int flag=0;
    do
    {
        menuMostrar();
        scanf("%i", &option);
        switch(option)
        {
        case 1:
        {
            system("cls");

            escogerMarca(datoChar);

            flag = BuscarDatoChar(listaAutos, datoChar);
            if(flag!=1)
            {
                printf("La marca ingresada no se encuentra en el sistema. Intente de nuevo\n");
            }
            break;
        }
        case 2:
        {
            system("cls");
            printf("\nQue Modelo en especifico desea ver\n");
            printf("\nIngrese Modelo: ");
            fflush(stdin);
            gets(datoChar);

            flag = BuscarDatoChar(listaAutos, datoChar);

            if(flag!=1)
            {
                printf("El Modelo ingresado no se encuentra en el sistema. Intente de nuevo\n");
            }
            break;
        }

        case 3:
        {
            system("cls");
            printf("\nQue anio de auto en especifico desea ver?\n");
            printf("\nIngrese el anio: ");
            scanf("%i", &datoInt);
            flag = buscarDatoInt(listaAutos, datoInt);
            if(flag!=1)
            {
                printf("El anio ingresado no se encuentra en el sistema. Intente de nuevo\n");
            }
            break;
        }
        case 4:
        {
            int select = 0;
            char seguir2 = 's';
            system("cls");
            printf("\nIngrese tipo de combustible: \n");
            printf("  1- Gasoil\n");
            printf("  2- Nafta\n");
            printf("  3- Electrico\n");
            do
            {
                printf("\nOpcion: ");
                scanf("%d", &select);
                switch(select)
                {
                case 1:
                {
                    strcpy(datoChar, "Gasoil");
                    seguir2 = 'n';
                    break;
                }
                case 2:
                {
                    strcpy(datoChar, "Nafta");
                    seguir2 = 'n';
                    break;
                }
                case 3:
                {
                    strcpy(datoChar, "Electrico");
                    seguir2 = 'n';
                    break;
                }
                default:
                {
                    printf("\nOpcion incorrecta, ingrese otra...");
                    break;
                }
                }
            }
            while(seguir2 == 's');

            flag = BuscarDatoChar(listaAutos, datoChar);
            if(flag!=1)
            {
                printf("El tipo de combustible no se encuentra en el sistema. Intente de nuevo\n");
            }
            break;
        }
        case 0:
        {
            seguir = 'n';
            break;
        }
        default:
        {
            printf("\nEl inciso marcado no existe, intente de nuevo.\n");
            break;
        }
        }
        system("pause");
        system("cls");
    }
    while(seguir=='s');
}
/// BUSCAR DATOS POR X COSAS
void escogerMarca(char marca[])
{
    int select=0;
    char continuar='s';
    do
    {
        menuAutos();
        scanf("%i", &select);
        switch(select)
        {
        case 1:
        {
            strcpy(marca, "Chevrolet");
            continuar = 'n';
            break;
        }
        case 2:
        {
            strcpy(marca, "Fiat");
            continuar = 'n';
            break;
        }
        case 3:
        {
            strcpy(marca, "Nissan");
            continuar = 'n';
            break;
        }
        case 4:
        {
            strcpy(marca, "Peugeot");
            continuar = 'n';
            break;
        }
        case 5:
        {
            strcpy(marca, "Ford");
            continuar = 'n';
            break;
        }
        case 6:
        {
            strcpy(marca, "Citroen");
            continuar = 'n';
            break;
        }
        case 7:
        {
            strcpy(marca, "Mercedes-Benz");
            continuar = 'n';
            break;
        }
        case 8:
        {
            strcpy(marca, "Renault");
            continuar = 'n';
            break;
        }
        case 9:
        {
            strcpy(marca, "Toyota");
            continuar = 'n';
            break;
        }
        case 10:
        {
            strcpy(marca, "Volkswagen");
            continuar = 'n';
            break;
        }
        default:
        {
            printf("\n[Opcion incorrecta, ingrese otra]: ");
            break;
        }
        }
        system("pause");
        system("cls");
    }
    while(continuar == 's');
}
int BuscarDatoChar(nodoAutos *listaAutos, char dato[])
{
    int flag=0;
    nodoAutos *seg=listaAutos;
    while(seg!=NULL)
    {
        if((strcmp(dato, seg->autos.Marca))==0)
        {
            mostrarAuto(seg->autos);
            flag=1;
        }
        else if((strcmp(dato, seg->autos.Modelo))==0)
        {
            mostrarAuto(seg->autos);
            flag=1;
        }
        else if((strcmp(dato, seg->autos.Combustible))==0)
        {
            mostrarAuto(seg->autos);
            flag=1;
        }
        seg=seg->siguiente;
    }
    return flag;
}
int buscarDatoInt(nodoAutos *listaAutos, int dato)
{
    int flag=0;
    nodoAutos *seg=listaAutos;
    while(seg!=NULL)
    {
        if(dato==seg->autos.Anio)
        {
            mostrarAuto(seg->autos);
            flag=1;
        }
        seg=seg->siguiente;
    }
    return flag;
}
///buscar auto por patente
void buscarAutoPorPatente(nodoAutos *lista, char patente[])
{
    nodoAutos *seg=lista;
    int flag=0;
    while(seg!=NULL && flag==0)
    {
        if(strcmpi(seg->autos.Patente, patente)==0)
        {
            mostrarAuto(seg->autos);
            flag=1;
        }
        seg=seg->siguiente;
    }
    if(flag == 0)
    {
        printf("\n[NO HAY REGISTRADO AUTO CON ESA PATENTE]\n");
    }
}
///ver vehiculos en venta
void verVehiculosEnVenta(nodoAutos *lista)
{
    system("cls");
    nodoAutos *seg=lista;
    while(seg!=NULL)
    {
        if(seg->autos.Estado==1)
        {
            mostrarAuto(seg->autos);
        }
        seg=seg->siguiente;
    }
}
///ver vehiculos vendidos
void verVehiculosVendidos(nodoAutos *lista)
{
    system("cls");
    nodoAutos *seg=lista;
    while(seg!=NULL)
    {
        if(seg->autos.Estado==0)
        {
            mostrarAuto(seg->autos);
        }
        seg=seg->siguiente;
    }
}
/// mostrar autos x lista
void verTodosLosAutos(nodoAutos *lista)
{
    nodoAutos *seg=lista;
    while(seg!=NULL)
    {
        mostrarAuto(seg->autos);
        seg=seg->siguiente;
    }
}
//Funciones clasicas de nodo
nodoAutos* inicLista()
{
    return NULL;
}
nodoAutos* crearNodoAuto(stAutos autoNuevo)
{
    nodoAutos* nuevo = (nodoAutos*) malloc(sizeof(nodoAutos));
    nuevo->autos = autoNuevo;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}
nodoAutos* agrgarPpioAuto(nodoAutos* lista, nodoAutos* nuevo)
{
    if(lista)
    {
        nuevo->siguiente = lista;
        lista->anterior = nuevo;
    }
    lista = nuevo;
    return lista;
}
nodoAutos* buscarUltimo(nodoAutos* lista)
{
    nodoAutos* seg = lista;
    if(lista)
    {
        while(seg->siguiente)
        {
            seg = seg->siguiente;
        }
    }
    return seg;
}
nodoAutos* agregarFinalAuto(nodoAutos* lista, nodoAutos* nuevo)
{
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else
    {
        if(nuevo->autos.Anio <= lista->autos.Anio)
        {
            lista = agrgarPpioAuto(lista, nuevo);
        }
        else
        {
            nodoAutos* ante = lista;
            nodoAutos* seg = lista->siguiente;
            while(seg && nuevo->autos.Anio > seg->autos.Anio)
            {
                ante = seg;
                seg = seg->siguiente;
            }
            ante->siguiente = nuevo;
            nuevo->anterior = ante;
            nuevo->siguiente = seg;
            if(seg)
            {
                seg->anterior = nuevo;
            }
        }
    }
    return lista;
}
