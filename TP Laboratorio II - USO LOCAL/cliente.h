#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct
{
    char nombre[30];
    char apellido[30];
    char dni[9];
    char telefono[11];
    char domicilio[30];
    char altura[5];
}stCliente;

typedef struct
{
    stCliente cliente;
    struct nodoVenta*lista;
}celdaClientes;

stCliente cargarCliente(stCliente nuevoCliente);
void verCliente (stCliente aux);
void mostrarCliente (char nombre_archivo[]);

int buscarPosCliente(celdaClientes arr[], char datos[], int validos);


#endif // CLIENTE_H_INCLUDED
