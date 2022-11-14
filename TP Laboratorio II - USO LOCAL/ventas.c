#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ventas.h"
#include "empleado.h"
#include "cliente.h"
#include "auto.h"

nodoAutos*Cargarlista(char nombre_archivo[],nodoAutos*lista)
{
    FILE*archivo=fopen(nombre_archivo,"rb");

    stAutos aux;
    nodoAutos*nuevonodo;
    if(archivo)
    {
        while(fread(&aux,sizeof(stAutos),1,archivo)>0)
        {
            if(aux.Estado==1)
            {
                nuevonodo=crearNodoAuto(aux);
                lista=agregaralfinalAuto(lista,nuevonodo);
            }
        }
        fclose(archivo);
    }
    return lista;
}

nodoAutos*agregaralfinalAuto(nodoAutos*lista,nodoAutos*nuevonodo)
{
    nodoAutos*ultimo;
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        ultimo=buscarUltimo(lista);
        nuevonodo->anterior=ultimo;
        ultimo->siguiente=nuevonodo;
    }
    return lista;
}

int sizes(char nombre[]) // consigo cantidad de registros
{
    int size=0;
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        fseek(buffer, 0, SEEK_END);
        size = ftell(buffer) / sizeof(stAutos);
        fclose(buffer);
    }
    return size;
}

void mostrarAutos(nodoAutos*lista)
{
    int i=1;
    nodoAutos*seg=lista;

    while(seg!=NULL)
    {
        printf("\n------AUTO: %d-----\n",i);
        mostrarAuto(seg->autos);
        i++;
        seg=seg->siguiente;
    }

}

int busqueda (nodoAutos*lista, int numero)
{
    int i=1;
    int flag=0;
    nodoAutos*seg=lista;

    while(seg!=NULL&&flag==0)
    {
        if(i==numero)
        {
            flag=1;
            printf("\n----DATOS DEL AUTO----\n");
            mostrarAuto(seg->autos);
        }
        i++;
        seg=seg->siguiente;
    }
    return flag;
}

int buscardni (char nombre_archivo[],char dni[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    int flag=0;
    stCliente aux;
    if(archivo)
    {
        while(flag==0&&fread(&aux,sizeof(stCliente),1,archivo)>0)
        {
            if(strcmpi(aux.dni,dni)==0)
            {
                flag=1;
            }
        }
        fclose(archivo);
    }

    return flag;
}

nodoAutos*busquedaNodo (nodoAutos*lista,int numero)
{
    int i=1;
    nodoAutos*seg=lista;
    nodoAutos*aux=NULL;
    while(seg!=NULL&&aux==NULL)
    {
        if(i==numero)
        {
            aux=seg;
        }
        i++;
        seg=seg->siguiente;
    }
    return aux;
}

void ventaNuevoCliente(char archivo_auto[],char archivo_empleado[],char archivo_venta[],char archivo_cliente[],nodoAutos*lista,int numero)
{
    system("cls");
    nodoAutos*autoVendido=busquedaNodo(lista,numero);
    FILE*autos=fopen(archivo_auto,"r+b");//modificamos auto
    FILE*empleado=fopen(archivo_empleado,"rb");//leemos empleados
    FILE*venta=fopen(archivo_venta,"ab");//cargamos venta
    FILE*cliente=fopen(archivo_cliente,"ab");//cargamos cliente

    stVentas ventaFinal;
    stAutos autoFinal;
    stCliente persona;

    int idEmpleado;
    stEmpleado trabajador;
    if(autos&&empleado&&venta&&cliente)
    {
        puts("Usted no es cliente\n");
        printf("\n---Ingrese sus datos---\n");

        ventaFinal.cliente=cargarCliente(persona);
        autoFinal=AutoComprado(autoVendido);
        ventaFinal.automovil=autoFinal;

        srand (time(NULL));
        idEmpleado=1+rand()%4;
        trabajador=buscarEmpleado(empleado,idEmpleado);


        ventaFinal.empleado=trabajador;

        generarFecha(ventaFinal.anioDeVenta);
        ventaFinal.idVenta=rand()%100000;

        fwrite(&ventaFinal.cliente,sizeof(stCliente),1,cliente);

        fwrite(&ventaFinal,sizeof(stVentas),1,venta);
        modificarEstadoVenta2(autos,autoVendido->autos.Patente);

        fclose(autos);
        fclose(empleado);
        fclose(venta);
        fclose(cliente);

    }
    system("cls");
    printf("\nVENTA GENERADA CON EXITO!\n\n");
    printf("\nA CONTINUACION, LOS DATOS DE LA VENTA\n\n");
    mostrarVenta(ventaFinal);

    puts("Muchas gracias por su compra!");
}

void modificarEstadoVenta2(FILE*archivo,char patente[])
{
    stAutos aux;
    int flag=0;
    while(flag==0&&fread(&aux,sizeof(stAutos),1,archivo)>0)
    {
        if(strcmp(aux.Patente,patente)==0)
        {
            flag=1;
            aux.Estado=0;
            fseek(archivo,sizeof(stAutos)*(-1),SEEK_CUR);
            fwrite(&aux,sizeof(stAutos),1,archivo);
        }
    }
}

void mostrarTodasVentas (char nombre_archivo[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    stVentas aux;
    if(archivo)
    {
        while(fread(&aux,sizeof(stVentas),1,archivo)>0)
        {
            printf("\t[ID Venta:%d] -- ",aux.idVenta);
            printf("[Año de Venta:%s]\n",aux.anioDeVenta);
            mostrarVenta(aux);
        }
        fclose(archivo);
    }
}


void mostrarVenta(stVentas venta)
{
    printf("\n----------------DATOS COMPRADOR----------------\n");
    verCliente(venta.cliente);
    printf("\n----------------DATOS AUTOMOVIL----------------\n");
    mostrarAuto(venta.automovil);
    printf("\n----------------DATOS VENDEDOR----------------\n");
    verUnEmpleado(venta.empleado);
    printf("\n\n___________________________________________\n\n");
}



void modificarEstadoVenta(char nombre[], int pos)
{
    stAutos aux;
    int estado;
    FILE* buffer = fopen(nombre, "r+b");
    if(buffer)
    {
        fseek(buffer, sizeof(stAutos)*pos, SEEK_SET);
        fread(&aux, sizeof(stAutos), 1, buffer);
        if(aux.Estado == 1)
        {
            estado = 0;
        }
        if(aux.Estado == 0)
        {
            estado = 1;
        }
        aux.Estado = estado;
        fseek(buffer, sizeof(stAutos)*-1, SEEK_CUR);
        fwrite(&aux, sizeof(stAutos), 1, buffer);


        fclose(buffer);
    }
}

nodoVenta*archiVenta_a_lista(char nombre_archivo[],nodoVenta*lista)
{
    system("cls");
    FILE*archivo=fopen(nombre_archivo,"rb");
    stVentas aux;
    nodoVenta*nuevonodo;
    if(archivo)
    {
        while(fread(&aux,sizeof(stVentas),1,archivo)>0)
        {
            nuevonodo=crearnodoVenta(aux);
            lista=agregaralppioVenta(lista,nuevonodo);
        }
        fclose(archivo);
    }
    return lista;
}
nodoVenta*crearnodoVenta(stVentas aux)
{
    nodoVenta*nuevonodo=(nodoVenta*)malloc(sizeof(nodoVenta));
    nuevonodo->venta=aux;
    nuevonodo->sig=NULL;
    return nuevonodo;
}

nodoVenta*agregaralppioVenta(nodoVenta*lista,nodoVenta*nuevonodo)
{
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        nuevonodo->sig=lista;
        lista=nuevonodo;
    }
    return lista;
}

void mostrarListaVenta(nodoVenta*lista)
{
    nodoVenta*seg=lista;

    while(seg!=NULL)
    {
        printf("\t[ID Venta: %d] ---",seg->venta.idVenta);
        printf("[Anio Venta: %s]\n",seg->venta.anioDeVenta);
        mostrarVenta(seg->venta);
        seg=seg->sig;
    }
}



stEmpleado buscarEmpleado (FILE*archivo,int id)
{
    int flag=0;
    stEmpleado aux;
    while(flag==0&&fread(&aux,sizeof(stEmpleado),1,archivo)>0)
    {

        if(aux.idEmpleado==id)
        {
            flag=1;
        }
    }
    return aux;
}

void generarFecha (char fecha[])
{
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);
    strftime(fecha, 100, "%Y", tm);
}

stAutos AutoComprado (nodoAutos*nodoEncontrado)
{
    stAutos nuevo=nodoEncontrado->autos;

    return nuevo;
}
void ventaClienteViejo (char archivo_auto[],char archivo_empleado[],char archivo_venta[],char archivo_cliente[],nodoAutos*lista,int numero,char dni[])
{
    system("cls");
    nodoAutos*autoVendido=busquedaNodo(lista,numero);
    FILE*autos=fopen(archivo_auto,"r+b");//modificamos auto
    FILE*empleado=fopen(archivo_empleado,"rb");//leemos empleados
    FILE*venta=fopen(archivo_venta,"ab");//cargamos venta
    FILE*cliente=fopen(archivo_cliente,"r+b");//cargamos cliente
    stVentas ventaFinal;
    stAutos autoFinal;
    stCliente persona;
    int idEmpleado;
    stEmpleado trabajador;

    if(autos&&empleado&&venta&&cliente)
    {
        //cliente
        persona=buscarpordni(cliente,dni);
        ventaFinal.cliente=persona;
        //auto
        autoFinal=AutoComprado(autoVendido);
        ventaFinal.automovil=autoFinal;
        //empleado
        srand (time(NULL));
        idEmpleado=1+rand()%4;
        trabajador=buscarEmpleado(empleado,idEmpleado);
        ventaFinal.empleado=trabajador;
        //fecha de compra e id
        generarFecha(ventaFinal.anioDeVenta);
        ventaFinal.idVenta=rand()%100000;
        //guardar cliente
        fwrite(&ventaFinal.cliente,sizeof(stCliente),1,cliente);
        //guardar venta
        fwrite(&ventaFinal,sizeof(stVentas),1,venta);
        modificarEstadoVenta2(autos,autoVendido->autos.Patente);

        fclose(autos);
        fclose(empleado);
        fclose(venta);
        fclose(cliente);
    }
    system("cls");
    printf("\nVENTA GENERADA CON EXITO!\n\n");
    printf("\nA CONTINUACION, LOS DATOS DE LA VENTA\n\n");
    mostrarVenta(ventaFinal);

    puts("Muchas gracias por su compra!");
}
stCliente buscarpordni (FILE*archivo,char dni[])
{
    int flag=0;
    stCliente aux;
    while(flag==0&&fread(&aux,sizeof(stCliente),1,archivo)>0)
    {
        if(strcmp(aux.dni,dni)==0)
        {
            flag=1;
        }
    }
    return aux;
}

int sumatoriaPorAnio (nodoVenta*lista,char anio[])
{
    nodoVenta*seg=lista;
    int sumatoria=0;
    while(seg!=NULL)
    {
        if(strcmpi(seg->venta.anioDeVenta,anio)==0)
        {
            sumatoria=sumatoria+seg->venta.automovil.PrecioDeVenta;
        }
        seg=seg->sig;
    }
    return sumatoria;
}



//ARREGLO DE EMPLEADOS-VENTAS

int pasar_de_archivo_a_adl_Empleado(celdaEmpleado arreglo[],int validos,char nombre_archivo[])
{
    FILE*archivo=fopen(nombre_archivo,"rb");
    stVentas aux;

    if(archivo)
    {
        while(fread(&aux,sizeof(stVentas),1,archivo)>0)
        {
            validos=altaEmpleado(arreglo,validos,aux);
        }
        fclose(archivo);
    }
    return validos;
}

int altaEmpleado(celdaEmpleado arreglo[],int validos,stVentas aux)
{
    nodoVenta*nuevonodo=crearnodoVenta(aux);
    int pos=buscarArregloEmpleado(arreglo,validos,aux.empleado.idEmpleado);
    if(pos==-1)
    {
        validos=agregarCeldaEmpleado(arreglo,validos,aux.empleado);
        pos=validos-1;
    }
    arreglo[pos].lista=agregaralfinalVenta(arreglo[pos].lista,nuevonodo);
    return validos;
}
int buscarArregloEmpleado(celdaEmpleado arreglo[],int validos,int id)
{
    int pos=-1;
    int i=0;
    while(i<validos&&pos==-1)
    {
        if(arreglo[i].empleado.idEmpleado==id)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

int agregarCeldaEmpleado(celdaEmpleado arreglo[],int validos,stEmpleado empleado)
{
    arreglo[validos].empleado=empleado;
    arreglo[validos].lista=NULL;
    validos++;
    return validos;
}

nodoVenta*agregaralfinalVenta(nodoVenta*lista,nodoVenta*nuevonodo)
{
    nodoVenta*ultimo;
    if(lista==NULL)
    {
        lista=nuevonodo;
    }
    else
    {
        ultimo=buscarUltimoVenta(lista);
        ultimo->sig=nuevonodo;
    }
    return lista;
}
nodoVenta*buscarUltimoVenta(nodoVenta*lista)
{
    nodoVenta*seg=lista;
    while(seg->sig!=NULL)
    {
        seg=seg->sig;
    }
    return seg;
}

void mostrarAdlEmpleadoVenta(celdaEmpleado arreglo[],int validos)
{
    system("cls");
    int i=0;
    nodoVenta*seg;
    while(i<validos)
    {
        printf("\n\t[%s %s]\n",arreglo[i].empleado.nombre,arreglo[i].empleado.apellido);
        seg=arreglo[i].lista;
        while(seg!=NULL)
        {
            muestraVentaEmpleado(seg->venta);
            seg=seg->sig;
        }
        i++;
    }
}

void muestraVentaEmpleado (stVentas aux)
{
    mostrarAuto(aux.automovil);
    printf("\n[COMPRADOR]\n");
    printf("Nombre: %s\n",aux.cliente.nombre);
    printf("Apellido: %s\n",aux.cliente.apellido);
    printf("DNI: %s\n",aux.cliente.dni);
    printf("\n___________________________________\n");
}


int sizesEmpleado(char nombre[])
{
    int size=0;
    FILE* buffer = fopen(nombre, "rb");
    if(buffer)
    {
        fseek(buffer, 0, SEEK_END);
        size = ftell(buffer) / sizeof(stEmpleado);
        fclose(buffer);
    }
    return size;
}


int cantidadVentaxID (celdaEmpleado adl[],int validos,int id)
{
    int cant=0;

    int pos=buscarArregloEmpleado(adl,validos,id);

    if (pos!=-1)
    {
        printf("\nEmpleado:%s\t%s\n",adl[pos].empleado.nombre,adl[pos].empleado.apellido);
        nodoVenta*seg=adl[pos].lista;

        while(seg!=NULL)
        {
            cant++;
            seg=seg->sig;
        }
    }


    return cant;
}

int sumatoria (celdaEmpleado adl[],int validos,int id)
{
    int sumatoria=0;
    int pos=buscarArregloEmpleado(adl,validos,id);

    nodoVenta*seg=adl[pos].lista;

    while(seg!=NULL)
    {
        sumatoria=sumatoria+seg->venta.automovil.PrecioDeVenta;
        seg=seg->sig;
    }
    return sumatoria;
}

float comision (celdaEmpleado adl[],int validos,int id)
{
    float resultadoParcial=(float)sumatoria(adl,validos,id)/cantidadVentaxID(adl,validos,id);
    float comi=0;
    printf("\nIngrese la comision elegida\n");
    scanf("%f",&comi);

    float resultadoTotal=resultadoParcial*comi;
    resultadoTotal=resultadoTotal/100;

    return resultadoTotal;
}

/// nodo ventas
nodoVenta *crearNodo(stVentas datos)
{
    nodoVenta *aux=(nodoVenta*) malloc(sizeof(nodoVenta));
    aux->venta.automovil=datos.automovil;
    aux->venta.cliente=datos.cliente;
    aux->venta.empleado=datos.empleado;
    strcpy(aux->venta.anioDeVenta, datos.anioDeVenta);
    aux->venta.idVenta=datos.idVenta;
    aux->sig=NULL;
    return aux;
}
nodoVenta *agregarPrinc(nodoVenta *lista, nodoVenta *aux)
{
    if(lista==NULL)
    {
        lista=aux;
    }
    else
    {
        aux->sig=lista;
        lista=aux;
    }
    return lista;
}

