#ifndef AUTO_H_INCLUDED
#define AUTO_H_INCLUDED

typedef struct
{
    char Marca[30];
    char Modelo[30];
    int Km;
    int Anio;
    int PrecioDeVenta;
    char Patente[10];
    int Estado;
    char Combustible[30];
} stAutos;

typedef struct nodoAutos
{
    stAutos autos;
    struct nodoAutos* siguiente;
    struct nodoAutos* anterior;
} nodoAutos;

typedef struct
{
    char Marca[30];
    char Modelo[30];
    int Km;
    int Anio;
    int PrecioDeVenta;
    char Patente[8];
    int Estado;

} coche;

typedef struct nodoLista
{
    coche vehiculo;
    struct nodoLista*sig;
}nodoLista;

typedef struct
{
    char Combustible[30];
    char Marca[30];
    char Modelo[30];
} stTipos;

typedef struct
{
    stTipos tipo;
    struct nodoLista*lista;
} celda;

void mostrarArchivoAutos(char nombre[]);
void mostrarAuto(stAutos auto1);
int pasar_de_archivo_a_adl (celda arreglo[],int dimension,char nombre_archivo[]);
coche cargarcoche(char marca[],char modelo[],int km, int anio, int precio, char patente[],int estado);
int altaTipos(celda arreglo[],int validos,coche vehiculo,char combustible[],char marca[],char modelo[]);
int agregarCombustible(celda arreglo[],int validos,char combustible[]);
int buscarCombustible(celda arreglo[],int validos,char combustible[]);
nodoLista*agregaralfinalL(nodoLista*lista,nodoLista*nuevonodo);
nodoLista*buscarultimoL(nodoLista*lista);
nodoLista*crearnodoL(coche vehiculo);
void mostrarlistaCombustible(celda arreglo[],int validos,char combustible[]);
void mostrarCoche (coche autito);
void modificarModelo(char nombre[], int pos);
void modificarKm(char nombre[], int pos);
void modificarAnio(char nombre[], int pos);
void modificarPrecio(char nombre[], int pos);
void modificarPatente(char nombre[], int pos);
void modificarCombustible(char nombre[], int pos);
int sizes(char nombre[]);
void escogerMarca(char marca[]);
int BuscarDatoChar(nodoAutos *listaAutos, char dato[]);
int buscarDatoInt(nodoAutos *listaAutos, int dato);


int pasar_de_archivo_a_adl_Marca (celda arreglo[],int dimension,char nombre_archivo[]);
int altaMarca(celda arreglo[],int validos,coche vehiculo,char combustible[],char marca[],char modelo[]);
int buscarMarca(celda arreglo[],int validos,char marca[]);
int agregarMarca(celda arreglo[],int validos,char marca[]);
void marcaElegida(celda arreglo[],int validos,int eleccion);
void mostrarlistaMarca(celda arreglo[],int validos,char marca[]);

void listaArchivo(char nombre[], nodoAutos* lista);
nodoAutos* inicLista();
nodoAutos* cargarLista(nodoAutos* lista);
nodoAutos* archivoLista(nodoAutos* lista, char nombre[]);
nodoAutos* crearNodoAuto(stAutos autoNuevo);
nodoAutos* agrgarPpioAuto(nodoAutos* lista, nodoAutos* nuevo);
nodoAutos* buscarUltimo(nodoAutos* lista);
nodoAutos* agregarFinalAuto(nodoAutos* lista, nodoAutos* nuevo);
nodoAutos*pasar_de_archivo_a_lista_doble(char nombre_archivo[],nodoAutos*lista);
void Rango(nodoAutos*lista,int rangoA, int rangoB);
void RangoKm(nodoAutos*lista,int rangoA, int rangoB);

stAutos datosAuto();

void mostrarArchivoAutosEnVenta(char nombre[]);


#endif // AUTO_H_INCLUDED
