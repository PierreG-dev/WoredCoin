#include "process.h"
//#include "blockchain.h"


int main(int argc, char **argv) {

  int commande[] = {0, 0, 0, 0};

  int nbBlock = 0;
  int difficulty = 0;
  int cheatBlock = 0;
  int cheatTransaction = 0;

  for (int parcours_Argc = 0; parcours_Argc < (argc - 1); parcours_Argc++) {

    if (strcmp(argv[parcours_Argc], "-b") == 0) {
      commande[0] = 1;
      if (sscanf(argv[parcours_Argc + 1], "%d", &nbBlock) != 1) {
          printf("Veuillez saisir un nombre pour -b\n");
          return 0;
      }
      if(nbBlock < 1){
        printf("Veuillez saisir un nombre de block superieur\n");
        return 0;
      }
    }
    if ( strcmp(argv[parcours_Argc], "-d") == 0) {
      commande[1] = 1;
      if (sscanf(argv[parcours_Argc + 1], "%d", &difficulty) != 1) {
          printf("Erreur arguments\n");
          return 0;
      }
      if(difficulty < 1){
        printf("Erreur arguments\n");
        return 0;
      }
    }
    if (strcmp(argv[parcours_Argc], "-cb") == 0) {
      commande[2] = 1;
      if (sscanf(argv[parcours_Argc + 1], "%d", &cheatBlock) != 1) {
          printf("Erreur arguments\n");
          return 0;
      }
    }
    if ( strcmp(argv[parcours_Argc], "-ct") == 0) {
      commande[3] = 1;
      if (sscanf(argv[parcours_Argc + 1], "%d", &cheatTransaction) != 1) {
          printf("Erreur arguments\n");
          return 0;
      }
    }
  }

  if(commande[0] == 1 && commande[1] == 1 && commande[2] == 0 && commande[3] == 0){
    //génération blockchain
    BlockChain* blockChain = genBlockChain(difficulty, nbBlock);
    return 0;
  }

  else if(commande[0] == 1 && commande[1] == 1 && commande[2] == 1 && commande[3] == 0){
    //génération blockchain + cheat + controle
    cheatTransaction = -1;
    BlockChain* blockChain = genBlockChain(difficulty, nbBlock);
    if(hackBlockChain(blockChain, cheatBlock, -2) == 0){
      return 0;
    }
    printBlockChain(blockChain);
    return 0;
  }

  else if(commande[0] == 1 && commande[1] == 1 && commande[2] == 1 && commande[3] == 1){
    //génération blockchain + suppression transaction + controle
    BlockChain* blockChain = genBlockChain(difficulty, nbBlock);
    if(hackBlockChain(blockChain, cheatBlock, cheatTransaction) == 0){
      return 0;
    }
    printBlockChain(blockChain);
    return 0;
  }
  else{
    printf("Erreur d'arguments\n");
    return 0;
  }
  return 0;
}
