#ifndef CONFIG_H
#define CONFIG_H

//Constante du programme
// ATTENTION : toujours vérifier que les varibles Nonce/MAX_VALUE_RAND et nombre de block ne dépasse pas en nombre de caractère, sinon ajuster les varibles caract en conséquence
#define MAX_BLOCK 4 //nb de caract du Nombre
#define MAX_TRANSACTION_CHAR 3 //nb de caract du Nombre de Transaction
#define MAX_NONCE_CHAR 10 //Nb caract max de la nonce
#define TRANSACTION_SIZE 30 // Taille de la chaine de caractère d'une transaction
#define TIMESTAMP_SIZE 25 //nb de caract du timeStamp

#define MAX_TRANSACTION 100 //nb max de transaction
#define HASH_SIZE 64 //Taille du hash
#define MAX_NONCE 9999999 //Nonce max
#define MAX_VALUE_RAND 1000000 //Max nombre random pour simuler transaction

 #endif
