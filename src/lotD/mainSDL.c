#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "mainSDL.h"

const int SCREEN_WIDTH  = 1430;
const int SCREEN_HEIGHT = 800;
/*const int TILE_SIZE = 40;*/
/**
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message to
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(char msg[]){
    printf("%s error: %s" ,msg,SDL_GetError());
    printf("\n");
}

/**
 * Loads a BMP image into a texture on the rendering device
 * @param file The BMP image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went wrong.
 */
SDL_Texture* loadTexture(char file[], SDL_Renderer *ren){
    /*Initialize to nullptr to avoid dangling pointer issues*/
    
    SDL_Texture *texture = IMG_LoadTexture(ren, file);
    
    if (texture == 0){
        logSDLError("LoadTexture");
    }
    return texture;
}

/**
 * Render the message we want to display to a texture for drawing
 * @param message The message we want to display
 * @param fontFile The font we want to use to render the text
 * @param color The color we want the text to be
 * @param fontSize The size we want the font to be
 * @param renderer The renderer to load the texture in
 * @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
 */
SDL_Texture* renderText_font(char message[] , char fontFile[],
                        SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
    /*Open the font*/
    TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
    if (font == 0){
        logSDLError("TTF_OpenFont");
        return 0;
    }
    /*We need to first render to a surface as that's what TTF_RenderText
    returns, then load that surface into a texture*/
    SDL_Surface *surf = TTF_RenderText_Blended(font, message, color);
    if (surf == 0){
        TTF_CloseFont(font);
        logSDLError("TTF_RenderText");
        return 0;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == 0){
        logSDLError("CreateTexture");
    }
    /*Clean up the surface and font*/
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
 * width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 * @param w The width of the texture to draw
 * @param h The height of the texture to draw
 */
void renderTexture_wh(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    /*Setup the destination rectangle to be at the position we want*/
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    renderTexture_wh(tex, ren, x, y, w, h);
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at some destination rect
 * taking a clip of the texture if desired
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param dst The destination rectangle to render the texture to
 * @param clip The sub-section of the texture to draw (clipping rect)
 *		default of nullptr draws the entire texture
 */
void renderTexture_clip(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
                   SDL_Rect *clip)
{
    SDL_RenderCopy(ren, tex, clip, &dst);
}

void affiche_Rules(SDL_Renderer *renderer)
{
    SDL_Color color1 = {238 ,238, 209, 25 };    
    char rules_1[1000]="1. Deux points pour chaque foret";
    char rules_2[1000]="2. Trois points pour nombre de (Lacs-1)";
    char rules_3[1000]="3. 4 points pour chaque ressource allouee a une usine";
    char rules_4[1000]="4. Nombre de villes contigues du plus grand village points";
    char rules_5[1000]="5. Une Usine ne peut traiter qu'une Ressource";
    char rules_6[1000]="6. une Ressource ne peut etre allouee qu'a une Usine";
    char rules_7[1000]="7. Une tuile ne peut etre totalement recouverte ";
    char rules_8[1000]="8. nouvelle tuile posee doit recouvrir au moins une case de l'une des tuiles";
    char rules_9[1000]="9. Aucune case Lac ne peut etre recouverte.";
    char rules_10[1000]="Click to return ";
    int size = 65;
    SDL_Texture *r1 = renderText_font(rules_1, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r2 = renderText_font(rules_2, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r3 = renderText_font(rules_3, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r4 = renderText_font(rules_4, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r5 = renderText_font(rules_5, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r6 = renderText_font(rules_6, "ttf/Chocolate.ttf",color1, size, renderer);

    SDL_Texture *r7 = renderText_font(rules_7, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r8 = renderText_font(rules_8, "ttf/Chocolate.ttf",color1, size, renderer);
    SDL_Texture *r9 = renderText_font(rules_9, "ttf/Chocolate.ttf",color1, size, renderer);
    
    SDL_Texture *r10 = renderText_font(rules_10, "ttf/Chocolate.ttf",color1, size+10, renderer);
    

    SDL_Texture *background = loadTexture("image/O.png",renderer);
     SDL_SetTextureBlendMode(background,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background,200);
    int pos_x=20;

    int quit =0;
    SDL_Event e;
    while(quit==0)
    {
       
        while(SDL_PollEvent(&e))
        {
            if (e.type==SDL_MOUSEBUTTONDOWN)
            {
                quit=1;
            }
        }
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0);
    renderTexture(r1, renderer,pos_x, 0*50+20);
    renderTexture(r2, renderer,pos_x, 1*50+20);
    renderTexture(r3, renderer,pos_x, 2*50+20);
    renderTexture(r4, renderer,pos_x, 3*50+20);
    renderTexture(r5, renderer,pos_x, 4*50+20);
    renderTexture(r6, renderer,pos_x, 5*50+20);
    renderTexture(r7, renderer,pos_x, 6*50+20);
    renderTexture(r8, renderer,pos_x, 7*50+20);
    renderTexture(r9, renderer,pos_x, 8*50+20);
    renderTexture(r10, renderer,pos_x+800, 9*50+50);
     SDL_RenderPresent(renderer);
     
    }

}



int affiche_index(SDL_Renderer *renderer)
{
    SDL_Texture *background = loadTexture("image/P1.png",renderer);
    SDL_SetTextureBlendMode(background,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background,220);
    SDL_Color color = { 250, 251, 100, 255 };
    SDL_Color color1 = { 255,228,181 ,255};    
    SDL_Texture *image = renderText_font("welcome to honshu", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color, 160, renderer);
    SDL_Texture *image2 = renderText_font("Click here to begin playing", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color1, 70, renderer);
    
    SDL_Texture *file   = renderText_font("begin with a file", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color1, 70, renderer);

    SDL_Texture *image3 = renderText_font("Show rules", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color1, 70, renderer);
    
    SDL_Texture *image4 = renderText_font("Leave", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color1, 70, renderer);

    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT /4;
    
    SDL_Event e;
    int quit =0;
    int res = 0;
    while(!quit){
          SDL_RenderClear(renderer);
        renderTexture(background, renderer, 0, 0);
        renderTexture(image, renderer, x, y);
        renderTexture(image2, renderer, x+iW/5, y+iH);
        renderTexture(image3,renderer,200,650);
        renderTexture(image4,renderer,1020,640);
        renderTexture(file,renderer,x+iW/5,y+iH+100);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT)
                quit = 1;
            if (e.type==SDL_MOUSEBUTTONDOWN)
            {
                /*on clique sur show rules*/
                if(e.button.button==SDL_BUTTON_LEFT && e.button.x>=200 && 
                e.button.x<=450 && e.button.y>=650 &&e.button.y<=760)
                {
                     affiche_Rules(renderer);
                }
                /*clique sur Begin here*/
                else if(e.button.button==SDL_BUTTON_LEFT && e.button.x>=x+iW/5 && 
                e.button.x<=1000 && e.button.y>=y+iH &&e.button.y<=y+iH+120)
                {
                quit = 1;
                res = 1;
                }
                /*clique sur Leave*/
                else if(e.button.button==SDL_BUTTON_LEFT && e.button.x>=950&& 
                e.button.x<=1150 && e.button.y>=650 &&e.button.y<=760)
                {
                quit = 1;
                res = 0;
                }
                /*clique sur begin with a file*/
                else if(e.button.button==SDL_BUTTON_LEFT && e.button.x>=x+iW/5&& 
                e.button.x<=800 && e.button.y>=y+iH+100 &&e.button.y<=y+iH+240)
                {
                quit = 1;
                res = 2;
                }
            }
        }      
    }
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image2);
    SDL_DestroyTexture(image3);
    SDL_DestroyTexture(image4);
    return res;
}

void affiche_grille(SDL_Renderer *renderer,grille g)
{
    SDL_Texture *background = loadTexture("image/K1.png",renderer);
    SDL_SetTextureBlendMode(background,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background,255/2);
    SDL_Texture *Hligne = loadTexture("image/Hligne.png",renderer);

    
    SDL_Texture *Vligne = loadTexture("image/Vligne.png",renderer);
    SDL_Texture *Ville = loadTexture("image/V.png",renderer);
    SDL_Texture *Usine = loadTexture("image/U.png",renderer);
    SDL_Texture *Plate = loadTexture("image/P.png",renderer);
    SDL_Texture *Forest = loadTexture("image/F.png",renderer);
    SDL_Texture *Ressouce = loadTexture("image/R.png",renderer);
    SDL_Texture *Lac = loadTexture("image/L.png",renderer);
    
        renderTexture(background, renderer, 0, 0);
        int i=10;
        for (i=10; i<=610; i=i+60) {
            renderTexture(Vligne, renderer, i, 10);
            renderTexture(Hligne, renderer, 10, i);
        }
        int x, y;
        for (x=0; x<g->size; x++){
            for (y=0; y<g->size; y++){
                int pos_y = 15 + x*60;
                int pos_x = 15 + y*60;
                switch(lecture_grille(x, y, g)){
                    case 'P':
                        renderTexture(Plate, renderer, pos_x, pos_y);
                        break;
                    case 'F':
                        renderTexture(Forest, renderer, pos_x, pos_y);
                        break;
                    case 'L':
                        renderTexture(Lac, renderer, pos_x, pos_y);
                        break;
                    case 'V':
                        renderTexture(Ville, renderer, pos_x, pos_y);
                        break;
                    case 'U':
                        renderTexture(Usine, renderer, pos_x, pos_y);
                        break;
                    case 'R':
                        renderTexture(Ressouce, renderer, pos_x, pos_y);
                    default:
                        break;
                }
            }
        } 
        SDL_DestroyTexture(Hligne);
        SDL_DestroyTexture(Vligne);
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(Ville);
        SDL_DestroyTexture(Usine);
        SDL_DestroyTexture(Plate);
        SDL_DestroyTexture(Forest);
        SDL_DestroyTexture(Ressouce);
        SDL_DestroyTexture(Lac);
}

void affiche_piletuile(SDL_Renderer *renderer,/*grille g,*/pile p)
{   
    SDL_Texture *Ville = loadTexture("image/V.png",renderer);
    SDL_Texture *Usine = loadTexture("image/U.png",renderer);
    SDL_Texture *Plate = loadTexture("image/P.png",renderer);
    SDL_Texture *Forest = loadTexture("image/F.png",renderer);
    SDL_Texture *Ressouce = loadTexture("image/R.png",renderer);
    SDL_Texture *Lac = loadTexture("image/L.png",renderer);

    int pos_x = 0;
    int pos_y = 0;
    
    SDL_Color color = { 20, 21, 25, 25 };
        int i,x,y;
         for (i=0; i<p.som; i++){
              char s[3];
              sprintf(s, "%d", i);
              if( p.t[i]->pos[0] == -1)
              {
              SDL_Texture *image = renderText_font(s, "ttf/planetbe.ttf",color, 20, renderer);
              pos_x = i%4;
              pos_y = i/4;
              renderTexture(image, renderer, 755+pos_x*180, pos_y*220);
             }
            
        }
        
        for (i=0; i<p.som; i++)
        {
            for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++){
                 pos_x = 700 + (i%4)*180+ x*60;
                 pos_y = 30 + (i/4)*220+y*60;
                if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x]){
                    case 'P':
                        renderTexture(Plate, renderer, pos_x, pos_y);
                        break;
                    case 'F':
                        renderTexture(Forest, renderer, pos_x, pos_y);
                        break;
                    case 'L':
                        renderTexture(Lac, renderer, pos_x, pos_y);
                        break;
                    case 'V':
                        renderTexture(Ville, renderer, pos_x, pos_y);
                        break;
                    case 'U':
                        renderTexture(Usine, renderer, pos_x, pos_y);
                        break;
                    case 'R':
                        renderTexture(Ressouce, renderer, pos_x, pos_y);
                    default:
                        break;
                }
                }
              }
            }
        }
    SDL_DestroyTexture(Ville);
    SDL_DestroyTexture(Usine);
    SDL_DestroyTexture(Forest);
    SDL_DestroyTexture(Ressouce);
    SDL_DestroyTexture(Plate);
    SDL_DestroyTexture(Lac);
}

int numerotuile_clique(int x,int y)
{
    int i=0,j=0;
    if(x<=820 && x>=700)
        i=1;
    if(x<=1000 && x>=880)
        i=2;
    if(x<=1180 && x>=1060)
        i=3;
    if(x<=1360 && x>=1240)
        i=4;
    if(y<=210 && y>=30)
        j=1;
    if(y<=430 && y>=250)
        j=2;
    if(y<=650 && y>=470)
        j=3;
    
    if(i==0 || j==0) /*on a pas cliqué sur les tuiles*/
        return -1;
    return (i-1)+(j-1)*4;
}

int Poser_tuile(int i,pile p,grille g,int x,int y)
{
    tuile tuile_test = ini_tuile();
    inser_tuile(g, p.t[i], x, y);

    return end_of_game(g,p,tuile_test);
}

void Affiche_Rotation_tuile(SDL_Renderer *renderer,int i,pile p,char ort)
{
    SDL_Texture *Ville = loadTexture("image/V.png",renderer);
    SDL_Texture *Usine = loadTexture("image/U.png",renderer);
    SDL_Texture *Plate = loadTexture("image/P.png",renderer);
    SDL_Texture *Forest = loadTexture("image/F.png",renderer);
    SDL_Texture *Ressouce = loadTexture("image/R.png",renderer);
    SDL_Texture *Lac = loadTexture("image/L.png",renderer);
    int w, h;
    SDL_QueryTexture(Ville, NULL, NULL, &w, &h);
    int x,y;
    if(ort=='^')
    {
    for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++){
                 int pos_x = 700 + (i%4)*180+ x*60;
                 int pos_y = 30 + (i/4)*220+y*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x]){
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,1.2*w,1.2*h);
                    default:
                        break;
                    }
                }
            }
           }
    }
    if(ort=='>')
    {
    for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++){
                 int pos_x = 820 + (i%4)*180- y*60;
                 int pos_y = 45 + (i/4)*220+x*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x]){
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,1.2*w,1.2*h);
                    default:
                        break;
                    }
                }
            }
           }
    }
    if(ort=='v')
    {
     for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++){
                 int pos_x = 760 + (i%4)*180- x*60;
                 int pos_y = 150 + (i/4)*220-y*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x]){
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,1.2*w,1.2*h);
                    default:
                        break;
                    }
                }
            }
           }
    }
    if(ort=='<')
    {
     for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++){
                 int pos_x = 670 + (i%4)*180+ y*60;
                 int pos_y = 120 + (i/4)*220-x*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x]){
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,1.2*w,1.2*h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,1.2*w,1.2*h);
                    default:
                        break;
                    }
                }
            }
         }
    }
    SDL_DestroyTexture(Ville);
        SDL_DestroyTexture(Usine);
        SDL_DestroyTexture(Plate);
        SDL_DestroyTexture(Forest);
        SDL_DestroyTexture(Ressouce);
        SDL_DestroyTexture(Lac);
}

/*Move tile with the mouse*/
void Affiche_Move_tuile(SDL_Renderer *renderer,int x_m,int y_m,int i,pile p)
{
    SDL_Texture *Ville = loadTexture("image/V.png",renderer);
    SDL_Texture *Usine = loadTexture("image/U.png",renderer);
    SDL_Texture *Plate = loadTexture("image/P.png",renderer);
    SDL_Texture *Forest = loadTexture("image/F.png",renderer);
    SDL_Texture *Ressouce = loadTexture("image/R.png",renderer);
    SDL_Texture *Lac = loadTexture("image/L.png",renderer);

    SDL_SetTextureBlendMode(Ville,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(Ville,255/2);
    SDL_SetTextureBlendMode(Usine,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(Usine,255/2);
    SDL_SetTextureBlendMode(Plate,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(Plate,255/2);
    SDL_SetTextureBlendMode(Forest,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(Forest,255/2);
    SDL_SetTextureBlendMode(Ressouce,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(Ressouce,255/2);
    SDL_SetTextureBlendMode(Lac,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(Lac,255/2);
    int w, h;
    SDL_QueryTexture(Ville, NULL, NULL, &w, &h);
    int x,y;
    x_m = ((x_m-10)/60)*60+15;
    y_m = ((y_m-10)/60)*60+15;
    char ort = p.t[i]->ort;
    if(ort=='^')
        {
            for(x=0;x<2;x++)
            {
                for (y=0; y<3; y++)
                {
                     int pos_x = x_m + x*60;
                     int pos_y = y_m + y*60;
                    if( p.t[i]->pos[0] == -1)
                    {
                    switch(p.t[i]->point[y][x])
                       {
                        case 'P':
                            renderTexture_wh(Plate, renderer, pos_x, pos_y,w,h);
                            break;
                        case 'F':
                            renderTexture_wh(Forest, renderer, pos_x, pos_y,w,h);
                            break;
                        case 'L':
                            renderTexture_wh(Lac, renderer, pos_x, pos_y,w,h);
                            break;
                        case 'V':
                            renderTexture_wh(Ville, renderer, pos_x, pos_y,w,h);
                            break;
                        case 'U':
                            renderTexture_wh(Usine, renderer, pos_x, pos_y,w,h);
                            break;
                        case 'R':
                            renderTexture_wh(Ressouce, renderer, pos_x, pos_y,w,h);
                        default:
                            break;
                        }
                    }
                }
            }
        }
        if(ort=='>')
        {
            for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++)
             {
                 int pos_x = x_m- y*60;
                 int pos_y = y_m +x*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x])
                {
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,w,h);
                    default:
                        break;
                    }
                }
            }
           }
        }
         if(ort=='v')
         {
            for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++)
             {
                 int pos_x = x_m - x*60;
                 int pos_y = y_m -y*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x])
                {
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,w,h);
                    default:
                        break;
                    }
                }
             }
           }
         }
         if(ort=='<')
         {
            for(x=0;x<2;x++)
            {
             for (y=0; y<3; y++)
             {
                 int pos_x = x_m +  y*60;
                 int pos_y = y_m -x*60;
                 if( p.t[i]->pos[0] == -1)
                {
                switch(p.t[i]->point[y][x])
                {
                    case 'P':
                        renderTexture_wh(Plate, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'F':
                        renderTexture_wh(Forest, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'L':
                        renderTexture_wh(Lac, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'V':
                        renderTexture_wh(Ville, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'U':
                        renderTexture_wh(Usine, renderer, pos_x, pos_y,w,h);
                        break;
                    case 'R':
                        renderTexture_wh(Ressouce, renderer, pos_x, pos_y,w,h);
                    default:
                        break;
                    }
                }
            }
         }
    }     
    SDL_DestroyTexture(Ville);
        SDL_DestroyTexture(Usine);
        SDL_DestroyTexture(Plate);
        SDL_DestroyTexture(Forest);
        SDL_DestroyTexture(Ressouce);
        SDL_DestroyTexture(Lac);        
}

int btg_Clique_une_tuile(SDL_Renderer *renderer, int i,pile p,grille g)
{
    SDL_Texture *Ville = loadTexture("image/V.png",renderer);
    SDL_Texture *Usine = loadTexture("image/U.png",renderer);
    SDL_Texture *Plate = loadTexture("image/P.png",renderer);
    SDL_Texture *Forest = loadTexture("image/F.png",renderer);
    SDL_Texture *Ressouce = loadTexture("image/R.png",renderer);
    SDL_Texture *Lac = loadTexture("image/L.png",renderer);
   /* SDL_Color c_w={255,0,0,0};
    SDL_Texture *warning_no_tuile  = renderText_font("Click right click to rotate the tuile and click on the grille", "ttf/Chocolate.ttf",c_w, 90, renderer);
    renderTexture(warning_no_tuile, renderer,SCREEN_WIDTH/30,  SCREEN_HEIGHT*6/7  );
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);*/
    int w, h;
    SDL_QueryTexture(Ville, NULL, NULL, &w, &h);
    int fin=0;
    SDL_Event e;
    int quit =0;
    rot_tuile(p.t[i],'^');
    int x_m,y_m;
    while(quit==0)
    {
        if(p.t[i]->pos[0] == -1)
        {
        SDL_RenderClear(renderer);
        affiche_grille(renderer,g);
        if(x_m>=10 && x_m<=610 && y_m>=10 &&y_m<=610)
        {
        Affiche_Move_tuile(renderer,x_m,y_m,i,p);
        }
        Affiche_Rotation_tuile(renderer,i,p,p.t[i]->ort);
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&e))
        {    
            if(e.type == SDL_MOUSEMOTION)
            {
                x_m = e.motion.x;
                y_m = e.motion.y;
            }       
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_RIGHT)
                {
                    char ort=p.t[i]->ort;
                    /*sens des aiguilles d'une montre*/
                    if(ort=='^')
                        rot_tuile(p.t[i],'>');
                    else if(ort=='>')
                        rot_tuile(p.t[i],'v');
                    else if(ort=='v')
                        rot_tuile(p.t[i],'<');
                    else 
                        rot_tuile(p.t[i],'^');
                    SDL_RenderClear(renderer);
                    affiche_grille(renderer,g);
                    Affiche_Rotation_tuile(renderer,i,p,p.t[i]->ort);
                }
                /*on a cliqué sur la grille*/
                if(e.button.button==SDL_BUTTON_LEFT && e.button.x>=10 && 
                e.button.x<=610 && e.button.y>=10 &&e.button.y<=610)
                {
                     int y = (e.button.x-10)/60;
                     int x = (e.button.y-10)/60;
                     printf("x y add_to_grille %d %d %d\n",x,y,add_to_grille(g,p.t[i],x,y,0));
                     if(add_to_grille(g,p.t[i],x,y,0)==1)
                     {
                        fin = Poser_tuile(i,p,g,x,y);
                        affiche_piletuile(renderer,p);
                        quit=1;
                     }
                     else
                     {
                        SDL_Color color1={255,0,0,0};
                        SDL_Texture *warning_cor = renderText_font("It is not a correct position please respect the rules", "ttf/Girls.ttf",
                                    color1, 60, renderer);
                        renderTexture(warning_cor,renderer,SCREEN_WIDTH/10,SCREEN_HEIGHT/7);
                        SDL_RenderPresent(renderer);
                        SDL_DestroyTexture(warning_cor);
                        SDL_Delay(1400);
                        continue;
                     }
                     
                }
                if( e.button.button==SDL_BUTTON_LEFT)
                {
                    affiche_piletuile(renderer,p);
                    quit=1;
                }
            } 

        }
        }
        
    }
    
    SDL_DestroyTexture(Ville);
    SDL_DestroyTexture(Usine);
    SDL_DestroyTexture(Forest);
    SDL_DestroyTexture(Ressouce);
    SDL_DestroyTexture(Plate);
    SDL_DestroyTexture(Lac);
    return fin;
}

void affiche_score(SDL_Renderer *renderer,grille g)
{
    int sc = score(g);
    char s[4];
    sprintf(s, "%d", sc);
    SDL_Color color = {255,30,30,255};
    SDL_Texture *image = renderText_font("Your score is : ", "ttf/planetbe.ttf",color, 40, renderer);
    SDL_Texture *image1 = renderText_font(s, "ttf/planetbe.ttf",color, 40, renderer);
    renderTexture(image, renderer, 100, 620);
    renderTexture(image1, renderer, 500, 620);
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(image1);
}

int Fin_du_jeu()
{
    int res;
    int quit =0;
    SDL_Event e;
    while(!quit){  
        while (SDL_PollEvent(&e))
        {
             if(e.type==SDL_MOUSEBUTTONDOWN)
             {
                if (e.button.button==SDL_BUTTON_LEFT &&
                  e.button.x>=SCREEN_WIDTH*2/3 && e.button.x<=SCREEN_WIDTH*2/3+200 
                  && e.button.y>=SCREEN_HEIGHT*4/5 &&e.button.y<=SCREEN_HEIGHT*4/5+100)
                 {
                     res = 1;
                     quit=1;
                 } 
                else if(e.button.button==SDL_BUTTON_LEFT&&
                e.button.x>=SCREEN_WIDTH*2/3 && e.button.x<=SCREEN_WIDTH*2/3+200 
                 && e.button.y>=SCREEN_HEIGHT/5 &&e.button.y<=SCREEN_HEIGHT/5+100 )
                {
                res = 0;
                quit=1;
                }
             else
                 continue;
             }   
        }
    }
    
    return res;
}


void Jeu(SDL_Renderer *renderer,SDL_Window *window,grille g,pile p)
{
    int numerotuile=-1;
    SDL_Event e;
    int quit =0;
    int size=80;
     SDL_Color color = {0,255,255,255};
    SDL_Texture *Solution  = renderText_font("Solution", "ttf/Chocolate.ttf",color, size, renderer);
    SDL_Texture *Leave  = renderText_font("Leave", "ttf/Chocolate.ttf",color, size, renderer);
    SDL_Texture *Retire  = renderText_font("Remove", "ttf/Chocolate.ttf",color, size, renderer);
    SDL_Texture *index  = renderText_font(" Home ", "ttf/Chocolate.ttf",color, size, renderer);
    while(!quit){
        SDL_RenderClear(renderer);
        renderTexture(Solution, renderer, SCREEN_WIDTH/7+60, SCREEN_HEIGHT*6/7 );
        renderTexture(Leave, renderer,SCREEN_WIDTH*6/7, SCREEN_HEIGHT*6/7 );
        renderTexture(index, renderer,SCREEN_WIDTH/30, SCREEN_HEIGHT*6/7 );
        renderTexture(Retire, renderer,SCREEN_WIDTH*3/7-110, SCREEN_HEIGHT*6/7 );
        affiche_grille(renderer,g);
        affiche_piletuile(renderer,p);
        affiche_score(renderer,g);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&e))
        {
        if (e.type == SDL_QUIT)
            quit = 1;
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
             /*On clique sur home*/
            if(e.button.button== SDL_BUTTON_LEFT && e.button.x>=SCREEN_WIDTH/30 && 
               e.button.x<=SCREEN_WIDTH/30+150 && e.button.y>=SCREEN_HEIGHT*6/7 
               &&e.button.y<=SCREEN_HEIGHT*6/7+80)
            {
                g=create(10);
                p=initi_tuiles(12);
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                mainSDL(g,p);
                quit=1;
            }
            /*On clique sur Solution*/
            if(e.button.button== SDL_BUTTON_LEFT && e.button.x>=SCREEN_WIDTH/7+60 && 
               e.button.x<=SCREEN_WIDTH/7+230 && e.button.y>=SCREEN_HEIGHT*6/7 
               &&e.button.y<=SCREEN_HEIGHT*6/7+80)
            {
                pile p_res = initi_tuiles(p.som);
                int best_s = solveur(g,p,p_res);
                best_s=0;
                SDL_RenderClear(renderer);           
                int size_image =80;
                SDL_Color color = {0,255,255,255};
                SDL_Texture *image  = renderText_font("Play Again!", "ttf/Chocolate.ttf",color, size_image, renderer);

                SDL_Texture *image1 = renderText_font("Leave?", "ttf/Chocolate.ttf",color, size_image, renderer);
                renderTexture(image, renderer, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*4/5 );
                renderTexture(image1, renderer,SCREEN_WIDTH*2/3, SCREEN_HEIGHT/5 );
                SDL_DestroyTexture(image);
                SDL_DestroyTexture(image1);
                affiche_grille(renderer,g);
                int i;
                for(i=0;i<p.som;i++)
                    p.t[i]->pos[0]=0;
                affiche_piletuile(renderer,p);
                affiche_score(renderer,g);
                SDL_RenderPresent(renderer);
               
                int res = Fin_du_jeu();
                printf("Fin_du_jeu %d \n",res);
                if (res ==0)
                    quit = 1;
                else
                {
                int size=10;
                g = create(size);
                int nbt=12;
                p = initi_tuiles(nbt);
                }
            }

            /*On clique sur Leave*/
            if(e.button.button== SDL_BUTTON_LEFT && e.button.x>=SCREEN_WIDTH*6/7 && 
               e.button.x<=SCREEN_WIDTH*6/7+120 && e.button.y>=SCREEN_HEIGHT*6/7 
               &&e.button.y<=SCREEN_HEIGHT*6/7+80)
            {
                 quit = 1;
            }

            /*On clique sur Remove*/
            if(e.button.button== SDL_BUTTON_LEFT && e.button.x>=SCREEN_WIDTH*3/7-110 && 
               e.button.x<=SCREEN_WIDTH*3/7+120 && e.button.y>=SCREEN_HEIGHT*6/7 
               &&e.button.y<=SCREEN_HEIGHT*6/7+80)
            {
                int i=0,nb=0;
                for(i=0;i<12;i++)
                {
                    if(p.t[i]->pos[0]!=-1)
                        nb++;
                }
                if(nb!=0)
                retrait(g,&p);
                else{
                    SDL_Color c_w={255,0,0,0};
                    SDL_Texture *warning_no_tuile  = renderText_font("No tuile insert,you can't remove", "ttf/Chocolate.ttf",c_w, 90, renderer);
                    renderTexture(warning_no_tuile, renderer,SCREEN_WIDTH/3,  SCREEN_HEIGHT/3  );
                    SDL_RenderPresent(renderer);
                     SDL_DestroyTexture(warning_no_tuile);
                    SDL_Delay(1000);
                }
            }

            /*cadre de button pour les tuile*/ 
           if(e.button.button== SDL_BUTTON_LEFT && e.button.x>=700 && 
               e.button.x<=1360 && e.button.y>=30 &&e.button.y<=680)
            {
            numerotuile = numerotuile_clique(e.button.x,e.button.y);
            if(numerotuile<0) /*on n'a chiqué sur aucune tuile*/
                continue;
            printf("DL_BUTTON_LEFT,%d,%hhu\n",numerotuile,e.button.button);
            int fin = btg_Clique_une_tuile(renderer,numerotuile,p,g);
            /*Il y a encore les tuile qui n'a pas eté posé*/
            if (fin ==0)
                continue;
            /*Fin du jeu*/
            else 
            {
                SDL_RenderClear(renderer);           
                int size_image =80;
                SDL_Color color = {0,255,255,255};
                SDL_Texture *image  = renderText_font("Play Again!", "ttf/Chocolate.ttf",color, size_image, renderer);

                SDL_Texture *image1 = renderText_font("Leave?", "ttf/Chocolate.ttf",color, size_image, renderer);
 
                renderTexture(image, renderer, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*4/5 );
                renderTexture(image1, renderer,SCREEN_WIDTH*2/3, SCREEN_HEIGHT/5 );
                SDL_DestroyTexture(image); 
                SDL_DestroyTexture(image1); 
                affiche_grille(renderer,g);
                affiche_piletuile(renderer,p);
                affiche_score(renderer,g);
                SDL_RenderPresent(renderer);
                printf("Fin_du_jeu\n");
                int res = Fin_du_jeu();
                if (res ==0)
                    quit = 1;
                else
                {
                int size=10;
                g = create(size);
                int nbt=12;
                p = initi_tuiles(nbt);
                }
            }
            printf("back\n");
            }
            else if(e.button.button== SDL_BUTTON_LEFT && e.button.y<=680)
            {
                 SDL_Color c_w={255,0,0,0};
                 SDL_Texture *warning_no_tuile  = renderText_font("Click on a tuile", "ttf/Chocolate.ttf",c_w, 100, renderer);
                 renderTexture(warning_no_tuile, renderer,SCREEN_WIDTH/3,  SCREEN_HEIGHT/3  );
                 SDL_DestroyTexture(warning_no_tuile);
                 SDL_RenderPresent(renderer);
                 SDL_Delay(1000);
            }
        }
        }
     }
        SDL_DestroyTexture(Solution);
        SDL_DestroyTexture(Leave);
        SDL_DestroyTexture(index);
        SDL_DestroyTexture(Retire);
        
     
}
 /*if( ( SDL_GetKeyName(event.key.keysym.sym) >= '0' ) && ( SDL_GetKeyName(event.key.keysym.sym)<= '9' ) )
                    {
                       //Append the character
                       char b[1];
                       b[0]=SDL_GetKeyName(event.key.keysym.sym);
                       strcat(file_name,b);
                    }
                    //If the key is a uppercase letter
                    else if( ( SDL_GetKeyName(event.key.keysym.sym)>= 'A' ) && ( SDL_GetKeyName(event.key.keysym.sym) <= 'Z' ) )
                    {
                         //Append the character
                       char b[1];
                       b[0]=(char)SDL_GetKeyName(event.key.keysym.sym) ;
                       strcat(file_name,b);
                    }
                    //If the key is a lowercase letter
                    else if( (SDL_GetKeyName(event.key.keysym.sym) >= 'a' ) && ( SDL_GetKeyName(event.key.keysym.sym)<= 'z' ) )
                    {
                       //Append the character
                       char b[1];
                       b[0]=(char)SDL_GetKeyName(event.key.keysym.sym);
                       strcat(file_name,b);
                    }*/
void Begin_with_file(SDL_Renderer * renderer,SDL_Window * window,grille g)
{
    SDL_Texture *background = loadTexture("image/Y.png",renderer);
    SDL_SetTextureBlendMode(background,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background,170);
    SDL_Color color = { 255 ,255 ,240 ,255  };
    SDL_Texture *image = renderText_font("input the name of file :", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color, 100, renderer);
   
    SDL_Color color1= { 255, 255 ,240, 255  };
    SDL_Texture *image2 = renderText_font("Home", "ttf/MotionPicture_PersonalUseOnly.ttf",
                                    color1, 100, renderer);

    char file_name[1000]="";
    SDL_Event event;
    int quit = 0;
    while(quit==0){
       
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                quit = 1;
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT && event.button.x>=950&& 
                event.button.x<=1150 && event.button.y>=650 &&event.button.y<=760)
                {
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                pile p = initi_tuiles(12);
                mainSDL(g,p);
                quit=1;
                }
            }
            if( event.type == SDL_KEYDOWN )
                {
                    if(event.key.keysym.sym==SDLK_BACKSPACE)
                    {
                       file_name[strlen(file_name)-1]=0;
                    }
                    else if(event.key.keysym.sym==SDLK_RETURN)
                    {
                        FILE* fp;
                        for(int i=0;i<(int)sizeof(file_name);i++)
                        {
                            file_name[i]=tolower(file_name[i]);
                        }
                         printf("%s is  file_name \n",file_name);
                        if(( fp = fopen(file_name, "r"))==NULL)
                        {
                          SDL_Texture *warning_file_nom = renderText_font("file_name is not correct,please retype", "ttf/Girls.ttf",
                                    color, 80, renderer);
                          memset(file_name, 0, sizeof(file_name));
                          SDL_RenderClear(renderer);
                          renderTexture(background,renderer,0,0);
                          renderTexture(warning_file_nom,renderer,100,100);
                          SDL_RenderPresent(renderer);
                          SDL_DestroyTexture(warning_file_nom);
                          SDL_Delay(1500);
                        }
                        else{
                         int nbt;
                         pile p = initi_tuile_fichier(fp,&nbt);
                         Jeu(renderer,window,g,p);
                         quit=1;
                        }
                         
                    }
                    else{
                         strcat(file_name,SDL_GetKeyName(event.key.keysym.sym));
                    }
                }
        }
        SDL_RenderClear(renderer);
        renderTexture(background,renderer,0,0);
         renderTexture(image2, renderer,950, 650 );
        renderTexture(image,renderer,SCREEN_WIDTH/10,SCREEN_HEIGHT/3);
       
        if(strlen(file_name)>0)
        {
        SDL_Texture *image1 = renderText_font(file_name, "ttf/Girls.ttf",
                                    color, 100, renderer);
        renderTexture(image1,renderer,SCREEN_WIDTH/2,SCREEN_HEIGHT/3+100);
        SDL_DestroyTexture(image1);
        }
        SDL_RenderPresent(renderer);    
        
    }
    SDL_DestroyTexture(image);

    SDL_DestroyTexture(background);
}
int mainSDL(grille g,pile p)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError("SDL_Init");
        return 1;
    }
    
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
        logSDLError("IMG_Init");
        SDL_Quit();
        return 1;
    }
    
    if (TTF_Init() != 0){
        logSDLError( "TTF_Init");
        SDL_Quit();
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("honshu", 1000, 1000, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == 0){
        logSDLError("CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == 0){
        logSDLError( "CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    int res = affiche_index(renderer);
   
    if(res == 0)
    {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    }
    
    else if(res == 1){
        Jeu(renderer,window,g,p);
    }
    else{
        Begin_with_file(renderer,window,g);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
    return 0;
}
