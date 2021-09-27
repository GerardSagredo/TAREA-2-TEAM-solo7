#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"

typedef struct{ //cambiar tamaños
  char* nombre ;
  char* marca;
  char* tipo;
  int stock;
  int precio;
}Producto;




//Funcion para leer el k-esimo elemento de un string (separado por comas)
char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
              ret[i-ini_i] = 0;
              return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
      ret[i-ini_i] = 0;
      return ret;
    }


    return NULL;
}


//************************************
void agregarProducto(HashMap* productos);
void busquedaTipo(HashMap* productos,char* tipo);
void busquedaMarca(HashMap* productosTipo);
void busquedaNombre(HashMap* productos);
void mostrartodo(HashMap* productos);
void AgregarCarrito(char nombre, int cantidad, char carrito);//falta
void ConcretarCompra (char carrito);//falta
void exportarCsv(HashMap* productos);//incompleta
void crearlistaTipo(List * tipos);//falta
//*************************************


int main(void) {
  HashMap* productosNombre = createMap(130);
  HashMap* mapTipos = createMap(20);
  HashMap* productosTipos = createMap(130);
  HashMap* productosMarca = createMap(130);
  int cont=20;
  FILE *fp = fopen ("100productos.csv" , "r");
  char linea[1024];
  int k=0;
  
  while (fgets (linea, 1024, fp) != NULL) {

    Producto* p = (Producto*) malloc (sizeof(Producto));
    
    //printf("ENTRA");
    
    p->nombre=get_csv_field(linea, 0);
    p->marca=get_csv_field(linea, 1);
    p->tipo=get_csv_field(linea, 2);
    p->stock = strtol(get_csv_field(linea, 3) , NULL, 10);
    p->precio= strtol(get_csv_field(linea, 4) , NULL, 10);
   
    

    insertMap(productosNombre,p->nombre , p);

    k++; if(k==100) break;
  }

  

  printf("Ingrese un número:\n");
  printf("1 - Agregar producto\n");
  printf("2 - Buscar por tipo\n");
  printf("3 - Buscar por marca\n");
  printf("4 - Buscar por nombre \n");
  printf("5 - Mostrar todos los produsctos\n");
  printf("6 - Agregar al carrito\n");
  printf("7 - Concretar compra\n");
  printf("8 - Terminar ejecucion\n");
  printf("9 - Exportar CSV\n");
  while(1){
    int opcion;
    scanf("%d",&opcion);
    switch(opcion){
      case 1:
        agregarProducto(productosNombre);
        break;
      case 2:
        printf("ingrese tipo\n");
        char* aux;
        scanf("%s",aux);
        busquedaTipo(mapTipos,aux);
        break;
      case 3:
        busquedaMarca(productosNombre);
        break;
        busquedaNombre(productosNombre);
      case 5:
        mostrartodo(productosNombre);
        break;
      case 6:

        break;
      case 7:

        break;
      case 8:
        printf("Fin de ejecucion");
        return 0;
        break;
      case 9:
        //exportarCsv(productosNombre);
        break;
    }
    printf("~~~~~~~ Escoja otra operacion a realizar ~~~~~~~\n");
  }
  return 0;
}

void agregarProducto(HashMap* productos){

  printf("entra agregar\n");
  Producto* p = (Producto*) malloc (sizeof(Producto));
  

  p->nombre= (char *)calloc( sizeof( char ), 30 );
  p->marca= (char *)calloc( sizeof( char ), 20 );
  p->tipo= (char *)calloc( sizeof( char ), 20 );
  
  printf("nombre: \n");
  scanf(" %s",p->nombre);
    

  Producto* aux;
  aux = (Producto*)searchMap(productos,p->nombre);
  if(aux !=NULL){//al reves
    aux->stock++;
    printf("%d\n",aux->stock);
    return;
  }

  printf("marca: \n");
  scanf("%s",p->marca);
    
  printf("tipo: \n");
  scanf("%s", p->tipo);

  printf("stock:\n");
  scanf("%d",&p->stock);

  printf("precio:\n");
  scanf("%d",&p->precio);

  insertMap(productos,p->nombre , p); //un capo
}

/*void crearlistaTipo(List * tipos){
  //Tengo pensado agregar una lista solo para tipos, pero no se como agregarla
  Producto * tipo = (Producto*) malloc (sizeof(Producto));

}*/

void busquedaTipo(HashMap* productosTipo,char* tipo){
  
  int iguales,encontrado = 0;
  char *busqueda;
  Pair* aux = (Pair*) malloc (sizeof(Pair));
  aux = searchMap(productosTipo,tipo);

  Producto* p = (Producto*)malloc(sizeof(Producto));
  while (aux!=NULL){

    busqueda = strstr(p->tipo, tipo);
    if(busqueda != NULL ){
      printf(" %s, %s, %s, %d, %d \n",p->nombre ,p->marca,p->tipo, p->stock, p->precio );
      encontrado++;
    }
    aux = nextMap(productosTipo);
  }
  if(encontrado == 0){
    printf("No se encontraron coincidencias\n");
  }
} //no coincide palabras

/*void exportarCsv(HashMap* productos){
  printf("ERROR");
  char* filename = "exportado.csv";
  
  Pair *auxMap = firstMap(productos);
  Producto* aux=(Producto*)malloc(sizeof(Producto));
  FILE *fp;
  int i,j;
  filename = strcat(filename,"w+");
  fprintf(fp," %s, %s, %s, %d, %d",aux->nombre,aux->tipo,aux->marca,aux->stock,aux->precio); //FALTO REPETIR ESTA LINEA.
}*/

void mostrartodo(HashMap* productos){

   Producto* aux = NULL;

   aux= firstMap(productos);
    while(aux!=NULL) {

      printf(" %s, %s, %s, %d, %d \n",aux->nombre ,aux->marca,aux->tipo, aux->stock, aux->precio );
      aux = nextMap(productos);
    }


}

void busquedaMarca(HashMap* productos){
  char mar[15];

  scanf("%s", mar);
  Producto*  aux= firstMap(productos);
    while(aux!=NULL) {
        printf("%s",aux->marca);
        if(aux->marca==mar){

          printf(" %s, %s, %s, %d, %d \n",aux->nombre ,aux->marca,aux->tipo, aux->stock, aux->precio );
          break;
        }
    
      aux = nextMap(productos);
    }


  printf("NO EXISTE");


}

void busquedaNombre(HashMap* productos){
  char mar[15];

  scanf("%s", mar);
  Producto*  aux= firstMap(productos);
    while(aux!=NULL) {
        printf("%s",aux->nombre);
        if(aux->nombre == mar){

          printf(" %s, %s, %s, %d, %d \n",aux->nombre ,aux->marca,aux->tipo, aux->stock, aux->precio );
          break;
        }
    
      aux = nextMap(productos);
    }


  printf("NO EXISTE");


}