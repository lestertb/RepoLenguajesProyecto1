#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdbool.h>
#include <string.h>


//Imagen con tamaño por defecto para realizar re-ajuste.
struct sfImage* defaultSizeImgMax(){
    sfImage* resultImg =  sfImage_create(2048,1536);
    return resultImg;
}

//Imagen con tamaño por defecto para realizar re-ajuste.
struct sfImage* defaultSizeImg(){
    sfImage* resultImg =  sfImage_create(1080,720);
    return resultImg;
}



//Re-ajusta la imagen original a el tamaño predefinido de resizedImg
void testResize(const sfImage* originalImg, sfImage* resizedImg){

    const sfVector2u sizeOriginalImg = sfImage_getSize(originalImg);
    const sfVector2u sizeResizedImg = sfImage_getSize(resizedImg);

    for (unsigned int y = 0; y < sizeResizedImg.y; ++y)
    {
        for (unsigned int x = 0; x < sizeResizedImg.x; ++x)
        {
            unsigned int origX = (unsigned int) ((double) x / (double)sizeResizedImg.x * (double)sizeOriginalImg.x);
            unsigned int origY = (unsigned int) ((double) y / (double) sizeResizedImg.y * (double) sizeOriginalImg.y);
            sfImage_setPixel(resizedImg, x,y, sfImage_getPixel(originalImg,origX,origY));
        }
    }

}



//Funcion que verifica las restricciones del tamaño.
/*
 * ----Parametros--------
 * int x : el valor x del tamaño de la imagen
 * int y : el valor y del tamaño de la imagen
 * ----Returns--------
 *  0 : imagen no cumple mínimo
 *  -1 : imagen excede el máximo, requiere re ajustar el tamañp
 *  1 : imagen funciona
*/
int VerificarSizeImg(unsigned int x, unsigned int y){
    if (x < 390 && y < 250){
        return 0;
    }else if (x > 2048 && y > 1536){
        return -1;
    }else
        return 1;
}


//Funcion que crea la postal:
/*
 * ----Parametros--------
 * char* rutaImg : ruta donde se encuentra la imagen
 * int extension : valor que especifica la extension, 1 = jpg, 2 = png, 3 = bmp
*/

void CrearPostal(char* rutaImg, int extension, char* nombreResultado, char* text1, char* text2, int tipoLetra, int tamannoLetra){

    sfImage* img1 = sfImage_createFromFile(rutaImg);

    sfImage_flipVertically(img1);

    sfVector2u sizeImgToResize = sfImage_getSize(img1);

    struct sfImage* ImgDefaultSize;

    if (VerificarSizeImg(sizeImgToResize.x, sizeImgToResize.y) == 0){
        printf("\nLa imagen no tiene la resolucion minima que se requiere, intente con otra imagen");
        exit(0);
    }
    else if(VerificarSizeImg(sizeImgToResize.x, sizeImgToResize.y) == -1){
        printf("\nLa imagen excede el size maximo, re-ajustando la imagen al estandar");
        ImgDefaultSize = defaultSizeImg();
        testResize(img1,ImgDefaultSize);
    }else{
        printf("\nEstandarizando imagen para crear postal");
        ImgDefaultSize = defaultSizeImg();
        testResize(img1,ImgDefaultSize);
    }

    sfTexture* textureResized = sfTexture_createFromImage(ImgDefaultSize, NULL);

    sfImage* testImgResized  =  sfTexture_copyToImage(textureResized);

    sfVector2u sizeImg = sfImage_getSize(testImgResized);

    //Textos
    sfFont *font;
    if (tipoLetra == 1){
        font = sfFont_createFromFile("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\Fonts\\noto-sans-bold.ttf");
    }
    else if  (tipoLetra == 2){
        font = sfFont_createFromFile("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\Fonts\\Smith mouth.ttf");
    }
    else if (tipoLetra == 3){
        font = sfFont_createFromFile("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\Fonts\\The Loccosta FREE.ttf");
    }else{
        printf("\nEl tipo de letra ingresado no existe, colocando tipo de letra default: 1");
        font = sfFont_createFromFile("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\Fonts\\noto-sans-bold.ttf");
    }
    sfText *textArriba;

    sfText *textAbajo;

    int sizeLetra;

    if (tamannoLetra == 1){
        sizeLetra = 100;
    }
    else if  (tamannoLetra == 2){
        sizeLetra = 75;
    }
    else if (tamannoLetra == 3){
        sizeLetra = 50;
    }else{
        printf("\nEl tamanno de letra ingresado no existe, colocando tamanno default: 1");
        sizeLetra = 100;
    }

    textArriba = sfText_create();
    sfVector2f vecArriba  = { 0, 0 }; // posicion del texto
    sfText_setPosition(textArriba,vecArriba);
    sfText_setString(textArriba, text1);
    sfText_setFont(textArriba, font);
    sfText_setCharacterSize(textArriba, sizeLetra);

    textAbajo = sfText_create();
    sfVector2f vecAbajo  = { 0, 500 }; // posicion del texto
    sfText_setPosition(textAbajo,vecAbajo);
    sfText_setString(textAbajo, text2);
    sfText_setFont(textAbajo, font);
    sfText_setCharacterSize(textAbajo, sizeLetra);


    sfRenderTexture *texturWithText = sfRenderTexture_create(sizeImg.x, sizeImg.y, sfTrue);

    sfRenderTexture_drawText(texturWithText, textArriba, NULL);

    sfRenderTexture_drawText(texturWithText, textAbajo, NULL);

    sfTexture* renderTexturWithText =  (void*) sfRenderTexture_getTexture(texturWithText);

    sfTexture_updateFromImage(renderTexturWithText, img1, sizeImg.x, sizeImg.y);

    sfImage* resultImg =  sfTexture_copyToImage(renderTexturWithText);

    sfImage_flipVertically(resultImg);

    if (extension == 1){
        char* str1;
        char* str2;
        char* str3;
        str1 = "C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\";
        str2 = nombreResultado;
        str3 = ".jpg";
        char * str4 = (char *) malloc(1 + strlen(str1)+ strlen(str2) + strlen(str3));
        strcpy(str4, str1);
        strcat(str4, str2);
        strcat(str4, str3);
        sfImage_saveToFile(resultImg, str4);
        printf("\nImagen fue generada correctamente con size: x= %d y y= %d", sizeImg.x, sizeImg.y);
    }
    else if  (extension == 2){
        char* str1;
        char* str2;
        char* str3;
        str1 = "C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\";
        str2 = nombreResultado;
        str3 = ".png";
        char * str4 = (char *) malloc(1 + strlen(str1)+ strlen(str2) + strlen(str3));
        strcpy(str4, str1);
        strcat(str4, str2);
        strcat(str4, str3);
        sfImage_saveToFile(resultImg, str4);
        printf("\nImagen fue generada correctamente con size: x= %d y y= %d", sizeImg.x, sizeImg.y);
    }
    else if (extension == 3){
        char* str1;
        char* str2;
        char* str3;
        str1 = "C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\";
        str2 = nombreResultado;
        str3 = ".bmp";
        char * str4 = (char *) malloc(1 + strlen(str1)+ strlen(str2) + strlen(str3));
        strcpy(str4, str1);
        strcat(str4, str2);
        strcat(str4, str3);
        sfImage_saveToFile(resultImg, str4);
        printf("\nImagen fue generada correctamente con size: x= %d y y= %d", sizeImg.x, sizeImg.y);
    }else
        printf("La extension es invalida, intente con otra imagen");
}

int main() {
    //Crear postal con imagen por parametro
    //Postal con formato JPG
    CrearPostal("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\edificio.jpg",1,"resultado1","sdasdasdasdasdasdasdfasdnas dnas dkas jasnd nasjknd kj","aasdsaad",1,1);
    //Postal con formato PNG
    //CrearPostal("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\instagram.png",2,"resultado2","sdasdasdasdasdasdasdfasdnas dnas dkas jasnd nasjknd kj","aasdsaad",1,1);
    //Postal con formato BMP
    //CrearPostal("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\Bitmap3.bmp",3,"resultado3","sdasdasdasdasdasdasdfasdnas dnas dkas jasnd nasjknd kj","aasdsaad",1,1);

    return 0;
}
