#include "Biblio.h"

void initialisationAllegro()
{

    int largeurBureau = 0, hauteurBureau = 0;
    allegro_init();
    install_keyboard();
    install_mouse();
    show_mouse(screen);
    get_desktop_resolution(&largeurBureau, &hauteurBureau);
    set_color_depth(desktop_color_depth());

    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0))!=0)
    {
        allegro_message("Probleme de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

t_case** Creation_Matrice ()
{
    t_case** MAP = (t_case**)calloc(MAPTX, sizeof(t_case*));

    for(int i = 0; i < MAPTX; i++)
    {
        MAP[i] = (t_case*)calloc(MAPTX, sizeof(t_case));
    }

    for(int y = 0; y < MAPTY; y++)
    {
        for(int x = 0; x < MAPTX; x++)
        {
            MAP[y][x].coord_x = 0;
            MAP[y][x].coord_y = 0;
            MAP[y][x].ptniv0 = (t_niv0*)malloc(sizeof(t_niv0));
            MAP[y][x].ptniv0->pt_bat = (t_batiment*)malloc(sizeof(t_batiment));
            MAP[y][x].ptniv0->pt_habitat = (t_habitation*)malloc(sizeof(t_habitation));
            MAP[y][x].ptniv0->type = 0;
            MAP[y][x].ptniv0->pt_bat->type = 0;
            MAP[y][x].ptniv0->pt_habitat->type = 0;
            MAP[y][x].ptniv1 = (t_niv1*)malloc(sizeof(t_niv1));
            MAP[y][x].ptniv2 = (t_niv2*)malloc(sizeof(t_niv2));
            //MAP[y][x].ptniv0->type = 0;

            printf("\n Valeur des coordonees MAP[%d][%d] : x -> %d  y -> %d ", y, x, MAP[y][x].coord_x, MAP[y][x].coord_y);
        }
    }


    for(int y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            //printf("\n boucle 1 okkk ");
            MAP[y][x].coord_x = x * TX;
            //MAP[y][x].type = 0;
        }
    }

    for(int x = 0; x < MAPTX; x++) /// jusqu'a 45
    {
        for(int y = 0; y < MAPTY; y++)  /// jusqu'a 35
        {
            MAP[y][x].coord_y = y * TY;
        }
    }


    for(int y = 0; y < MAPTY; y++)
    {
        for (int x = 0; x < MAPTX; x++)
        {
            printf("\n Valeur des coordonees MAP[%d][%d] : y -> %d  x -> %d ", y, x, MAP[y][x].coord_y, MAP[y][x].coord_x);
        }
    }
    printf("\n\n\n MATRICE INITIALISE \n\n\n");

    return MAP;


}

void quadrillage_MAP(t_jeu *Jeu)
{
    for(int y = 0; y < MAPTY; y++) /// jusqu'a 38
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 51
        {
            blit(Jeu->sol, Jeu->buffer, 0, 0, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, TX, TY);
        }
    }
    for(int x = 0; x < MAPTX; x++) /// jusqu'a 38
    {
        for(int y = 0; y < MAPTY; y++)  /// jusqu'a 51
        {
            blit(Jeu->sol, Jeu->buffer, 0, 0, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, TX, TY);
        }
    }


    for(int y = 0; y < MAPTY; y++) /// jusqu'a 38
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 51
        {
            rect(Jeu->buffer, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, Jeu->MAP[y][MAPTX-1].coord_x, Jeu->MAP[y][MAPTX-1].coord_y, makecol(105, 155, 105));
            //circlefill(buffer, MAP[y][x].coord_x,MAP[y][x].coord_y, 2, makecol(255, 0, 0));

        }
    }
    for(int x = 0; x < MAPTX; x++) /// jusqu'a 38
    {
        for(int y = 0; y < MAPTY; y++)  /// jusqu'a 51
        {
            rect(Jeu->buffer, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, Jeu->MAP[MAPTY-1][x].coord_x, Jeu->MAP[MAPTY-1][x].coord_y, makecol(255, 255, 255));

        }
    }

    //printf("\n Quadrillage okk \n");

}

void affichage_icones(t_jeu *Jeu)
{
    /// On affiche les icônes

    draw_sprite(Jeu->buffer,Jeu->pt_icone->icone_sol_vague->icone,Jeu->pt_icone->icone_sol_vague->coord_x,Jeu->pt_icone->icone_sol_vague->coord_y);
    textprintf_ex(Jeu->buffer, font, SCREEN_W -110, 70, makecol(250,200,250), -1,"Coût : 10",NULL);

    draw_sprite(Jeu->buffer,Jeu->pt_icone->icone_route->icone,Jeu->pt_icone->icone_route->coord_x,Jeu->pt_icone->icone_route->coord_y);
    textprintf_ex(Jeu->buffer, font, SCREEN_W -110, 200, makecol(250,200,250), -1,"Coût : ?",NULL);

    /*draw_sprite(Jeu->buffer,Jeu->pt_icone->icone_canalisation->icone,Jeu->pt_icone->icone_canalisation->coord_x,Jeu->pt_icone->icone_canalisation->coord_y);
    textprintf_ex(Jeu->buffer, font, SCREEN_W -110, 330, makecol(250,200,250), -1,"Coût : ?",NULL);

    draw_sprite(Jeu->buffer,Jeu->pt_icone->icone_elec->icone,Jeu->pt_icone->icone_elec->coord_x,Jeu->pt_icone->icone_elec->coord_y);
    textprintf_ex(Jeu->buffer, font, SCREEN_W -110, 460, makecol(250,200,250), -1,"Coût : ?",NULL);*/


    draw_sprite(Jeu->buffer,Jeu->pt_icone->icone_chatodo->icone,Jeu->pt_icone->icone_chatodo->coord_x,Jeu->pt_icone->icone_chatodo->coord_y);
    textprintf_ex(Jeu->buffer, font, SCREEN_W -110, 590, makecol(250,200,250), -1,"Coût : ?",NULL);

    draw_sprite(Jeu->buffer,Jeu->pt_icone->icone_centrale->icone,Jeu->pt_icone->icone_centrale->coord_x,Jeu->pt_icone->icone_centrale->coord_y);
    textprintf_ex(Jeu->buffer, font, SCREEN_W -110, 700, makecol(250,200,250), -1,"Coût : ?",NULL);
}

void initialisation_struct_Jeu(t_jeu *Jeu)
{
    Jeu->pt_icone = (t_icone*)malloc(sizeof(t_icone));
    Jeu->pt_icone->selection = 0;
    //allegro_message("rentre dans init");

    Jeu->pt_icone->icone_sol_vague = (t_sprite*)malloc(sizeof(t_sprite));
    //allegro_message("allocation ok");
    Jeu->pt_icone->icone_sol_vague->coord_x = SCREEN_W - 110;
    Jeu->pt_icone->icone_sol_vague->end_x = 965;
    Jeu->pt_icone->icone_sol_vague->coord_y = 10;
    Jeu->pt_icone->icone_sol_vague->end_y = 60;
    allegro_message("init sol vague okk");

    Jeu->pt_icone->icone_route = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_route->coord_x = SCREEN_W - 110;
    //Jeu->pt_icone->icone_route->end_x = Jeu->pt_icone->icone_route->coord_x + Jeu->pt_icone->icone_route->icone->h;
    Jeu->pt_icone->icone_route->coord_y = 110;
    //Jeu->pt_icone->icone_route->end_y = Jeu->pt_icone->icone_route->coord_y + Jeu->pt_icone->icone_route->icone->h;
    //allegro_message("init route okk");

    /*Jeu->pt_icone->icone_canalisation = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_canalisation->coord_x = SCREEN_W - 110;
    //Jeu->pt_icone->icone_canalisation->end_x = Jeu->pt_icone->icone_canalisation->coord_x + Jeu->pt_icone->icone_canalisation->icone->h;
    Jeu->pt_icone->icone_canalisation->coord_y = 240;
    //Jeu->pt_icone->icone_canalisation->end_y = Jeu->pt_icone->icone_canalisation->coord_y + Jeu->pt_icone->icone_canalisation->icone->h;
    //allegro_message("init canalisation okk");


    Jeu->pt_icone->icone_elec = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_elec->coord_x = SCREEN_W - 110;
    //Jeu->pt_icone->icone_elec->end_x = Jeu->pt_icone->icone_elec->coord_x + Jeu->pt_icone->icone_elec->icone->h;
    Jeu->pt_icone->icone_elec->coord_y = 370;
    //Jeu->pt_icone->icone_elec->end_y = Jeu->pt_icone->icone_elec->coord_y + Jeu->pt_icone->icone_elec->icone->h;
    //allegro_message("init elec okk");*/

    Jeu->pt_icone->icone_chatodo = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_chatodo->coord_x = SCREEN_W - 110;
    //Jeu->pt_icone->icone_chatodo->end_x = Jeu->pt_icone->icone_chatodo->coord_x + Jeu->pt_icone->icone_chatodo->icone->h;
    Jeu->pt_icone->icone_chatodo->coord_y = 490;
    //Jeu->pt_icone->icone_chatodo->end_y = Jeu->pt_icone->icone_chatodo->coord_y + Jeu->pt_icone->icone_chatodo->icone->h;
    //allegro_message("init chatodo okk");

    Jeu->pt_icone->icone_centrale = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_centrale->coord_x = SCREEN_W - 110;
    //Jeu->pt_icone->icone_centrale->end_x = Jeu->pt_icone->icone_centrale->coord_x + Jeu->pt_icone->icone_centrale->icone->h;
    Jeu->pt_icone->icone_centrale->coord_y = 610;
    //Jeu->pt_icone->icone_centrale->end_y = Jeu->pt_icone->icone_centrale->coord_y + Jeu->pt_icone->icone_centrale->icone->h;
    allegro_message("init centrale okk");




    Jeu->ptniv0 = (t_niv0*)malloc(sizeof(t_niv0));

    Jeu->ptniv0->route_mini = (t_sprite_mini*)malloc(sizeof (t_sprite_mini));

    Jeu->ptniv0->pt_bat = (t_batiment*)malloc(sizeof(t_batiment));
    Jeu->ptniv0->pt_bat->chato = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_bat->centrale = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

    Jeu->ptniv0->pt_habitat = (t_habitation*)malloc(sizeof(t_habitation));
    Jeu->ptniv0->pt_habitat->type = 0;
    Jeu->ptniv0->pt_habitat->sol_vague = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_habitat->cabane = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_habitat->maison = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_habitat->immeuble = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_habitat->gratte_ciel = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_habitat->sol_vague->icone_mini = load_bitmap("Bitmap/mini/terrain_vague_unite.bmp", NULL);
    Jeu->ptniv0->pt_habitat->cabane->icone_mini =  load_bitmap("Bitmap/mini/hut_mini.bmp", NULL);
    Jeu->ptniv0->pt_habitat->maison->icone_mini = load_bitmap("Bitmap/mini/house_red_mini.bmp", NULL);
    Jeu->ptniv0->pt_habitat->immeuble->icone_mini = load_bitmap("Bitmap/mini/office_building_mini.bmp", NULL);

    Jeu->ptniv0->route_mini->icone_mini =  load_bitmap("Bitmap/mini/route_mini.bmp", NULL);


    Jeu->ptniv1 = (t_niv1*)malloc(sizeof(t_niv1));
    Jeu->ptniv1->origine = (t_batiment*)malloc(sizeof(t_batiment));
    Jeu->ptniv1->canalisation_mini = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

    Jeu->ptniv2 = (t_niv2*)malloc(sizeof(t_niv2));
    Jeu->ptniv2->origine = (t_batiment*)malloc(sizeof(t_batiment));
    Jeu->ptniv2->elec_mini = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

    Jeu->buffer = create_bitmap(SCREEN_W,SCREEN_H);
    Jeu->sol = load_bitmap("Bitmap/sol.bmp", NULL); /// On charge le sol du jeu



    Jeu->pt_icone->icone_sol_vague->icone = load_bitmap("Bitmap/icones/terrain_vague_unite_icone.bmp", NULL);
    Jeu->pt_icone->icone_route->icone =  load_bitmap("Bitmap/icones/route_icone.bmp", NULL);
    //Jeu->pt_icone->icone_canalisation->icone = load_bitmap("Bitmap/icones/water_pipe_icone.bmp", NULL);
    //Jeu->pt_icone->icone_elec->icone = load_bitmap("Bitmap/icones/electric_cable_icone.bmp", NULL);
    Jeu->pt_icone->icone_chatodo->icone = load_bitmap("Bitmap/icones/chatodo_icone.bmp", NULL);
    Jeu->pt_icone->icone_centrale->icone = load_bitmap("Bitmap/icones/centrale_elec_icone.bmp", NULL);



    if(Jeu->ptniv0->pt_habitat->sol_vague == NULL || Jeu->pt_icone->icone_sol_vague == NULL || Jeu->sol == NULL)
    {
    allegro_message("Pas reussi a charger sol_vague ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }
    if(Jeu->ptniv0->pt_habitat->cabane == NULL )
    {
    allegro_message("Pas reussi a charger cabane ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }
    if(Jeu->pt_icone->icone_route== NULL )
    {
    allegro_message("Pas reussi a charger maison ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }
    if(Jeu->ptniv0->pt_habitat->immeuble == NULL )
    {
    allegro_message("Pas reussi a charger immeuble ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }

    Jeu->nbSecondes = 0;
    Jeu->nbHabitantsTotal = 0;
    Jeu->argent = 500000;
    Jeu->nbChatodo = 0;
    Jeu->nbCentrale = 0;


}

void selection_icone(t_jeu *Jeu) /// En fonction de la où on clique, le sous prog de placement d'icônes se lance avec l'icone selectionné
{
    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_sol_vague->coord_x) && (mouse_x <= Jeu->pt_icone->icone_sol_vague->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_sol_vague->coord_y) && (mouse_y <= Jeu->pt_icone->icone_sol_vague->end_y)))
    {
        textprintf_ex(Jeu->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'sol vague' ",NULL);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_sol_vague, Jeu->ptniv0->pt_habitat->sol_vague);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_route->coord_x) && (mouse_x <= Jeu->pt_icone->icone_route->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_route->coord_y) && (mouse_y <= Jeu->pt_icone->icone_route->end_y)))
    {
        textprintf_ex(Jeu->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'route' ",NULL);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_route, Jeu->ptniv0->route_mini);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_chatodo->coord_x) && (mouse_x <= Jeu->pt_icone->icone_chatodo->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_chatodo->coord_y) && (mouse_y <= Jeu->pt_icone->icone_chatodo->end_y)))
    {
        textprintf_ex(Jeu->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'chateau d'eau' ",NULL);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_chatodo, Jeu->ptniv0->pt_bat->chato);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_centrale->coord_x) && (mouse_x <= Jeu->pt_icone->icone_centrale->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_centrale->coord_y) && (mouse_y <= Jeu->pt_icone->icone_centrale->end_y)))
    {
        textprintf_ex(Jeu->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'centrale électrique' ",NULL);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_centrale, Jeu->ptniv0->pt_bat->centrale);
    }
}

void sub_placement_icone(t_jeu *Jeu, t_sprite *sprite, t_sprite_mini *sprite_mini)
{
    int valeur = 0;

    for(int y = 0; y < MAPTY; y++) /// jusqu'a 38
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 51
        {
            if(Jeu->MAP[y][x].ptniv0->type == 0)/// Si la case est libre
            {
                circlefill(Jeu->buffer, Jeu->MAP[y][x].coord_x+TX/2,Jeu->MAP[y][x].coord_y+TY/2, 2, makecol(0, 255, 0));
            }
        }
    }

    /**
            -> Sélectionner l'icône de son choix
            -> Message au joueur disant quelle icône il a selectionné
            -> Afficher les cases disponible où l'icône peut être placée
            -> Calculer la case choisie par les coordonnées du clique divisé par la taille de la case
            -> Marquer la case comme occupé et par quel type d'infrastucture
            -> Poosibiliré d'annuler le choix avant de placer
     **/

    /// Afficher les cases en parcourant MAP avec souris
    do{
        Jeu->case_select_x = (mouse_x)%TX; /// On récupère la case en X pendant que le joueur parcourt la MAP avec la souris
        Jeu->case_select_y = (mouse_y)%TY; /// On récupère la case en Y
        printf("\n Valeur case selectionne : [%d][%d]", Jeu->case_select_y, Jeu->case_select_x);

        if((mouse_b&1) && Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type == 0) /// Si le joueur clique sur une case qui est libre
            valeur = 1;
    }while(valeur == 0);

    if(valeur == 1) /// Si la case est libre et que le joueur a cliqué dessus alors on affiche l'icone selectionnée sur la case en question
    {
        Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type = sprite->type; /// Le type de la case prend le type du sprit posé sur la case
        valeur = 0;
        Jeu->pt_icone->selection = 0;
    }

}



void recherche_Niveau0(t_jeu *Jeu)
{
    for(int x = 0; x < MAPTX; x++) /// jusqu'a 35
    {
        for(int y = 0; y < MAPTY; y++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Route)
            {
                draw_sprite(Jeu->buffer, Jeu->ptniv0->route,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
            }

            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 1)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_habitat->sol_vague->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 2)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_habitat->cabane->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 3)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_habitat->maison->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 4)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_habitat->immeuble->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 5)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_habitat->gratte_ciel->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }
            }

            if(Jeu->MAP[y][x].ptniv0->type == Batiment)
            {
                if(Jeu->MAP[y][x].ptniv0->pt_bat->type == 1)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_bat->chato->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_bat->type == 2)
                {
                    draw_sprite(Jeu->buffer, Jeu->ptniv0->pt_bat->centrale->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }
            }

            if(Jeu->MAP[y][x].ptniv0->type == Rien)
            {
                draw_sprite(Jeu->buffer, Jeu->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
            }
        }
    }
}

void cycle_temps_sauvegarde(t_jeu *Jeu, clock_t tDebut)
{
    clock_t tActuel;
    int temps, min = 0, sec = 0;

    rest(10);
    textprintf_ex(Jeu->buffer, font, SCREEN_W - 380, SCREEN_H - 50, makecol(250, 0, 250), -1, "Minutes :%d", min);
    textprintf_ex(Jeu->buffer, font, SCREEN_W - 380, SCREEN_H - 40, makecol(250, 0, 250), -1, "Secondes :%d", sec);

    tActuel = clock ();
    temps = (int)(tActuel-tDebut)/CLOCKS_PER_SEC;

    sec = temps - 60*min;
    if(temps%60 == 0 && temps!= 0)
    {
        sec = 0;
        min = min + 1;
    }

    if(temps%15 == 0 && temps!= 0)
    {
        rest(1000);
        Jeu->nbSecondes = Jeu->nbSecondes + 15;
        sauvegardePartie(Jeu);
        ///lireGraphe(Jeu);
    }
}

void sauvegardePartie(t_jeu *Jeu)
{
    FILE *fichier=NULL;
    int i,j;
    fichier = fopen("fichierTexte.txt","w");
    if (fichier==NULL)
    {
        printf ("erreur d'ouverture de fichier\n");
    }
    else
    {
        fprintf(fichier,"%d\n", Jeu->nbSecondes);
        fprintf(fichier,"%d\n", Jeu->nbHabitantsTotal);
        fprintf(fichier,"%d\n", Jeu->argent);
        fprintf(fichier,"%d\n", Jeu->nbChatodo);
        fprintf(fichier,"%d\n\n", Jeu->nbCentrale);

        for(i=0; i < MAPTY; i++)
        {
            for(j=0; j < MAPTX; j++)
            {
                fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->type);

                if(Jeu->MAP[i][j].ptniv0->type != 0)
                {
                    fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->type);
                    if(Jeu->MAP[i][j].ptniv0->type == Route)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv1->origine->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv1->flot);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv2->origine->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv2->flot);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Construction_habitation)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_habitat->type);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Batiment)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->type);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                }
            }
        }
        printf("%d", Jeu->nbSecondes);
        fclose(fichier);
    }
}


void lireGraphe(t_jeu *Jeu)
{
    FILE *fichier=NULL;
    int i,j;
    fichier = fopen("fichierTexte.txt","r");
    if (fichier==NULL)
    {
        printf ("erreur d'ouverture de fichier\n");
    }
    else
    {
        fscanf(fichier,"%d\n", &Jeu->nbSecondes);
        fscanf(fichier,"%d\n", &Jeu->nbHabitantsTotal);
        fscanf(fichier,"%d\n", &Jeu->argent);
        fscanf(fichier,"%d\n", &Jeu->nbChatodo);
        fscanf(fichier,"%d\n\n", &Jeu->nbCentrale);

        for(i=0; i<45; i++)
        {
            for(j=0; j<35; j++)
            {
                fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->type);

                if(Jeu->MAP[i][j].ptniv0->type != 0)
                {
                    fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->type);
                    if(Jeu->MAP[i][j].ptniv0->type == 1100)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv1->origine->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv1->flot);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv2->origine->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv2->flot);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == 1101)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_habitat->type);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == 1102)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->type);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                }
            }
        }

        fclose(fichier);
    }
}