#include <stdio.h>
/* programa para crear imagenes rgb o ppm en C*/
int main(){
int ancho,alto;
scanf("%d %d",&ancho,&alto);
printf("P3\n%d %d\n255\n",ancho,alto);
int i,j;
for (j=0;j<alto;j++){
     for(i=0;i<ancho;i++){
         printf("250 0 0 ");// en esta parte van los valores rgb R G B ,en esta ocasion es 255 0 0 por lo que es toda roja
        }
    printf("\n");    
}
return 0;
}
//gcc imagebpm.c -o imagenbpm
//./imagenbpm >i.ppm;eog i.ppm
//o podemos crearla en rgb asi
//./imagenbpm >im.rgb