#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED
#include "cliente.h"
#include "auto.h"
#include "empleado.h"
typedef struct
{
    int idVenta;
    stCliente cliente;
    stAutos automovil;
    stEmpleado empleado;
    char anioDeVenta[5];
}stVentas;


typedef struct nodoVenta
{
    stVentas venta;
    struct nodoVenta*sig;
}nodoVenta;




int posicion(char nombre[]);
int sizes(char nombre[]);
int venderAuto(char nombre_archivo[],int pos);//segundo parametro va la funcion posicion
void modificarEstadoVenta(char nombre[], int pos);

void modificarEstadoVenta2(FILE*archivo,char patente[]);

int altaDatos(celdaClientes arr[], stVentas datos, int validos);
int agregarCliente(celdaClientes arr[], stVentas datos, int validos);

nodoAutos*Cargarlista(char nombre_archivo[],nodoAutos*lista);
nodoAutos*agregaralfinalAuto(nodoAutos*lista,nodoAutos*nuevonodo);
nodoAutos* buscarUltimo(nodoAutos* lista);
void mostrarAutos(nodoAutos*lista);
int busqueda (nodoAutos*lista,int numero);
void ventaNuevoCliente(char archivo_auto[],char archivo_empleado[],char archivo_venta[],char archivo_cliente[],nodoAutos*lista,int numero);
int buscardni (char nombre_archivo[],char dni[]);//cambio a char
nodoAutos*busquedaNodo (nodoAutos*lista,int numero);//se podria reultilizar busqueda, ver como hacerlo
stAutos AutoComprado (nodoAutos*nodoEncontrado);
stEmpleado buscarEmpleado (FILE*archivo,int id);
void generarFecha (char fecha[]);
void mostrarTodasVentas (char nombre_archivo[]);
void mostrarVenta(stVentas venta);
void ventaClienteViejo (char archivo_auto[],char archivo_empleado[],char archivo_venta[],char archivo_cliente[],nodoAutos*lista,int numero,char dni[]);
stCliente buscarpordni (FILE*archivo,char dni[]);


nodoVenta *crearNodo(stVentas datos);
nodoVenta*archiVenta_a_lista(char nombre_archivo[],nodoVenta*lista);
void mostrarListaVenta(nodoVenta*lista);
nodoVenta*crearnodoVenta(stVentas aux);
nodoVenta*agregaralppioVenta(nodoVenta*lista,nodoVenta*nuevonodo);
int sumatoriaPorAnio (nodoVenta*lista,char anio[]);


//ARREGLO EMPLEADO-VENTA
int pasar_de_archivo_a_adl_Empleado(celdaEmpleado arreglo[],int validos,char nombre_archivo[]);
int altaEmpleado(celdaEmpleado arreglo[],int validos,stVentas aux);
int buscarArregloEmpleado(celdaEmpleado arreglo[],int validos,int id);
int agregarCeldaEmpleado(celdaEmpleado arreglo[],int validos,stEmpleado empleado);
nodoVenta*agregaralfinalVenta(nodoVenta*lista,nodoVenta*nuevonodo);
nodoVenta*buscarUltimoVenta(nodoVenta*lista);
void mostrarAdlEmpleadoVenta(celdaEmpleado arreglo[],int validos);
void muestraVentaEmpleado (stVentas aux);

int cantidadVentaxID (celdaEmpleado adl[],int validos,int id);
int sizesEmpleado(char nombre[]);
int sumatoria (celdaEmpleado adl[],int validos,int id);
float comision (celdaEmpleado adl[],int validos,int id);


#endif // VENTAS_H_INCLUDED
