#include "transaction.h"


void genTransaction(Block* block){

  srand((unsigned int) clock()); //Initialisé le random

  int nb_Transaction = (rand()%(MAX_TRANSACTION) + 1); //Nombre de transaction max
  char** tab_Transaction = malloc(nb_Transaction * sizeof(char*));

  for(int i = 0; i < nb_Transaction; ++i){
    //Malloc + ajout transaction.
    tab_Transaction[i] = malloc((TRANSACTION_SIZE + 1) * sizeof(char));
    sprintf(tab_Transaction[i], "%s%d", "Source-Destination: ", rand()%MAX_VALUE_RAND);
  }
  setNbTransactionBlock(block, nb_Transaction);
  setListTransactionBlock(block, tab_Transaction);
}
