#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED


typedef struct
{
    int idEmpleado;
    char nombre[30];
    char apellido[30];
    int dni;
}stEmpleado;


typedef struct nodoEmpleado
{
    stEmpleado dato;
    struct nodoEmpleado*sig;
}nodoEmpleado;


typedef struct
{
    stEmpleado empleado;
    struct nodoVenta*lista;
}celdaEmpleado;


nodoEmpleado*agregarEmpleado(nodoEmpleado*lista);
void cargarEmpleado(stEmpleado*aux);
void cargarArchivo (char nombre_archivo[],nodoEmpleado*lista);
nodoEmpleado*inicEmpleado();
nodoEmpleado*crearNodoEmpleado(stEmpleado aux);
nodoEmpleado*agregaalppioEmpleado(nodoEmpleado*lista,nodoEmpleado*nuevonodo);
void verEmpleados(char nombre_archivo[]);
void verUnEmpleado (stEmpleado aux);



#endif // EMPLEADO_H_INCLUDED
