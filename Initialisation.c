#include "Biblio.h"

void initialisationAllegro()
{
    /// 255, 216, 185
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

t_case** Creation_Matrice()
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

            /// Initialisation et allocation NIVEAU 0
            MAP[y][x].ptniv0 = (t_niv0*)malloc(sizeof(t_niv0));
            MAP[y][x].ptniv0->type = 0;
            MAP[y][x].ptniv0->route_mini = (t_sprite_mini*)malloc(sizeof (t_sprite_mini));
            MAP[y][x].ptniv0->route_mini->coord_x = 0;
            MAP[y][x].ptniv0->route_mini->coord_y = 0;

            /// Initialisation et allocation Structure habitation
            MAP[y][x].ptniv0->pt_habitat = (t_habitation*)malloc(sizeof(t_habitation));
            MAP[y][x].ptniv0->pt_habitat->sol_vague = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_habitat->sol_vague->coord_x = 0;
            MAP[y][x].ptniv0->pt_habitat->sol_vague->coord_y = 0;

            MAP[y][x].ptniv0->pt_habitat->cabane = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_habitat->cabane->coord_x = 0;
            MAP[y][x].ptniv0->pt_habitat->cabane->coord_y = 0;

            MAP[y][x].ptniv0->pt_habitat->maison = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_habitat->maison->coord_x = 0;
            MAP[y][x].ptniv0->pt_habitat->maison->coord_y = 0;

            MAP[y][x].ptniv0->pt_habitat->immeuble = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_habitat->immeuble->coord_x = 0;
            MAP[y][x].ptniv0->pt_habitat->immeuble->coord_y = 0;

            MAP[y][x].ptniv0->pt_habitat->gratte_ciel = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_habitat->gratte_ciel->coord_x = 0;
            MAP[y][x].ptniv0->pt_habitat->gratte_ciel->coord_y = 0;

            MAP[y][x].ptniv0->pt_habitat->capa_cabane = 0;
            MAP[y][x].ptniv0->pt_habitat->capa_maison = 0;
            MAP[y][x].ptniv0->pt_habitat->capa_immeuble = 0;
            MAP[y][x].ptniv0->pt_habitat->capa_gratte_ciel = 0;


            /// Initialisation et allocation Struct Bâtiment
            MAP[y][x].ptniv0->pt_bat = (t_batiment*)malloc(sizeof(t_batiment));
            MAP[y][x].ptniv0->pt_bat->capa_tot = 0;
            MAP[y][x].ptniv0->pt_bat->flot = 0;
            MAP[y][x].ptniv0->pt_bat->marque = 0;

            MAP[y][x].ptniv0->pt_bat->chato = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_bat->chato->coord_x = 0;
            MAP[y][x].ptniv0->pt_bat->chato->coord_y = 0;

            MAP[y][x].ptniv0->pt_bat->centrale = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv0->pt_bat->centrale->coord_x = 0;
            MAP[y][x].ptniv0->pt_bat->centrale->coord_y = 0;



            /// Initialisation et allocation NIVEAU -1
            MAP[y][x].ptniv1 = (t_niv1*)malloc(sizeof(t_niv1));
            MAP[y][x].ptniv1->flot = 0;
            MAP[y][x].ptniv1->canalisation_mini = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

            /// Initialisation et allocation Batiment d'origine
            MAP[y][x].ptniv1->origine = (t_batiment*)malloc(sizeof(t_batiment));
            MAP[y][x].ptniv1->origine->chato = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv1->origine->chato->coord_x = 0;
            MAP[y][x].ptniv1->origine->chato->coord_y = 0;

            MAP[y][x].ptniv1->origine->capa_tot = 0;
            MAP[y][x].ptniv1->origine->flot = 0;
            MAP[y][x].ptniv1->origine->marque = 0;


            /// Initialisation et allocation NIVEAU -2
            MAP[y][x].ptniv2 = (t_niv2*)malloc(sizeof(t_niv2));
            MAP[y][x].ptniv2->flot = 0;
            MAP[y][x].ptniv2->elec_mini = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

            /// Initialisation et allocation Batiment d'origine
            MAP[y][x].ptniv2->origine = (t_batiment*)malloc(sizeof(t_batiment));
            MAP[y][x].ptniv2->origine->centrale = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
            MAP[y][x].ptniv2->origine->centrale->coord_x = 0;
            MAP[y][x].ptniv2->origine->centrale->coord_y = 0;

            MAP[y][x].ptniv2->origine->capa_tot = 0;
            MAP[y][x].ptniv2->origine->flot = 0;
            MAP[y][x].ptniv2->origine->marque = 0;



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
            blit(Jeu->utile->sol, Jeu->utile->buffer, 0, 0, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, TX, TY);
        }
    }
    for(int x = 0; x < MAPTX; x++) /// jusqu'a 38
    {
        for(int y = 0; y < MAPTY; y++)  /// jusqu'a 51
        {
            blit(Jeu->utile->sol, Jeu->utile->buffer, 0, 0, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, TX, TY);
        }
    }


    for(int y = 0; y < MAPTY; y++) /// jusqu'a 38
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 51
        {
            rect(Jeu->utile->buffer, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, Jeu->MAP[y][x].coord_x+TX, Jeu->MAP[y][x].coord_y+TY, makecol(0, 0, 0));
            //circlefill(buffer, MAP[y][x].coord_x,MAP[y][x].coord_y, 2, makecol(255, 0, 0));

        }
    }

    //printf("\n Quadrillage okk \n");
}

void affichage_icones(t_jeu *Jeu)
{
    /// On affiche les icônes
    draw_sprite(Jeu->utile->buffer, Jeu->utile->cadre, WIDTH, -8);
    draw_sprite(Jeu->utile->buffer, Jeu->utile->banderole, 910, 24);
    draw_sprite(Jeu->utile->buffer, Jeu->utile->cadre_info, 5, 710);

    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->cabane->icone_mini, Jeu->MAP[15][15].coord_x, Jeu->MAP[15][15].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->maison->icone_mini, Jeu->MAP[20][20].coord_x, Jeu->MAP[20][20].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->immeuble->icone_mini, Jeu->MAP[15][15].coord_x, Jeu->MAP[20][20].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->gratte_ciel->icone_mini, Jeu->MAP[15][15].coord_x, Jeu->MAP[25][25].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->sol_vague->icone_mini, Jeu->MAP[11][11].coord_x, Jeu->MAP[11][11].coord_y);






    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_sol_vague->icone,Jeu->pt_icone->icone_sol_vague->coord_x+20,Jeu->pt_icone->icone_sol_vague->coord_y);
    //textprintf_ex(Jeu->utile->buffer, font, SCREEN_W -110, 70+120, makecol(20,20,20), -1,"Coût : 10",NULL);

    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_route->icone,Jeu->pt_icone->icone_route->coord_x+20,Jeu->pt_icone->icone_route->coord_y+120);
    //textprintf_ex(Jeu->utile->buffer, font, SCREEN_W -110, 200+120, makecol(20,20,20), -1,"Coût : ?",NULL);

    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_chatodo->icone,Jeu->pt_icone->icone_chatodo->coord_x+20,Jeu->pt_icone->icone_chatodo->coord_y+120);
    //textprintf_ex(Jeu->utile->buffer, font, SCREEN_W -110, 350+120, makecol(20,20,20), -1,"Coût : ?",NULL);

    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_centrale->icone,Jeu->pt_icone->icone_centrale->coord_x+20,Jeu->pt_icone->icone_centrale->coord_y+120);
    //textprintf_ex(Jeu->utile->buffer, font, SCREEN_W -110, 480+120, makecol(20,20,20), -1,"Coût : ?",NULL);
}

void initialisation_struct_Jeu(t_jeu *Jeu)
{
    Jeu->utile = (t_utile*)malloc(sizeof(t_utile));
    
    Jeu->pt_icone = (t_icone*)malloc(sizeof(t_icone));
    Jeu->pt_icone->selection = 0;
    //allegro_message("rentre dans init");

    Jeu->pt_icone->icone_sol_vague = (t_sprite*)malloc(sizeof(t_sprite));
    //allegro_message("allocation ok");
    Jeu->pt_icone->icone_sol_vague->coord_x = SCREEN_W - 117;
    Jeu->pt_icone->icone_sol_vague->end_x = 997;
    Jeu->pt_icone->icone_sol_vague->coord_y = 110;
    Jeu->pt_icone->icone_sol_vague->end_y = 150;
    Jeu->pt_icone->icone_sol_vague->type = Construction_habitation;
    //allegro_message("init sol vague okk");

    Jeu->pt_icone->icone_route = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_route->coord_x = SCREEN_W - 115;
    Jeu->pt_icone->icone_route->end_x = 965;
    Jeu->pt_icone->icone_route->coord_y = 110;
    Jeu->pt_icone->icone_route->end_y = 190;
    Jeu->pt_icone->icone_route->type = Route;
    //allegro_message("init route okk");

    Jeu->pt_icone->icone_chatodo = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_chatodo->coord_x = SCREEN_W - 130;
    Jeu->pt_icone->icone_chatodo->end_x = 945;
    Jeu->pt_icone->icone_chatodo->coord_y = 235;
    Jeu->pt_icone->icone_chatodo->end_y = 330;
    Jeu->pt_icone->icone_chatodo->type = Chatodo;
    //allegro_message("init chatodo okk");

    Jeu->pt_icone->icone_centrale = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_centrale->coord_x = SCREEN_W - 130;
    Jeu->pt_icone->icone_centrale->end_x = 965;
    Jeu->pt_icone->icone_centrale->coord_y = 390;
    Jeu->pt_icone->icone_centrale->end_y = 466;
    Jeu->pt_icone->icone_centrale->type = Centrale;
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
    Jeu->ptniv0->pt_habitat->sol_vague->icone_mini = load_bitmap("Bitmap/mini/sol_vague_mini.bmp", NULL);
    Jeu->ptniv0->pt_habitat->cabane->icone_mini =  load_bitmap("Bitmap/mini/hut_mini.bmp", NULL);
    Jeu->ptniv0->pt_habitat->maison->icone_mini = load_bitmap("Bitmap/mini/house_mini_V2.bmp", NULL);
    Jeu->ptniv0->pt_habitat->immeuble->icone_mini = load_bitmap("Bitmap/mini/immeuble_mini.bmp", NULL);
    Jeu->ptniv0->pt_habitat->gratte_ciel->icone_mini = load_bitmap("Bitmap/mini/skycraper_mini.bmp", NULL);

    if(Jeu->ptniv0->pt_habitat->cabane->icone_mini == NULL )
    {
        allegro_message("Pas reussi a charger habtitation ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    Jeu->ptniv0->route_mini->icone_mini =  load_bitmap("Bitmap/mini/route_mini.bmp", NULL);


    Jeu->ptniv1 = (t_niv1*)malloc(sizeof(t_niv1));
    Jeu->ptniv1->origine = (t_batiment*)malloc(sizeof(t_batiment));
    Jeu->ptniv1->canalisation_mini = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));


    Jeu->ptniv2 = (t_niv2*)malloc(sizeof(t_niv2));
    Jeu->ptniv2->origine = (t_batiment*)malloc(sizeof(t_batiment));
    Jeu->ptniv2->elec_mini = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

    Jeu->utile->buffer = create_bitmap(SCREEN_W,SCREEN_H);
    Jeu->utile->sol = load_bitmap("Bitmap/Autres/sol.bmp", NULL); /// On charge le sol du jeu
    Jeu->utile->banderole = load_bitmap("Bitmap/Autres/banderole.bmp", NULL);
    Jeu->utile->cadre = load_bitmap("Bitmap/cadre.bmp", NULL);
    Jeu->utile->fond = load_bitmap("Bitmap/fond2.bmp", NULL);
    Jeu->utile->cadre_info = load_bitmap("Bitmap/reserves.bmp", NULL);

    Jeu->pt_icone->icone_sol_vague->icone = load_bitmap("Bitmap/icones/habitation_V2.bmp", NULL);
    Jeu->pt_icone->icone_route->icone =  load_bitmap("Bitmap/icones/road_V2.bmp", NULL);
    Jeu->pt_icone->icone_chatodo->icone = load_bitmap("Bitmap/icones/chatodeau.bmp", NULL);
    Jeu->pt_icone->icone_centrale->icone = load_bitmap("Bitmap/icones/centraleee.bmp", NULL);

    allegro_message("agisi");

    if(Jeu->utile->sol == NULL || Jeu->utile->cadre == NULL)
    {
        allegro_message("Pas reussi a charger utile ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if(Jeu->pt_icone->icone_sol_vague->icone == NULL)
    {
    allegro_message("Pas reussi a charger sol_vague ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }
    if(Jeu->ptniv0->pt_habitat->cabane == NULL ||  Jeu->pt_icone->icone_chatodo->icone == NULL)
    {
    allegro_message("Pas reussi a charger cabane ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }
    if(Jeu->pt_icone->icone_route->icone == NULL )
    {
    allegro_message("Pas reussi a charger route ");
    allegro_exit();
    exit(EXIT_FAILURE);
    }
    if(Jeu->pt_icone->icone_centrale->icone == NULL )
    {
    allegro_message("Pas reussi a charger centrale ");
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
        textprintf_ex(Jeu->utile->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'sol vague' ",NULL);
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_sol_vague, Jeu->ptniv0->pt_habitat->sol_vague);

    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_route->coord_x) && (mouse_x <= Jeu->pt_icone->icone_route->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_route->coord_y) && (mouse_y <= Jeu->pt_icone->icone_route->end_y)))
    {
        textprintf_ex(Jeu->utile->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'route' ",NULL);
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_route, Jeu->ptniv0->route_mini);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_chatodo->coord_x) && (mouse_x <= Jeu->pt_icone->icone_chatodo->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_chatodo->coord_y) && (mouse_y <= Jeu->pt_icone->icone_chatodo->end_y)))
    {
        textprintf_ex(Jeu->utile->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'chateau d'eau' ",NULL);
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_chatodo, Jeu->ptniv0->pt_bat->chato);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_centrale->coord_x) && (mouse_x <= Jeu->pt_icone->icone_centrale->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_centrale->coord_y) && (mouse_y <= Jeu->pt_icone->icone_centrale->end_y)))
    {
        textprintf_ex(Jeu->utile->buffer, font, 20, HEIGHT+20, makecol(250,0,250), -1,"Vous avez seléctionné l'élément 'centrale électrique' ",NULL);
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_centrale, Jeu->ptniv0->pt_bat->centrale);
    }
}

void sub_placement_icone(t_jeu *Jeu, t_sprite *sprite, t_sprite_mini *sprite_mini) {
    int valeur = 0;
    int x, y, n, m, valeurHabi, valeurBat;

    /**
            -> Sélectionner l'icône de son choix
            -> Message au joueur disant quelle icône il a selectionné
            -> Afficher les cases disponible où l'icône peut être placée
            -> Calculer la case choisie par les coordonnées du clique divisé par la taille de la case
            -> Marquer la case comme occupé et par quel type d'infrastucture
            -> Poosibiliré d'annuler le choix avant de placer
     **/

    /// Afficher les cases en parcourant MAP avec souris

    while(valeur == 0)
    {
        valeurHabi = 0;
        valeurBat = 0;

        if(mouse_x < TX*MAPTX && mouse_y < TY*MAPTY)
        {
            Jeu->case_select_x = (mouse_x)/TX; /// On récupère la case en X pendant que le joueur parcourt la MAP avec la souris
            Jeu->case_select_y = (mouse_y)/TY; /// On récupère la case en Y
            printf("\n Valeur case selectionne : [%d][%d]", Jeu->case_select_y, Jeu->case_select_x);

            x = Jeu->case_select_x*TX; /// On récupère la case en X pendant que le joueur parcourt la MAP avec la souris
            y = Jeu->case_select_y*TY;


            if(sprite->type == Route)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            {
                if(Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type == 0)
                {
                    rect(Jeu->utile->buffer, x, y, x + TX, y + TY, makecol(0, 250, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                    if(mouse_b&1) /// Si le joueur clique sur une case qui est libre
                    {
                        Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type = sprite->type; /// Le type de la case prend le type du sprit posé sur la case
                        Jeu->pt_icone->selection = 0;
                        valeur = 1;
                    }
                }
                else
                {
                    rect(Jeu->utile->buffer, x, y, x + TX, y + TY, makecol(250, 0, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }
            }

            else if(sprite->type == Construction_habitation)////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            {
                for(n=0; n<3; n++)
                {
                    for(m=0; m<3; m++)
                    {
                        if(Jeu->case_select_y + m < MAPTY && Jeu->case_select_x + n < MAPTX)
                        {
                            if(Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type == 0)
                            {
                                valeurHabi ++;
                            }
                        }
                    }
                }

                if(valeurHabi == 3*3)
                {

                    rect(Jeu->utile->buffer, x, y, x + TX*3, y + TY*3, makecol(0, 250, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                    if(mouse_b&1) /// Si le joueur clique sur une case qui est libre
                    {
                        for(n=0; n<3; n++)
                        {
                            for(m=0; m<3; m++)
                            {
                                if(Jeu->case_select_y + m < MAPTY && Jeu->case_select_x + n < MAPTX)
                                {
                                    if(Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type == 0)
                                    {
                                        Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type = sprite->type;
                                    }
                                }
                            }
                        }

                        Jeu->pt_icone->selection = 0;
                        valeur = 1;
                    }
                }
                else
                {
                    rect(Jeu->utile->buffer, x, y, x + TX*3, y + TY*3, makecol(250, 0, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }

            }

            else if(sprite->type == Chatodo || sprite->type == Centrale)/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            {
                for(n=0; n<4; n++)
                {
                    for(m=0; m<6; m++)
                    {
                        if(Jeu->case_select_y + m < MAPTY && Jeu->case_select_x + n < MAPTX)
                        {
                            if(Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type == 0)
                            {
                                valeurBat ++;
                            }
                        }
                    }
                }

                if(valeurBat == 4*6)
                {

                    rect(Jeu->utile->buffer, x, y, x + TX*4, y + TY*6, makecol(0, 250, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                    if(mouse_b&1) /// Si le joueur clique sur une case qui est libre
                    {
                        for(n=0; n<4; n++)
                        {
                            for(m=0; m<6; m++)
                            {
                                if(Jeu->case_select_y + m < MAPTY && Jeu->case_select_x + n < MAPTX)
                                {
                                    if(Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type == 0)
                                    {
                                        Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type = sprite->type;
                                    }
                                }
                            }
                        }

                        Jeu->pt_icone->selection = 0;
                        valeur = 1;
                    }
                }
                else
                {
                    rect(Jeu->utile->buffer, x, y, x + TX*4, y + TY*6, makecol(250, 0, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                }

            }


            clear_bitmap(Jeu->utile->buffer);
            quadrillage_MAP(Jeu);
            cycle_temps_sauvegarde(Jeu);
            affichage_icones(Jeu);

        }
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
                draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->route_mini->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
            }

            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 1)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->sol_vague->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 2)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->cabane->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 3)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->maison->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 4)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->immeuble->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

                if(Jeu->MAP[y][x].ptniv0->pt_habitat->type == 5)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->gratte_ciel->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }
            }

            if(Jeu->MAP[y][x].ptniv0->type == Chatodo)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_bat->chato->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }

            if(Jeu->MAP[y][x].ptniv0->type == Centrale)
                {
                    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_bat->centrale->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                }


            if(Jeu->MAP[y][x].ptniv0->type == Rien)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->utile->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
            }
        }
    }
}

void cycle_temps_sauvegarde(t_jeu *Jeu)
{
    clock_t tActuel;
    int temps, min = 0, sec = 0;

    tActuel = clock ();
    temps = (int)(tActuel-Jeu->debut)/CLOCKS_PER_SEC;

    min = temps/60;
    sec = temps - 60*min;

    if(sec%15 == 0 && temps!= 0)
    {
        rest(1000);
        Jeu->nbSecondes = Jeu->nbSecondes + 15;
        sauvegardePartie(Jeu);
        lireGraphe(Jeu);
    }

    rest(10);
    textprintf_ex(Jeu->utile->buffer, font, 687, 728, makecol(0, 0, 0), -1, "%d", min);
    textprintf_ex(Jeu->utile->buffer, font, 735, 728, makecol(0, 0, 0), -1, "%d", sec);

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
                        /*fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv1->origine->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv1->flot);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv2->origine->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv2->flot);*/
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Construction_habitation)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_habitat->type);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Chatodo)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Centrale)
                    {
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

        for(i=0; i < MAPTY; i++)
        {
            for(j=0; j < MAPTX; j++)
            {
                fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->type);

                if(Jeu->MAP[i][j].ptniv0->type != 0)
                {
                    fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->type);
                    if(Jeu->MAP[i][j].ptniv0->type == Route)
                    {
                        /*fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv1->origine->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv1->flot);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv2->origine->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv2->flot);*/
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Construction_habitation)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_habitat->type);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Chatodo)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                    else if(Jeu->MAP[i][j].ptniv0->type == Centrale)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                }
            }
        }

        fclose(fichier);
    }
}
