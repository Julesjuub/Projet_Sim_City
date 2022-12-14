//
// Created by jules on 31/10/2022.
//

#ifndef PROJET_S1_BIBLIO_H
#define PROJET_S1_BIBLIO_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

#define Route 1100 /// 1 case
#define Construction_habitation 1101 /// 3x3 cases
#define Chatodo 1102 /// 4x6 cases
#define Centrale 1103
#define Rien 1104

/// 1024 x 768
#define WIDTH 900 /// taille de la MAP en pixels en largeur
#define HEIGHT 700  /// taille de la MAP en pixels en longueur

#define TX 20 /// taille en pixel d'une case
#define TY 20
#define MAPTX 45 /// Nombre de cases en largeur
#define MAPTY 35

typedef struct sprite_mini
{
    BITMAP *icone_mini;
    int coord_x;
    int coord_y;
}t_sprite_mini;

typedef struct sprite
{
    BITMAP *icone;
    int coord_x;
    int end_x;
    int coord_y;
    int end_y;

    int type;
}t_sprite;

typedef struct icone
{
    t_sprite *icone_sol_vague;
    t_sprite *icone_route;

    t_sprite *icone_chatodo;
    t_sprite *icone_centrale;

    int selection;
}t_icone;

typedef struct batiment
{
    //int type; /// Quel type de bâtiment est-ce

    t_sprite_mini *chato; /// (Centrales et châteaux)
    t_sprite_mini *centrale;

    /// Regroupe caractéristiques centrales élec et châteaux d'eau
    int capa_tot;
    int flot;
    int marque; /// Pour différencier les batiments de meme types

}t_batiment;

typedef struct habitation
{
    int type; /// Quel type d'habitation est-ce

    t_sprite_mini *sol_vague;
    t_sprite_mini *cabane;
    t_sprite_mini *maison;
    t_sprite_mini *immeuble;
    t_sprite_mini *gratte_ciel;

    /// Nombre d'habitants possible
    int capa_cabane;
    int capa_maison;
    int capa_immeuble;
    int capa_gratte_ciel;

}t_habitation;



/// NIVEAUX ///


typedef struct Niveau0 /// On récupère les infos dans un fichier texte (les données de notre map)
{
    BITMAP *route;
    t_sprite_mini *route_mini;

    t_habitation *pt_habitat; /// BITMAP comprises dans les structures
    t_batiment *pt_bat;

    int type; /// Si la case en question est une route, une construction_habitation ou un bâtiment

}t_niv0;


typedef struct Niveau1 /// EAU
{
    t_batiment *origine; /// De quel château d'eau la canalisation vient
    int flot; /// Nombre de personne alimenté

    t_sprite_mini *canalisation_mini;

}t_niv1;

typedef struct Niveau2 /// ELECTRICITE
{
    t_batiment *origine;
    int flot; /// Nombre de personne alimenté

    t_sprite_mini *elec_mini;
}t_niv2;

typedef struct Case
{
    t_niv0 *ptniv0;
    t_niv1 *ptniv1;
    t_niv2 *ptniv2;

    int coord_x;
    int coord_y;



}t_case;

typedef struct Utiles
{
    BITMAP *buffer;
    BITMAP *sol;
    BITMAP *banderole;
    BITMAP *cadre;
    BITMAP *fond;
    BITMAP *cadre_info;

}t_utile;

typedef struct Jeu
{
    t_case **MAP;
    t_utile *utile;

    t_niv0 *ptniv0;
    t_niv1 *ptniv1;
    t_niv2 *ptniv2;

    t_icone *pt_icone;

    int nbSecondes;
    int nbHabitantsTotal;
    int argent;
    int nbChatodo;
    int nbCentrale;

    int case_select_x;
    int case_select_y;
    clock_t debut;

}t_jeu;

void initialisationAllegro();
t_case** Creation_Matrice ();
void quadrillage_MAP(t_jeu *Jeu);
void affichage_icones(t_jeu *Jeu);
void initialisation_struct_Jeu(t_jeu *Jeu);
void sub_placement_icone(t_jeu *Jeu, t_sprite *sprite, t_sprite_mini *sprite_mini);
void selection_icone(t_jeu *Jeu);
void sauvegardePartie(t_jeu *Jeu);
void lireGraphe(t_jeu *Jeu);
void cycle_temps_sauvegarde(t_jeu *Jeu);

void recherche_Niveau0(t_jeu *Jeu);





#endif //PROJET_S1_BIBLIO_H
