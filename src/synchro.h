#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "ensitheora.h"
#include <stdbool.h>

extern bool fini;
extern pthread_mutex_t mutex_taille;
extern pthread_mutex_t mutex_texture;
extern pthread_mutex_t mutex_texture_prod;
extern pthread_mutex_t mutex_texture_cons;
extern pthread_cond_t cond_taille;
extern pthread_cond_t cond_texture;
extern pthread_cond_t cond_depot;
extern pthread_cond_t cond_conso;
/* Les extern des variables pour la synchro ici */

/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
