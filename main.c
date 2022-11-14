#include "Biblio.h"

int main()
{
    clock_t tDebut;
    srand(time(NULL));

    initialisationAllegro();
    printf(" \n Initialisation okk ");

    t_jeu *Jeu = (t_jeu*)malloc(sizeof(t_jeu));
    initialisation_struct_Jeu(Jeu);


    printf("\n pre creation matrice \n");

    int case_tot = MAPTX * MAPTY; /// Nombre de cases en France

    Jeu->MAP = Creation_Matrice(); /// On crée la matrice contenant toutes les cases du jeu

    printf("\n On entre la boucle de Jeu \n");
    tDebut = clock ();
    sauvegardePartie(Jeu);

    while (!key[KEY_ESC])
    {
        clear_bitmap(Jeu->buffer);

        quadrillage_MAP(Jeu);
        affichage_icones(Jeu);

        recherche_Niveau0(Jeu);

        cycle_temps_sauvegarde(Jeu, tDebut);

        //printf("\n affichage icone ok");
        selection_icone(Jeu);




        rest(10);
        show_mouse(screen);
        textprintf_ex(Jeu->buffer, font, SCREEN_W - 180, SCREEN_H - 50, makecol(250,0,250), -1,"position x :%d",mouse_x);
        textprintf_ex(Jeu->buffer, font, SCREEN_W - 180, SCREEN_H - 40, makecol(250,0,250), -1,"position y :%d",mouse_y);

        blit(Jeu->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    return 0;
}END_OF_MAIN()

