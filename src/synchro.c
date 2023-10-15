#include "ensitheora.h"
#include "synchro.h"
#include "pthread.h"

pthread_mutex_t mutex_taille;
pthread_mutex_t mutex_texture;
pthread_mutex_t mutex_texture_prod;
pthread_mutex_t mutex_texture_cons;
pthread_cond_t cond_taille;
pthread_cond_t cond_texture;
pthread_cond_t cond_depot;
pthread_cond_t cond_conso;
/* les variables pour la synchro, ici */
int window;
int texture;
int empty = NBTEX;
/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
    pthread_mutex_lock(&mutex_taille);
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
    window = 1;
    pthread_cond_signal(&cond_taille);
    pthread_mutex_unlock(&mutex_taille);
}

void attendreTailleFenetre() {
    pthread_mutex_lock(&mutex_taille);
    while(window == 0){
        pthread_cond_wait(&cond_taille, &mutex_taille);
    }
    window = 0;
    pthread_mutex_unlock(&mutex_taille);
}

void signalerFenetreEtTexturePrete() {
    pthread_mutex_lock(&mutex_texture);
    texture = 1;
    pthread_cond_signal(&cond_texture);
    pthread_mutex_unlock(&mutex_texture);
}

void attendreFenetreTexture() {
    pthread_mutex_lock(&mutex_texture);
    while(texture == 0){
        pthread_cond_wait(&cond_texture, &mutex_texture);
    }
    texture = 0;
    pthread_mutex_unlock(&mutex_texture);
}

void debutConsommerTexture() {
    pthread_mutex_lock(&mutex_texture_cons);
    while(empty == NBTEX){
        pthread_cond_wait(&cond_conso, &mutex_texture_cons);
    }
    pthread_mutex_unlock(&mutex_texture_cons);
}

void finConsommerTexture() {
    pthread_mutex_lock(&mutex_texture_cons);
    empty++;
    pthread_cond_signal(&cond_depot);
    pthread_mutex_unlock(&mutex_texture_cons);
}

void debutDeposerTexture() {
    pthread_mutex_lock(&mutex_texture_prod);
    while(empty == 0){
        pthread_cond_wait(&cond_depot, &mutex_texture_prod);
    }
    pthread_mutex_unlock(&mutex_texture_prod);
}

void finDeposerTexture() {
    pthread_mutex_lock(&mutex_texture_prod);
    empty--;
    pthread_cond_signal(&cond_conso);
    pthread_mutex_unlock(&mutex_texture_prod);
}
