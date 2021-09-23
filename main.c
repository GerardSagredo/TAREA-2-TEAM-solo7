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
char *get_csv_fieldk (char * tmp, int k) {
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
//void exportarCsv(HashMap* productos);
//void crearlistaTipo(List * tipos);
//*************************************



int main(void) {
  HashMap* productosNombre = createMap(130);
  HashMap* mapTipos = createMap(20);
  //mapTipos-> = createList ();
  int cont=20;
  FILE *fp = fopen ("100productos.csv" , "r");
  char linea[1024];
  int k=0;
  while (fgets (linea, 1024, fp) != NULL) {
    //printf("ENTRA");
    Producto* p = (Producto*) malloc (sizeof(Producto));
    p->nombre=get_csv_field(linea, 0);
    p->marca=get_csv_field(linea, 1);
    p->tipo=get_csv_field(linea, 2);
    p->stock = strtol(get_csv_field(linea, 3) , NULL, 10);
    p->precio= strtol(get_csv_field(linea, 4) , NULL, 10);
    
    insertMap(productosNombre,p->nombre , p);

    k++; if(k==100) break;
  }
    
  Pair *aux = firstMap(productosNombre);
  while(aux!=NULL) {
      printf("%s\n", aux->key);
      aux = nextMap(productosNombre);
  }

  printf("1 - Agregar producto\n");
  printf("2 - Buscar por tipo\n");
  printf("3 - Terminar ejecucion\n");
  printf("4 - \n");
  printf("5 - Exportar csv\n");
  printf("Ingrese un número:\n");
  
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
        //busquedaTipo(maplistas,aux);
        break;
      case 3:
        printf("Fin de ejecucion");
        return 0;
        break;
        /* case 4:
            Pair* aux = firstMap(productos_nombre);
            while(aux!=NULL) {
              printf("%s \n", aux->key);
              aux = nextMap(productos_nombre);
            }
            break;*/
      case 5:
        


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
  scanf(" %[^\n]s",p->nombre);
    

  Producto* aux;
  aux = (Producto*)searchMap(productos,p->nombre);
  if(NULL !=aux){
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
  printf("entra buscar\n");
  Pair* p = (Pair*) malloc (sizeof(Pair));
  p= searchMap(productosTipo,tipo);
  while (p!=NULL){

  }

} 

/*void exportarCsv(HashMap* productos){

  Pair* aux=(Pair*)malloc(sizeof(Pair));
  

}
*/
