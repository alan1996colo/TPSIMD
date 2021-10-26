#include <stdio.h>
//declaracion de variables globales
int ancho,alto;
void leerimagen(char* nombreArchivo);
void imprimirimagen(int R[ancho][alto],int G[ancho][alto],int B[ancho][alto]);
/* programa para lectura y escritura de imagenes rgb o ppm en C*/
int main(int argc,char *argv[]){
    leerimagen(argv[1]);//lee el primer argumento de la terminal
return 0;
}
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

}
//gcc imagen.c -o a.out
//./a.out i.ppm; eog salida.ppm

//llaalalalalalala