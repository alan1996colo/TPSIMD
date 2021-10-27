#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//declaracion de variables globales
//int ancho,alto; //no se usa por el momento
void procesarArchivos(char *imagen1, char *imagen2, char *mask, int ancho, int alto);
void enmascararImagen(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void abrirImagen(char *nombreArchivo, int tamano, unsigned char *buffer);
void guardarImagen(char *nombreArchivo, int tamano, unsigned char *buffer);
//void leerimagen(char* nombreArchivo); //no se usan por el momento
//void imprimirimagen(int R[ancho][alto],int G[ancho][alto],int B[ancho][alto]); //no se usan por el momento
/* programa para lectura y escritura de imagenes rgb o ppm en C*/
int main(int argc, char *argv[])
{
  clock_t tiempo_inicio, tiempo_final;
  double segundos = 0.0;

  tiempo_inicio = clock();

  if (argc != 6)
  {
    printf("Error al ingresar los parametros\n");
    return 1;
  }


  //Parametros
  char *imagen1 = argv[1];      //imagene1
  char *imagen2 = argv[2];   //imagen2
  char *mask = argv[3];      //mascara
  int ancho = atoi(argv[4]); //para pasar el argumento a int
  int alto = atoi(argv[5]);  //para pasar el argumento a int

  

 

  tiempo_final = clock();
procesarArchivos(imagen1,imagen2,mask,ancho,alto);
  segundos = (double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
  printf("%.16g milisegundos\n", segundos * 1000.0);

  return 1;
}
/*
void imprimirimagen(int R[ancho][alto],int G[ancho][alto],int B[ancho][alto]){
    //imprime una imagen tomando cmoo parametro 3 arreglos de entero r,g,b y lo guarda en salida.ppm , es como el otro programa."imagenbpm"
    FILE *ap;
    ap=fopen("salida.ppm","w");
    fprintf(ap,"P3\n%d %d\n255\n",ancho,alto);
    int i,j;
    for(i=0;i<alto;i++){
        for(j=0;j<ancho;j++){
            fprintf(ap,"%d %d %d ",R[i][j],G[i][j],B[i][j]);
        }
        fprintf(ap,"\n");
    }
    fclose(ap);
}
*/
void abrirImagen(char *nombreArchivo, int tamano, unsigned char *buffer)
{
  FILE *fp;
  printf("abrir el archivo %s\n", nombreArchivo);

  fp = fopen(nombreArchivo, "r");//indicamos lectura
  if (fp == NULL)//si no existe..
  {
    printf("Error al abrir el archivo\n");
  }
  else
  {
    fread(buffer, tamano, 1, fp);
  }
  fclose(fp);
}


void guardarImagen(char *nombreArchivo, int tamano, unsigned char *buffer)
{
  FILE *fp;
  fp = fopen(nombreArchivo, "wb");//indicamos escritura
  fwrite(buffer, 1, tamano, fp);
  fclose(fp);
}

void enmascararImagen(unsigned char *a, unsigned char *b, unsigned char *mask, int tam)
{
  for (int i = 0; i < tam; i++)
  {
    if (mask[i] != 0)
    { //0 si es negro - 255 si es blanco
      a[i] = b[i];
    }
  }
}

void procesarArchivos(char *imagen1, char *imagen2, char *mask, int ancho, int alto)
{

  int cantidadxPixel = 3; //RGB 3 bytes por pixel, un byte hasta 255 por cada color R,G O B
  int tam = ancho * alto * cantidadxPixel;

  //Reservar memoria dinámica
  unsigned char *memoriaParaImg1 = malloc(tam);
  unsigned char *memoriaParaImg2 = malloc(tam);
  unsigned char *mascara = malloc(tam);

  //Abrimos las imagenes
  abrirImagen(imagen1, tam, memoriaParaImg1);
  abrirImagen(imagen2, tam, memoriaParaImg2);
  abrirImagen(mask, tam, mascara);

  enmascararImagen(memoriaParaImg1, memoriaParaImg2, mascara, tam);
  char* nameImagen="ImagenConMascara.rgb";
    guardarImagen(nameImagen, tam, memoriaParaImg1);

  //Liberar memoria
  free(memoriaParaImg1);
  free(memoriaParaImg2);
  free(mascara);
}




/*
void leerimagen(char *nombreArchivo){
    //lee la imagen del archivo pasado en parametro, crea 3 arreglos :r,g,b con sus psiciones 
    //alto y ancho y finalmente usa esos valores para pasarselos a imprimir imagen.
    FILE *archivo;
    archivo =fopen(nombreArchivo,"r");
    char letra; int tipo,maxcolor;
    fscanf(archivo,"%c %d %d %d %d",&letra,&tipo,&ancho,&alto,&maxcolor);
    int R[ancho][alto],G[ancho][alto],B[ancho][alto];
    int i,j;
    for(i=0;i<alto;i++){
        for(j=0;j<ancho;j++){
            fscanf(archivo,"%d %d %d",&R[i][j],&G[i][j],&B[i][j]);
        }
    }
fclose(archivo);
imprimirimagen(R,G,B);

}*/



//para probar.
//gcc imagen.c -o a.out

//./a.out imgen.rgb imgverde.rgb masc.rgb 400 400
//va producir un archivo llamado "ImagenConMascara.rgb"
//abrir y ver resultados.