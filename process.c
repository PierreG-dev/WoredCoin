#include "process.h"

void createBlock(BlockChain* temp){
  addBlock(temp, GenBlock(getLastBlock(temp)));
  genTransaction(getLastBlock(temp));
  miningBlock(getLastBlock(temp), getDifficulty(temp));
}

void printBlock(Block* blockTemp){
  printf("### BLOCK -> %d ### NB TRANSACTION -> %d\n### HASH PREV -> %s \n### HASH MERKLE ROOT -> %s\n### HASH CURRENT -> %s\n\n", getIndexBlock(blockTemp), getNbTransationBlock(blockTemp), getHashPrevious(blockTemp), getHashMerkleRoot(blockTemp), getHashCurrent(blockTemp));
}

void printBlockChain(BlockChain* blockChain){
  printf("### AFFICHAGE BLOCKCHAIN ### NOMBRE DE BLOCK %d ###\n", getNbBlock(blockChain));
  for(int i = 0; i< getNbBlock(blockChain); ++i){
    Block* temp = getBlockInChain(blockChain, i);
    printBlock(temp);
  }
  printf("### FIN AFFICHAGE BLOCKCHAIN ###\n\n");
}

bool verifBlockChain(BlockChain* blockChain){
  printf("\n### VERIFICATION DE LA COHERENCE DE LA BLOCKCHAIN ###\n\n");
  if(chainIsValid(blockChain) == true){
    printf("\n### LA BLOCKCHAIN EST COHERENTE ###\n\n");
    return true;
  }
  else{
    printf("\n### LA BLOCKCHAIN N'EST PAS COHERENTE ###\n\n");
    return false;
  }
}

bool verifHashRoot(BlockChain* blockChain){
  printf("### VERIFICATION DES HASHMERKLE DES BLOCS DE LA BLOCKCHAIN ###\n");
  if(merkleIsValid(blockChain) == true){
    printf("### LES HASHMERKLE DES BLOCS SONT VALIDES ###\n\n");
    return true;
  }
  else{
    printf("### LES HASHMERKLE DES BLOCS NE SONT PAS VALIDES ###\n\n");
    return false;
  }
}

int hackBlockChain(BlockChain* blockChain, int i, int transaction){
  printf("### CHEATER OF BLOCKCHAIN ###\n\n");
  if(transaction > 0){
    if(i < getNbBlock(blockChain)){
      if(transaction > getNbTransationBlock(getBlockInChain(blockChain, i))){
        printf("Le block ne contient pas la transaction demandé.\n");
        return 0;
      }
    }
    else {
      printf("Impossible ! Le numéro du block demander a cheater ne serra pas créé, nombre de block créé inférieur.\n");
      return 0;
    }
    printf("### SUPPRESSION LA TRANSACTION n°%d DU BLOCK n°%d ###\n", transaction, i);
    printf("### RECALCUL DE TOUT LES HASHS DES BLOCKS A PARTIR DU BLOCK n°%d DE LA BLOCKCHAIN ###\n", i);
    float temps;
    clock_t t1, t2;
    t1 = clock();
    alteredTransactionBlock(blockChain, getBlockInChain(blockChain, i), transaction);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("### FIN DU CALCUL DE TOUT LES HASHS DES BLOCKS DE LA BLOCKCHAIN EN %fs ###\n\n",temps);
    printf("### CHEAT TERMINER ###\n");
    verifBlockChain(blockChain);
    return 1;
  }
  else{
    if( i > getNbBlock(blockChain)){
      printf("Impossible ! Le numéro du block demander a cheater ne serra pas créé, nombre de block créé inférieur.\n");
      return 0;
    }
    printf("### SUPPRESSION DU BLOCK n°%d ###\n", i);
    printf("### RECALCUL DE TOUT LES HASHS DES BLOCKS A PARTIR DU BLOCK n°%d DE LA BLOCKCHAIN ###\n", i);
    float temps;
    clock_t t1, t2;
    t1 = clock();
    alteredRemoveBlock(blockChain, i);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("### FIN DU CALCUL DE TOUT LES HASHS DES BLOCKS DE LA BLOCKCHAIN EN %fs ###\n\n",temps);
    printf("### CHEAT TERMINER ###\n");
    verifBlockChain(blockChain);
    return 1;
  }
}

BlockChain* genBlockChain(int difficulty, int nbBlock){
  printf("### GENERATION BLOCKCHAIN ###\n\n");
  float temps;
  clock_t t1, t2;
  t1 = clock();
  BlockChain* temp = createBlockChain(difficulty);
  for(int i  = 0; i < nbBlock; ++i){
    printf("### GENERATION BLOCK n° %d ###\n", i + 1);
    createBlock(temp);
    printBlock(getLastBlock(temp));
  }
  t2 = clock();
  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  printf("### GENERATION BLOCKCHAIN TERMINEE EN %fs ###\n\n", temps);
  return temp;
}
