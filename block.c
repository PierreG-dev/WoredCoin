#include "block.h"

struct sBlock{

  int index;                      //Numéro du BlockList
  char timeStamp[TIMESTAMP_SIZE+1]; //Horodatage du block

  int nbTransaction;              //Nombre de transaction
  char** transactionList;         //Liste des transactions

  char* hashMerkleRoot; //Hash root de l'arbre de Merkle des transactions
  char* hashCurrent;    //Hash du block courant
  char* hashPrevious;   //Hash du block précèdent

  int nonce;                      //Nombre pseudo aléatoire et unique

};

int getIndexBlock(Block* blockTemp){
  return blockTemp->index;
}

void setIndexBlock(Block* blockTemp, int index){
  blockTemp->index = index;
}
char* getTimeStampBlock(Block* blockTemp){
  return blockTemp->timeStamp;
}
void setTimeStampBlock(Block* blockTemp, char* timeStamp){
  strcpy(blockTemp->timeStamp, timeStamp);
}

int getNbTransationBlock(Block* blockTemp){
  return blockTemp->nbTransaction;
}

void setNbTransactionBlock(Block* blockTemp, int nb){
  blockTemp->nbTransaction = nb;
}

char** getListTransationBlock(Block* blockTemp){
  return blockTemp->transactionList;
}

void setListTransactionBlock(Block* blockTemp, char** transaction){
  blockTemp->transactionList = transaction;
}

char* getListTransationBlockI(Block* blockTemp, int index){
  return blockTemp->transactionList[index];
}

void setListTransactionBlockI(Block* blockTemp, char* transaction, int index){
  blockTemp->transactionList[index] = transaction;
}

char* getHashMerkleRoot(Block* blockTemp){
  return blockTemp->hashMerkleRoot;
}

void setHashMerkleRoot(Block* blockTemp, char* hash){
  blockTemp->hashMerkleRoot = hash;
}

char* getHashPrevious(Block* blockTemp){
  return blockTemp->hashPrevious;
}

void setHashPrevious(Block* blockTemp, char* hash){
  blockTemp->hashPrevious = hash;
}
char* getHashCurrent(Block* blockTemp){
  return blockTemp->hashCurrent;
}

void setHashCurrent(Block* blockTemp, char* hash){
  blockTemp->hashCurrent = hash;
}

int getNonceBlock(Block* blockTemp){
  return blockTemp->nonce;
}

void setNonceBlock(Block* blockTemp, int nonce){
  blockTemp->nonce = nonce;
}



char* getTimeStamp(){
  time_t ltime;
  time(&ltime);
  return ctime(&ltime);
}

bool miningOK (char* hashTemp, int difficulty){
  for(int i = 0; i < difficulty; ++i){
    if(hashTemp[i] != '0'){
      return false;
    }
  }
  return true;
}


void miningBlock(Block* blockTemp, int difficulty){

  //printf("######%d\n\n", getIndexBlock(blockTemp));
  //concaténer les infos du block -> Taille + malloc
  int sizeConcat = MAX_BLOCK + TIMESTAMP_SIZE + MAX_TRANSACTION + (TRANSACTION_SIZE)*getNbTransationBlock(blockTemp) + (HASH_SIZE)*2 + MAX_NONCE_CHAR;

  char* hashBlock = malloc((HASH_SIZE + 1)*sizeof(char));
  char* tabConcat = malloc( (sizeConcat + 1) * sizeof(char));

  char IndexToString[MAX_BLOCK];
  char NbTransToString[MAX_TRANSACTION];
  char NonceToString[MAX_NONCE_CHAR];

  sprintf(IndexToString, "%d", getIndexBlock(blockTemp));
  sprintf(NbTransToString, "%d", getNbTransationBlock(blockTemp));


  strcpy(tabConcat, IndexToString);
  strcat(tabConcat, getTimeStampBlock(blockTemp));
  strcat(tabConcat, NbTransToString);

  for(int i = 0; i < getNbTransationBlock(blockTemp); i++){
    strcat(tabConcat, getListTransationBlockI(blockTemp, i));
  }

  setHashMerkleRoot(blockTemp, getMerkelRoot(getListTransationBlock(blockTemp), getNbTransationBlock(blockTemp)));
  //printf("STRLEN TABCONCAT = %d  MERKLE ROOT %d", strlen(tabConcat), strlen(blockTemp->hashMerkleRoot));
  //printf("HASH MERKLE %s\n", blockTemp->hashMerkleRoot);
  strcat(tabConcat, getHashMerkleRoot(blockTemp));
  //printf("HASH PREV %s\n", blockTemp->hashPrevious);
  strcat(tabConcat, getHashPrevious(blockTemp));

  int nonce = 0;
  char* tabConcatNonce = malloc((sizeConcat + 1) * sizeof(char));
  while(1){
    strcpy(tabConcatNonce, tabConcat);
    sprintf(NonceToString, "%d", nonce);
    strcat(tabConcatNonce, NonceToString);
    sha256ofString((BYTE*)tabConcatNonce, hashBlock);
    if(miningOK(hashBlock, difficulty) ==true){
      break;
    }
    nonce = nonce + 1;
  }

  setHashCurrent(blockTemp, hashBlock);
  setNonceBlock(blockTemp, nonce);
}

bool blockIsValid(Block* blockTemp){

  //concaténer les infos du block -> Taille + malloc
  int sizeConcat = MAX_BLOCK + TIMESTAMP_SIZE + MAX_TRANSACTION + (TRANSACTION_SIZE)*getNbTransationBlock(blockTemp) + (HASH_SIZE)*2 + MAX_NONCE_CHAR;

  char* hashBlock = malloc((HASH_SIZE + 1)*sizeof(char));
  char* tabConcat = malloc( (sizeConcat + 1) * sizeof(char));

  char IndexToString[MAX_BLOCK];
  char NbTransToString[MAX_TRANSACTION];
  char NonceToString[MAX_NONCE_CHAR];

  sprintf(IndexToString, "%d", getIndexBlock(blockTemp));
  sprintf(NbTransToString, "%d", getNbTransationBlock(blockTemp));

  strcpy(tabConcat, IndexToString);
  strcat(tabConcat, getTimeStampBlock(blockTemp));
  strcat(tabConcat, NbTransToString);

  for(int i = 0; i < getNbTransationBlock(blockTemp); i++){
    strcat(tabConcat, getListTransationBlockI(blockTemp, i));
  }
  strcat(tabConcat, getMerkelRoot(getListTransationBlock(blockTemp), getNbTransationBlock(blockTemp)));
  strcat(tabConcat, getHashPrevious(blockTemp));
  sprintf(NonceToString, "%d", getNonceBlock(blockTemp));
  strcat(tabConcat, NonceToString);
  sha256ofString((BYTE*)tabConcat, hashBlock);
  if(strcmp(hashBlock, getHashCurrent(blockTemp)) == 0){
    return true;
  }
  return false;
}


Block* GenesisBlock(){

  char* timeStamp = getTimeStamp();
  Block *temp = (Block*) malloc(sizeof(struct sBlock));

  setIndexBlock(temp, 0);
  setNbTransactionBlock(temp, 1);
  char** transactionTemp = malloc(sizeof(char)*8);
  transactionTemp[0] = "Genesis";
  setListTransactionBlock(temp, transactionTemp);
  setTimeStampBlock(temp, timeStamp);
  setHashPrevious(temp, "0");

  return temp;

}

Block* GenBlock(Block* prevBlock){

  char* timeStamp = getTimeStamp();
  Block *temp = (Block*) malloc(sizeof(struct sBlock));
  setIndexBlock(temp, getIndexBlock(prevBlock) + 1);
  setTimeStampBlock(temp, timeStamp);
  setHashPrevious(temp, getHashCurrent(prevBlock));

  return temp;
}

void freeBlockTransI(Block* temp, int i){
  printf("JE VAIS FREE %d", i);
  free(temp->transactionList[i]);
}
