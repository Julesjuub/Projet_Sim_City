#include "Biblio.h"

/*void InitialisationGenerale(t_jeu *Jeu)
{
    clock_t tDebut;
    srand(time(NULL));

    initialisationAllegro();

    printf(" \n Initialisation okk ");

    initialisation_struct_Jeu(Jeu);

    printf("\n pre creation matrice \n");

    Jeu->MAP = Creation_Matrice(); /// On crée la matrice contenant toutes les cases du jeu

    tDebut = clock ();
    Jeu->debut = tDebut;
    sauvegardePartie(Jeu);
}*/

void Jouer(t_jeu *Jeu)
{
    while (!key[KEY_ESC]) /// Faudra mettre une variable qui se met à 0 quand le jeu se finit
    {
        clear_bitmap(Jeu->utile->buffer);

        blit(Jeu->utile->fond, Jeu->utile->buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        quadrillage_MAP(Jeu);

        affichage_icones(Jeu);
        cycle_temps_sauvegarde(Jeu);

        selection_icone(Jeu); /// Contient tout le code pratiquement
        recherche_Niveau0(Jeu);

        if(Jeu->commuCapi == COMMU)
        {
            ameliorationBat(Jeu);
        }
        else if(Jeu->commuCapi == CAPITA)
        {
            ameliorationBatcapitaliste(Jeu);
        }


        rest(10);
        show_mouse(screen);
        textprintf_ex(Jeu->utile->buffer, Jeu->font1, 180, SCREEN_H - 50, makecol(250,0,250), -1,"position x :%d",mouse_x);
        textprintf_ex(Jeu->utile->buffer, Jeu->font1, 180, SCREEN_H - 40, makecol(250,0,250), -1,"position y :%d",mouse_y);

        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }
}

/*void ModeCommuniste(t_jeu *Jeu)
{



}*/


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
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
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
            if(Jeu->MAP[y][x].ptniv0->type == 0 || Jeu->MAP[y][x].ptniv0->type == Chatodo2 || Jeu->MAP[y][x].ptniv0->type == Centrale2 || Jeu->MAP[y][x].ptniv0->type == Habitation2)
            {
                rect(Jeu->utile->buffer, Jeu->MAP[y][x].coord_x, Jeu->MAP[y][x].coord_y, Jeu->MAP[y][x].coord_x + TX, Jeu->MAP[y][x].coord_y + TY, makecol(0, 0, 0));
            }
        }
    }

    //printf("\n Quadrillage okk \n");
}

void affichage_icones(t_jeu *Jeu)
{
    /// On affiche les icônes
    draw_sprite(Jeu->utile->buffer, Jeu->utile->cadre, WIDTH, -8);
    draw_sprite(Jeu->utile->buffer, Jeu->utile->banderole, 913, 20);
    draw_sprite(Jeu->utile->buffer, Jeu->utile->cadre_info, 5, 710);

    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->cabane->icone_mini, Jeu->MAP[15][15].coord_x, Jeu->MAP[15][15].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->maison->icone_mini, Jeu->MAP[20][20].coord_x, Jeu->MAP[20][20].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->immeuble->icone_mini, Jeu->MAP[15][15].coord_x, Jeu->MAP[20][20].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->gratte_ciel->icone_mini, Jeu->MAP[15][15].coord_x, Jeu->MAP[25][25].coord_y);
    draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_habitat->sol_vague->icone_mini, Jeu->MAP[11][11].coord_x, Jeu->MAP[11][11].coord_y);



    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_sol_vague->icone,Jeu->pt_icone->icone_sol_vague->coord_x,Jeu->pt_icone->icone_sol_vague->coord_y);
    //textprintf_ex(Jeu->utile->buffer, Jeu->font1, SCREEN_W -110, 70+120, makecol(20,20,20), -1,"Coût : 10",NULL);

    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_route->icone,Jeu->pt_icone->icone_route->coord_x,Jeu->pt_icone->icone_route->coord_y);
    //textprintf_ex(Jeu->utile->buffer, Jeu->font1, SCREEN_W -110, 200+120, makecol(20,20,20), -1,"Coût : ?",NULL);

    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_chatodo->icone,Jeu->pt_icone->icone_chatodo->coord_x,Jeu->pt_icone->icone_chatodo->coord_y);
    //textprintf_ex(Jeu->utile->buffer, Jeu->font1, SCREEN_W -110, 350+120, makecol(20,20,20), -1,"Coût : ?",NULL);

    draw_sprite(Jeu->utile->buffer,Jeu->pt_icone->icone_centrale->icone,Jeu->pt_icone->icone_centrale->coord_x,Jeu->pt_icone->icone_centrale->coord_y);
    //textprintf_ex(Jeu->utile->buffer, Jeu->font1, SCREEN_W -110, 480+120, makecol(20,20,20), -1,"Coût : ?",NULL);
}

void initialisation_struct_Jeu(t_jeu *Jeu)
{
    Jeu->utile = (t_utile*)malloc(sizeof(t_utile));

    Jeu->pt_icone = (t_icone*)malloc(sizeof(t_icone));
    Jeu->pt_icone->selection = 0;
    //allegro_message("rentre dans init");

    Jeu->pt_icone->icone_route = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_route->coord_x = 929;
    Jeu->pt_icone->icone_route->end_x = 1024;
    Jeu->pt_icone->icone_route->coord_y = 130;
    Jeu->pt_icone->icone_route->end_y = 219;
    Jeu->pt_icone->icone_route->type = Route;
    //allegro_message("init route okk");

    Jeu->pt_icone->icone_sol_vague = (t_sprite*)malloc(sizeof(t_sprite));
    //allegro_message("allocation ok");
    Jeu->pt_icone->icone_sol_vague->coord_x = 925;
    Jeu->pt_icone->icone_sol_vague->end_x = 965;
    Jeu->pt_icone->icone_sol_vague->coord_y = 245;
    Jeu->pt_icone->icone_sol_vague->end_y = 324;
    Jeu->pt_icone->icone_sol_vague->type = Construction_habitation;
    //allegro_message("init sol vague okk");

    Jeu->pt_icone->icone_chatodo = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_chatodo->coord_x = 914;
    Jeu->pt_icone->icone_chatodo->end_x = 1014;
    Jeu->pt_icone->icone_chatodo->coord_y = 355;
    Jeu->pt_icone->icone_chatodo->end_y = 496;
    Jeu->pt_icone->icone_chatodo->type = Chatodo;
    //allegro_message("init chatodo okk");

    Jeu->pt_icone->icone_centrale = (t_sprite*)malloc(sizeof(t_sprite));
    Jeu->pt_icone->icone_centrale->coord_x = 914;
    Jeu->pt_icone->icone_centrale->end_x = 1014;
    Jeu->pt_icone->icone_centrale->coord_y = 510;
    Jeu->pt_icone->icone_centrale->end_y = 633;
    Jeu->pt_icone->icone_centrale->type = Centrale;
    allegro_message("init centrale okk");



    Jeu->ptniv0 = (t_niv0*)malloc(sizeof(t_niv0));

    Jeu->ptniv0->route_mini = (t_sprite_mini*)malloc(sizeof (t_sprite_mini));

    Jeu->ptniv0->pt_bat = (t_batiment*)malloc(sizeof(t_batiment));
    Jeu->ptniv0->pt_bat->chato = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));
    Jeu->ptniv0->pt_bat->centrale = (t_sprite_mini*)malloc(sizeof(t_sprite_mini));

    Jeu->ptniv0->pt_bat->chato->icone_mini = load_bitmap("Bitmap/mini/chatodo_mini.bmp", NULL);
    Jeu->ptniv0->pt_bat->centrale->icone_mini = load_bitmap("Bitmap/mini/centrale_elec_mini.bmp", NULL);

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
    Jeu->utile->banderole = load_bitmap("Bitmap/icones/toolbox.bmp", NULL);
    Jeu->utile->cadre = load_bitmap("Bitmap/cadre.bmp", NULL);
    Jeu->utile->fond = load_bitmap("Bitmap/fond2.bmp", NULL);
    Jeu->utile->cadre_info = load_bitmap("Bitmap/icones/reserves.bmp", NULL);

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

    Jeu->font1=load_font("Bitmap/copper.pcx", NULL, NULL);


}

void selection_icone(t_jeu *Jeu) /// En fonction de la où on clique, le sous prog de placement d'icônes se lance avec l'icone selectionné
{
    recherche_Niveau0(Jeu);
    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_sol_vague->coord_x) && (mouse_x <= Jeu->pt_icone->icone_sol_vague->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_sol_vague->coord_y) && (mouse_y <= Jeu->pt_icone->icone_sol_vague->end_y)))
    {
        //allegro_message("maison");
        printf("\nVous avez seléctionné l'élément 'sol vague' \n");
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_sol_vague, Jeu->ptniv0->pt_habitat->sol_vague);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_route->coord_x) && (mouse_x <= Jeu->pt_icone->icone_route->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_route->coord_y) && (mouse_y <= Jeu->pt_icone->icone_route->end_y)))
    {
        //allegro_message("route");
        printf("\nVous avez seléctionné l'élément 'route' \n");
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_route, Jeu->ptniv0->route_mini);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_chatodo->coord_x) && (mouse_x <= Jeu->pt_icone->icone_chatodo->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_chatodo->coord_y) && (mouse_y <= Jeu->pt_icone->icone_chatodo->end_y)))
    {
        //allegro_message("chaotodo");
        printf("\nVous avez seléctionné l'élément 'chatodo' \n");
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_chatodo, Jeu->ptniv0->pt_bat->chato);
    }

    if((mouse_b&1) && ((mouse_x >= Jeu->pt_icone->icone_centrale->coord_x) && (mouse_x <= Jeu->pt_icone->icone_centrale->end_x )) && ((mouse_y >= Jeu->pt_icone->icone_centrale->coord_y) && (mouse_y <= Jeu->pt_icone->icone_centrale->end_y)))
    {
        //allegro_message("centrale");
        printf("\nVous avez seléctionné l'élément 'centrale' \n");
        blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        sub_placement_icone(Jeu, Jeu->pt_icone->icone_centrale, Jeu->ptniv0->pt_bat->centrale);
    }
}

void sub_placement_icone(t_jeu *Jeu, t_sprite *sprite, t_sprite_mini *sprite_mini)
{
    int valeur = 0;
    int x, y, n, m, valeurHabi, valeurBat;

    /**
            -> Sélectionner l'icône de son choix
            -> Message au joueur disant quelle icône il a selectionné
            -> Afficher les cases disponible où l'icône peut être placée
            -> Calculer la case choisie par les coordonnées du clique divisé par la taille de la case
            -> Marquer la case comme occupé et par quel type d'infrastucture
            -> Poosibilité d'annuler le choix avant de placer
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


            if(sprite->type == Route) //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            {
                if(Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type == 0)
                {
                    rect(Jeu->utile->buffer, x, y, x + TX, y + TY, makecol(0, 250, 0) );
                    blit(Jeu->utile->buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

                    if(mouse_b&1) /// Si le joueur clique sur une case qui est libre
                    {
                        if(Jeu->argent >10)
                        {
                            Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type = sprite->type; /// Le type de la case prend le type du sprit posé sur la case
                            Jeu->argent = Jeu->argent - 10;
                        }
                        else
                        {
                            printf("pas assez d'argent");
                        }
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
                        if(Jeu->argent > 1000)
                        {
                            for(n=0; n<3; n++)
                            {
                                for(m=0; m<3; m++)
                                {
                                    if(Jeu->case_select_y + m < MAPTY && Jeu->case_select_x + n < MAPTX)
                                    {
                                        if(Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type == 0)
                                        {
                                            Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type = Habitation2;
                                            Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->pt_habitat->type = 1;
                                        }
                                    }
                                }
                            }
                            Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type = sprite->type;
                            Jeu->argent = Jeu->argent - 1000;
                            Jeu->debut = clock ();
                            Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->pt_habitat->debut = Jeu->debut;
                        }
                        else
                        {
                            printf("pas assez d'argent");
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
                        if(Jeu->argent > 100000)
                        {
                            for(n=0; n<4; n++)
                            {
                                for(m=0; m<6; m++)
                                {
                                    if(Jeu->case_select_y + m < MAPTY && Jeu->case_select_x + n < MAPTX)
                                    {
                                        if(Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type == 0)
                                        {
                                            if(sprite->type == Chatodo)
                                            {
                                                Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type = Chatodo2;
                                            }
                                            else if(sprite->type == Centrale)
                                            {
                                                Jeu->MAP[Jeu->case_select_y + m][Jeu->case_select_x + n].ptniv0->type = Centrale2;
                                            }
                                        }
                                    }
                                }
                            }
                            Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->type = sprite->type;
                            if(sprite->type == Chatodo)
                            {
                                Jeu->nbChatodo = Jeu->nbChatodo + 1;
                                Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->pt_bat->marque = Jeu->nbChatodo;
                            }
                            if(sprite->type == Centrale)
                            {
                                Jeu->nbCentrale = Jeu->nbCentrale + 1;
                                Jeu->MAP[Jeu->case_select_y][Jeu->case_select_x].ptniv0->pt_bat->marque = Jeu->nbCentrale;
                            }

                            Jeu->argent = Jeu->argent - 100000;
                        }
                        else
                        {
                            printf("pas assez");

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
            recherche_Niveau0(Jeu);
        }
    }
}



void recherche_Niveau0(t_jeu *Jeu)
{
    int x, y;


    textprintf_ex(Jeu->utile->buffer, Jeu->font1, 99, 725, makecol(0, 0, 0), -1, "%d", Jeu->argent);
    textprintf_ex(Jeu->utile->buffer, Jeu->font1, 360, 725, makecol(0, 0, 0), -1, "%d", ((Jeu->nbCentrale)*5000));
    textprintf_ex(Jeu->utile->buffer, Jeu->font1, 535, 725, makecol(0, 0, 0), -1, "%d", ((Jeu->nbChatodo)*5000));


    for(y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == 0)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->utile->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
            }
            if(Jeu->MAP[y][x].ptniv0->type == Route)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->route_mini->icone_mini, x*TX, y*TY);
            }
            if(Jeu->MAP[y][x].ptniv0->type == Centrale2 || Jeu->MAP[y][x].ptniv0->type == Chatodo2 || Jeu->MAP[y][x].ptniv0->type == Habitation2)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->utile->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
            }


        }
    }
    quadrillage_MAP(Jeu);

    for(y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->utile->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
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

            else if(Jeu->MAP[y][x].ptniv0->type == Chatodo)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->utile->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_bat->chato->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);


            }
            else if(Jeu->MAP[y][x].ptniv0->type == Centrale)
            {
                draw_sprite(Jeu->utile->buffer, Jeu->utile->sol,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);
                draw_sprite(Jeu->utile->buffer, Jeu->ptniv0->pt_bat->centrale->icone_mini,Jeu->MAP[y][x].coord_x,Jeu->MAP[y][x].coord_y);

            }
        }
    }
}

void gagnerArgent(t_jeu *Jeu)
{
    int capacite, total = 0;
    for(int y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                capacite = chercheCapa2(Jeu, y, x);
                total = total + capacite*10;
            }
        }
    }
    printf("Vous avez gagnez %d", total);
    Jeu->argent = Jeu->argent + total;
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
        gagnerArgent(Jeu);
        progbfs(Jeu);
        sauvegardePartie(Jeu);
        lireGraphe(Jeu);
    }

    rest(10);
    textprintf_ex(Jeu->utile->buffer, Jeu->font1, 687, 720, makecol(0, 0, 0), -1, "%d", min);
    textprintf_ex(Jeu->utile->buffer, Jeu->font1, 735, 720, makecol(0, 0, 0), -1, "%d", sec);

}


void sauvegardePartie(t_jeu *Jeu)
{
    FILE *fichier=NULL;
    int i,j;
    fichier = fopen("fichier.txt","w");
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
                    if(Jeu->MAP[i][j].ptniv0->type == Construction_habitation)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_habitat->type);
                    }
                    if(Jeu->MAP[i][j].ptniv0->type == Chatodo)
                    {
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fprintf(fichier,"%d\n", Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                    if(Jeu->MAP[i][j].ptniv0->type == Centrale)
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

void ameliorationBat(t_jeu *Jeu)
{
    clock_t tActuel;
    int temps, min = 0, sec = 0, capaci, capaci2;

    tActuel = clock ();

    for(int y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                temps = (int)(tActuel-Jeu->MAP[y][x].ptniv0->pt_habitat->debut)/CLOCKS_PER_SEC;

                min = temps/60;
                sec = temps - 60*min;
                capaci = chercheCapa(Jeu, y, x);
                capaci2 = chercheCapa2(Jeu, y, x);

                if(sec%15 == 0 && temps!= 0)
                {
                    printf("test");

                    if(Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau >= capaci && Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec >= capaci)
                    {
                        if(Jeu->MAP[y][x].ptniv0->pt_habitat->type < 5)
                        {
                            printf("amelioration batiment");
                            Jeu->MAP[y][x].ptniv0->pt_habitat->type ++;
                            printf("\n%d, %d", Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau, Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec);
                        }
                    }
                    else if(Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau >= capaci2 && Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec >= capaci2)
                    {
                        if(Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau < capaci && Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec < capaci)
                        {
                            printf("\nbatiment stagne");
                        }
                    }
                    else
                    {
                        if(Jeu->MAP[y][x].ptniv0->pt_habitat->type > 1)
                        {
                            printf("regression batiment");
                            Jeu->MAP[y][x].ptniv0->pt_habitat->type --;
                            rest(1000);
                        }
                    }
                }
            }
        }
    }
}

void ameliorationBatcapitaliste(t_jeu *Jeu)
{
    clock_t tActuel;
    int temps, min = 0, sec = 0, capaci, capaci2;

    tActuel = clock ();

    for(int y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(int x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                temps = (int)(tActuel-Jeu->MAP[y][x].ptniv0->pt_habitat->debut)/CLOCKS_PER_SEC;

                min = temps/60;
                sec = temps - 60*min;
                capaci = chercheCapa(Jeu, y, x);
                capaci2 = chercheCapa2(Jeu, y, x);

                if(sec%15 == 0 && temps!= 0)
                {
                    rest(1000);
                    if(Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau > 1 && Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec > 1)
                    {
                        if(Jeu->MAP[y][x].ptniv0->pt_habitat->type < 5)
                        {
                            printf("amelioration batiment");
                            Jeu->MAP[y][x].ptniv0->pt_habitat->type ++;
                        }
                    }
                }
            }
        }
    }
}

int  chercheCapa(t_jeu *Jeu, int coordY, int coordX)
{
    int capa;
    if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 1)
    {
        capa = 10;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 2)
    {
        capa = 50;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 3)
    {
        capa = 100;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 4)
    {
        capa = 1000;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 5)
    {
        capa = 1000;
    }
    return capa;

}

int  chercheCapa2(t_jeu *Jeu, int coordY, int coordX)
{
    int capa;
    if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 1)
    {
        capa = 0;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 2)
    {
        capa = 10;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 3)
    {
        capa = 50;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 4)
    {
        capa = 100;
    }
    else if(Jeu->MAP[coordY][coordX].ptniv0->pt_habitat->type == 5)
    {
        capa = 1000;
    }
    return capa;

}


void changerBfs(t_jeu *Jeu, int coordY, int coordX, int capaci, int y, int x, int type)
{
    printf("\nchanger bfs");
    if(type == Chatodo)
    {
        if(Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot + capaci < 5000 && Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau == 0)
        {
            Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot = Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot + capaci;
            Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau = capaci;
            Jeu->MAP[y][x].ptniv0->pt_habitat->origineEau = Jeu->MAP[coordY][coordX].ptniv0->pt_bat->marque;
            printf("\n %d, %d,     eau %d\n", y, x, Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau);
        }
        else if(Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau < capaci && Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot < 5000)
        {

            Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau = Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau + 5000 - Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot;
            Jeu->MAP[y][x].ptniv0->pt_habitat->origineEau = Jeu->MAP[coordY][coordX].ptniv0->pt_bat->marque;
            Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot = Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot + Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau;

        }
    }
    else if(type == Centrale)
    {
        if(Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot + capaci < 5000 && Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec == 0)
        {
            Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot = Jeu->MAP[coordY][coordX].ptniv0->pt_bat->flot + capaci;
            Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec = capaci;
            Jeu->MAP[y][x].ptniv0->pt_habitat->origineElec = Jeu->MAP[coordY][coordX].ptniv0->pt_bat->marque;
            printf("\n %d, %d,     elec %d\n", y, x, Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec);

        }
    }
}

void bfs(t_jeu *Jeu, int s0, int** adj, int type, int coordY, int coordX)
{
    int *dejaVu = calloc(MAXI, sizeof(int));
    int *queue = calloc(MAXI, sizeof(int));


    int debut = -1, fin = -1, i;
    int x, y, capaci;
    for ( i = 0 ; i < MAXI ; i++)
    {
        dejaVu[i] = 0;
        queue[i] = 0;
    }

    debut++;
    queue[++fin] = s0;
    dejaVu[s0] = 1;

    while(debut <= fin)
    {
        s0 = queue[debut++];

        for ( i = 0 ; i < MAXI ; i++)
        {
            if (adj[s0][i] == 1 && dejaVu[i] != 1)
            {
                x = i%45;
                y = i - x;
                y = y/45;

                if(Jeu->MAP[y+1][x].ptniv0->type == Construction_habitation || Jeu->MAP[y+1][x].ptniv0->type == Habitation2)
                {
                    if(Jeu->MAP[y+1][x].ptniv0->type == Construction_habitation)////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y+1, x);
                        changerBfs(Jeu, coordY, coordX, capaci, y+1, x, type);

                    }
                    else if(Jeu->MAP[y+1][x-1].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y+1, x-1);
                        changerBfs(Jeu, coordY, coordX, capaci, y+1, x-1, type);

                    }
                    else if(Jeu->MAP[y+1][x-2].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y+1, x-2);
                        changerBfs(Jeu, coordY, coordX, capaci, y+1, x-2, type);
                    }
                }
                if(Jeu->MAP[y-1][x].ptniv0->type == Construction_habitation || Jeu->MAP[y-1][x].ptniv0->type == Habitation2)
                {
                    if(Jeu->MAP[y-3][x].ptniv0->type == Construction_habitation)////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-3, x);
                        changerBfs(Jeu, coordY, coordX, capaci, y-3, x, type);

                    }
                    else if(Jeu->MAP[y-3][x-1].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-3, x-1);

                        changerBfs(Jeu, coordY, coordX, capaci, y-3, x-1, type);

                    }
                    else if(Jeu->MAP[y-3][x-2].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-3, x-2);

                        changerBfs(Jeu, coordY, coordX, capaci, y-3, x-2, type);
                    }

                }
                if(Jeu->MAP[y][x+1].ptniv0->type == Construction_habitation || Jeu->MAP[y][x+1].ptniv0->type == Habitation2)
                {
                    if(Jeu->MAP[y][x+1].ptniv0->type == Construction_habitation)////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y, x+1);
                        changerBfs(Jeu, coordY, coordX, capaci, y, x+1, type);

                    }
                    else if(Jeu->MAP[y-1][x+1].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-1, x+1);

                        changerBfs(Jeu, coordY, coordX, capaci, y-1, x+1, type);

                    }
                    else if(Jeu->MAP[y-2][x+1].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-2, x+1);

                        changerBfs(Jeu, coordY, coordX, capaci, y-2, x+1, type);
                    }



                }
                if(Jeu->MAP[y][x-1].ptniv0->type == Construction_habitation || Jeu->MAP[y][x-1].ptniv0->type == Habitation2)
                {
                    if(Jeu->MAP[y][x-3].ptniv0->type == Construction_habitation)////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y, x-3);
                        changerBfs(Jeu, coordY, coordX, capaci, y, x-3, type);

                    }
                    else if(Jeu->MAP[y-1][x-3].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-1, x-3);

                        changerBfs(Jeu, coordY, coordX, capaci, y-1, x-3, type);

                    }
                    else if(Jeu->MAP[y-2][x-3].ptniv0->type == Construction_habitation)/////////////////////////////////////////////////////////////////////////////////
                    {
                        capaci = chercheCapa(Jeu, y-2, x-3);

                        changerBfs(Jeu, coordY, coordX, capaci, y-2, x-3, type);
                    }
                }


                queue[++fin] = i;
                dejaVu[i] = 1;
            }
        }
    }
}


void progbfs(t_jeu *Jeu)
{
    int** matrice = (int**)calloc(MAXI, sizeof(int*));

    for(int i = 0; i < MAXI; i++)
    {
        matrice[i] = (int*)calloc(MAXI, sizeof(int));
    }

    int x, y, i, j, y2;

    for(i = 0; i < MAXI; i++)
    {
        for(j=0; j < MAXI; j++)
        {
            matrice[i][j] = 0;
        }
    }
    for(y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Route)
            {
                if(y > 0 && x > 0)
                {
                    y2 = 45*y;
                    if(Jeu->MAP[y+1][x].ptniv0->type == Route)
                    {
                        matrice[y2+x][(y2+45)+x] = 1;
                    }
                    if(Jeu->MAP[y-1][x].ptniv0->type == Route)
                    {
                        matrice[y2+x][(y2-45)+x] = 1;
                    }
                    if(Jeu->MAP[y][x+1].ptniv0->type == Route)
                    {
                        matrice[y2+x][(x+1)+y2] = 1;
                    }
                    if(Jeu->MAP[y][x-1].ptniv0->type == Route)
                    {
                        matrice[y2+x][(x-1)+y2] = 1;
                    }
                }
            }
            if(Jeu->MAP[y][x].ptniv0->type == Construction_habitation)
            {
                Jeu->MAP[y][x].ptniv0->pt_habitat->origineEau = 0;
                Jeu->MAP[y][x].ptniv0->pt_habitat->origineElec = 0;
                Jeu->MAP[y][x].ptniv0->pt_habitat->flotEau = 0;
                Jeu->MAP[y][x].ptniv0->pt_habitat->flotElec = 0;
            }
        }
    }
    for(y = 0; y < MAPTY; y++) /// jusqu'a 35
    {
        for(x = 0; x < MAPTX; x++)  /// jusqu'a 45
        {
            if(Jeu->MAP[y][x].ptniv0->type == Chatodo || Jeu->MAP[y][x].ptniv0->type == Centrale)
            {
                Jeu->MAP[y][x].ptniv0->pt_bat->flot = 0;
                y2 = 45*y;
                //*//////////////////////////////////////////////////////////////////////////////////////////////////////////*//
                if(y > 0 && x > 0)
                {
                    if(Jeu->MAP[y-1][x].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2-45)+x, matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y-1][x+1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2-45)+(x+1), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y-1][x+2].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2-45)+(x+2), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y-1][x+3].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2-45)+(x+3), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    //*//////////////////////////////////////////////////////////////////////////////////////////////////////////*//
                    if(Jeu->MAP[y+6][x].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2+6*45)+x, matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+6][x+1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2+6*45)+(x+1), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+6][x+2].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2+6*45)+(x+2), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+6][x+3].ptniv0->type == Route)
                    {
                        bfs(Jeu, (y2+6*45)+(x+3), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    //*//////////////////////////////////////////////////////////////////////////////////////////////////////////*//
                    if(Jeu->MAP[y][x-1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x-1)+y2, matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+1][x-1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x-1)+(y2+1*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+2][x-1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x-1)+(y2+2*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+3][x-1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x-1)+(y2+3*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+4][x-1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x-1)+(y2+4*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+5][x-1].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x-1)+(y2+5*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    //*//////////////////////////////////////////////////////////////////////////////////////////////////////////*//
                    if(Jeu->MAP[y][x+4].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x+4)+y2, matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+1][x+4].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x+4)+(y2+1*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+2][x+4].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x+4)+(y2+2*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+3][x+4].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x+4)+(y2+3*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+4][x+4].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x+4)+(y2+4*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                    if(Jeu->MAP[y+5][x+4].ptniv0->type == Route)
                    {
                        bfs(Jeu, (x+4)+(y2+5*45), matrice, Jeu->MAP[y][x].ptniv0->type, y, x);
                    }
                }
            }
        }
    }

    for(int i = 0; i < MAXI; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}


void lireGraphe(t_jeu *Jeu)
{
    FILE *fichier=NULL;
    int i,j;
    fichier = fopen("fichier.txt","r");
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

        for(i=0; i<MAPTY; i++)
        {
            for(j=0; j<MAPTX; j++)
            {
                fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->type);

                if(Jeu->MAP[i][j].ptniv0->type != 0)
                {
                    fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->type);
                    if(Jeu->MAP[i][j].ptniv0->type == Route)
                    {
                        /*
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv1->origine->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv1->flot);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv2->origine->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv2->flot);*/
                    }
                    if(Jeu->MAP[i][j].ptniv0->type == Construction_habitation)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_habitat->type);
                    }
                    if(Jeu->MAP[i][j].ptniv0->type == Chatodo)
                    {
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->marque);
                        fscanf(fichier,"%d\n", &Jeu->MAP[i][j].ptniv0->pt_bat->flot);
                    }
                    if(Jeu->MAP[i][j].ptniv0->type == Centrale)
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


void MenuJeu(t_jeu* Jeu)
{

    //initialisation des bitmaps

    BITMAP *debut = load_bitmap("Bitmap/debut.bmp",NULL);
    BITMAP *nvpart = load_bitmap("Bitmap/nouvellepartie.bmp",NULL);
    BITMAP *regles = load_bitmap("Bitmap/regles.bmp",NULL);
    int fin = 0, retour = 0;
    MIDI *musique=NULL;

    //affichage de l'image
    musique = load_midi("Bitmap/musique.mid");
    if (musique==NULL)
    {
        printf("Probleme Musique de fond !");
    }
    if(debut == NULL || nvpart == NULL || regles == NULL)
    {
        allegro_message("probleme chargement image menu");
    }

    play_midi(musique,10);
    set_volume(200,100);


    show_mouse(screen);

    while(!key[KEY_ESC])
    {

        rectfill(Jeu->utile->buffer, 0, 0, 1024, 768, makecol(0,0,0));
        blit(debut,Jeu->utile->buffer,0,0,0, 0,1024, 768);//affiche l'image sur le buffer
        // textprintf_ex(buffer, Jeu->font1, 200, 300, makecol(0, 255, 0),makecol(0,0,255), "Coordonnées de la souris en ligne : %4d et en colonne :%4d", mouse_x, mouse_y);

        blit(Jeu->utile->buffer, screen, 0,0,0,0,1024,768);//affiche le buffer sur l'écran
        while(fin == 0)
        {
            textprintf_ex(Jeu->utile->buffer, Jeu->font1, 200, 300, makecol(0, 255, 0),makecol(0,0,255), "Coordonnées de la souris en ligne : %4d et en colonne :%4d", mouse_x, mouse_y);

            blit(Jeu->utile->buffer, screen, 0,0,0,0,1024,768);//affiche le buffer sur l'écran

            if (mouse_b&1 && mouse_x>599 && mouse_x<988 && mouse_y>320 && mouse_y<412 && retour==0 ) //coordonée du rectangle nouvelle partie
            {
                /// Mode communiste/capitaliste
                printf("nouvelle partie\n");

                clear_bitmap(Jeu->utile->buffer);
                blit(nvpart,Jeu->utile->buffer,0,0,0, 0,SCREEN_W, SCREEN_H);//affiche l'image sur le buffer
                blit(Jeu->utile->buffer, screen, 0,0,0,0,1024,768);//affiche le buffer sur l'écran



                printf("souris %4d\n", mouse_b);
                retour=1; ///Possibilité de retourner en arrière



                //qd je clique sur les coordeonnees de capitaliste c les mm que jeu
            }
            if (mouse_b&1 && mouse_x>0&& mouse_x<329&& mouse_y>203 && mouse_y<285) //coordonée du rectangle capitaliste
            {
                printf("\n Mode Capitaliste");
                Jeu->commuCapi = CAPITA;
                Jouer(Jeu);
            }
            /*if(mouse_b & 1 && mouse_x>721 && mouse_x<1022&& mouse_y>535 && mouse_y<646) //coordonée du rectangle communiste
            {
                printf("\n Mode Communiste");
                Jeu->commuCapi = COMMU;
                Jouer(Jeu);
            }*/


            if ( mouse_b&1 && mouse_x>25 && mouse_x<261 && mouse_y>671 && mouse_y<730 && retour==1 )//coordonée du bouton retour
            {
                printf("retour1\n");
                //retour au menu

                rectfill(Jeu->utile->buffer, 0, 0, 1024, 768, makecol(0,0,0));



                blit(debut,Jeu->utile->buffer,0,0,0, 0,1024, 768);//affiche l'image sur le buffer
                blit(Jeu->utile->buffer, screen, 0,0,0,0,1024,768);//affiche le buffer sur l'écran
                retour=0;

            }
            if (mouse_b & 1 && mouse_x>612 && mouse_x<972&& mouse_y>448 && mouse_y<541 &&retour!=1)//coordonée du rectangle reprendre partie
            {

                //lancer la sauvegarde
                printf("reprendre partie\n");
                clear_bitmap(Jeu->utile->buffer);
                retour=0;
            }

            if (mouse_b & 1 && mouse_x>598 && mouse_x<987&& mouse_y>576 && mouse_y<668 &&retour!=1)//coordonée du rectangle regles du jeu
            {

                printf("regles\n");
                blit(regles,Jeu->utile->buffer,0,0,0, 0,1024, 768);//affiche l'image sur le buffer
                blit(Jeu->utile->buffer, screen, 0,0,0,0,1024,768);//affiche le buffer sur l'écran
                retour=1;
            }
            if ( mouse_b & 1 && mouse_x>27 && mouse_x<263&& mouse_y>671 && mouse_y<726 &&retour==1 )//coordonée du bouton retour
            {
                printf("retour1\n");

                rectfill(Jeu->utile->buffer, 0, 0, 1024, 768, makecol(0,0,0));



                blit(debut,Jeu->utile->buffer,0,0,0, 0,1024, 768);//affiche l'image sur le buffer
                blit(Jeu->utile->buffer, screen, 0,0,0,0,1024,768);//affiche le buffer sur l'écran
                retour=0;

            }
        }
    }

    play_midi(NULL,FALSE);
    destroy_midi(musique);

}


/*void BoucleJeu()
{
     On appelle le menu du Jeu
     --> Qui lui appellera le sous prog capitaliste ou communiste
    */

