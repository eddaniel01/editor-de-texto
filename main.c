#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imp_archivo(FILE *archivo);
void cuenta_palabra_maxpalabra(FILE *archivo, char buffer[]);
int cuenta_lienas(FILE *archivo);
char espacios_antes_de_signos(FILE *archivo, char *texto, int cant_elementos);
void titulo(char *texto, int cant_elementos,char *token, char copia[]);
void escribir_segundo_archivo(char nomarchivo2, char *texto);

int main()
{
    char nomarchivo[50], buffer[50];
    FILE *archivo;


    printf("Digite la direccion del archivo: ");
    scanf("%s",nomarchivo);
    system("cls");

    archivo= fopen(nomarchivo,"r");
    if(archivo == NULL){
       perror("Error al intentar abrir el archivo");
       exit(1);
    }

    fseek(archivo, 0, SEEK_END);
    int cant_elementos= ftell(archivo);
    rewind(archivo);

    char *texto= (char*)calloc(sizeof(char),cant_elementos);
    if(texto==NULL){
      perror("Error al reservar memoria");
      exit(1);
    }

    while(!feof(archivo)){
       fread(texto,sizeof(char),cant_elementos,archivo);
    }
    rewind(archivo);

    char *token, copia[cant_elementos];

    printf("\t\t\tTexto original.\n");
    imp_archivo(archivo);

    titulo(texto,cant_elementos,token,copia);
    espacios_antes_de_signos(archivo,texto,cant_elementos);

    cuenta_palabra_maxpalabra(archivo,buffer);
    printf("\nLa cantidad de lineas es= %d",cuenta_lienas(archivo));

    printf("\n");

    fclose(archivo);

    printf("\n\nDigite la ruta donde desea almacenar el nuevo archivo: ");
    char nomarchivo2[50];
    scanf("%s",nomarchivo2);

    escribir_segundo_archivo(nomarchivo2,texto);

    return 0;
}


void imp_archivo(FILE *archivo){

   char aux;

   printf("\n");
   while ((aux=fgetc(archivo))!=EOF){
      printf("%c",aux);
   }
   printf("\n");

   rewind(archivo);
}

void cuenta_palabra_maxpalabra(FILE *archivo,char buffer[]){

  int i=0;
  char pmayor[50];
  char pmenor[50];
  int signos=0;

  for(int i=0; i<50; i++){
      pmayor[i]=0;
      pmenor[i]=180;
    }

   while(fscanf(archivo,"%s",buffer) != EOF){

     if(strlen(buffer)>strlen(pmayor)){
         strcpy(pmayor,buffer);
      }
      if(strlen(buffer)<strlen(pmenor)){
         strcpy(pmenor,buffer);
      }
      if((buffer[0]== ',') || (buffer[0]== '.') || (buffer[0]== ';') || (buffer[0]== ':')){
         signos++;
      }
      i++;
   }

   printf("\nLa cantidad de palabras es= %d",(i-signos));
   printf("\nLa palabra mas larga es: %s",pmayor);
   printf("\nLa palabra mas corta es: %s",pmenor);

   rewind(archivo);
}


int cuenta_lienas(FILE *archivo){

 int lineas=0;
 char aux;

 while ((aux=fgetc(archivo))!=EOF){
   if(aux=='\n'){lineas++;}
 }

 return lineas;
 rewind(archivo);
}


char espacios_antes_de_signos(FILE *archivo, char *texto, int cant_elementos){

    int a=0, arreglos=0;

    while(texto[a]!= '\0'){
      if((texto[a]== ' '&& texto[a+1]== ' ') || (texto[a]== ' '&& texto[a+1]== ',') || (texto[a]== ' '&& texto[a+1]== '.') || (texto[a]== ' '&& texto[a+1]== ';')){
         for(int i=a; i<cant_elementos; i++){
            texto[i]= texto[i+1];
         }
         arreglos++;
         cant_elementos--;
      }
      a++;
    }

    texto[0]=toupper(texto[0]);

    printf("\n\n");
    printf("     %s",texto);
    printf("\n");
    printf("Cantidad de arreglos= %d",arreglos);

    rewind(archivo);
}


void titulo(char *texto, int cant_elementos,char *token, char copia[]){


    strcpy(copia,texto);

    token=strtok(copia,".");

    for(int i=0; copia[i]!= '\0'; i++){
       copia[i]=toupper(copia[i]);
    }

    printf("\t\t\tTexto corregido.\n");
    printf("\n");
    printf("\t\t\t%s.",token);
    printf("\n");
}


void escribir_segundo_archivo(char nomarchivo2, char *texto){

  FILE *archivo2;
  archivo2=fopen(nomarchivo2,"w");

    if (archivo2 == NULL){
       perror("Error al intentar crear el archivo");
       exit(1);
    }

  fputs(archivo2,texto);
  printf("\n\n%s\n",texto);

  fclose(archivo2);


}
