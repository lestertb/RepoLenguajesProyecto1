#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>



void testImg(){

    sfImage* img1 = sfImage_createFromFile("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\edificio.jpg");

    sfImage_flipVertically(img1);

    sfTexture* texture = sfTexture_createFromImage(img1, NULL);

    sfImage* testImg =  sfTexture_copyToImage(texture);

    sfFont *font;
    sfText *text;

    sfVector2u size = sfImage_getSize(testImg);

    font = sfFont_createFromFile("C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\Fonts\\noto-sans-bold.ttf");
    text = sfText_create();
    sfVector2f vec  = { 0, 0 }; // posicion del texto
    //sfText_setRotation(text,320);
    sfText_setPosition(text,vec);
    sfText_setString(text, "hola");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 100);

    sfRenderTexture *texturWithText = sfRenderTexture_create(size.x, size.y, sfTrue);

    //sfImage_flipVertically(testImg);

    sfRenderTexture_drawText(texturWithText, text, NULL);

    //sfRenderTexture_display(texturWithText);

    sfTexture* si =  (void*) sfRenderTexture_getTexture(texturWithText);

    sfTexture_updateFromImage(si,img1,size.x, size.y);

    sfImage* im =  sfTexture_copyToImage(si);

    sfImage_flipVertically(im);

    sfImage_saveToFile(im, "C:\\Users\\Lester Trejos\\Documents\\RepoLenguajesProyecto1\\repolenguajesproyecto1\\Proyecto1Lenguajes\\Assets\\edificio2.jpg");
    printf("\nx= %d y y= %d", size.x, size.y);
}


int main() {

    testImg();

    return 0;
}