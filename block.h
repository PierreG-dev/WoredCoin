#ifndef BLOCK_H
#define BLOCK_H


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "merkel.h"
#include "sha256_utils.h"
#include "config.h"


typedef struct sBlock Block;

//Fonction accès structure block, beaucoup inutile.
int getIndexBlock(Block* blockTemp);
void setIndexBlock(Block* blockTemp, int index);
char* getTimeStampBlock(Block* blockTemp);
void setTimeStampBlock(Block* blockTemp, char* timeStamp);
int getNbTransationBlock(Block* blockTemp);
void setNbTransactionBlock(Block* blockTemp, int nb);
char** getListTransationBlock(Block* blockTemp);
void setListTransactionBlock(Block* blockTemp, char** transaction);
char* getListTransationBlockI(Block* blockTemp, int index);
void setListTransactionBlockI(Block* blockTemp, char* transaction, int index);
char* getHashMerkleRoot(Block* blockTemp);
void setHashMerkleRoot(Block* blockTemp, char* hash);
char* getHashPrevious(Block* blockTemp);
void setHashPrevious(Block* blockTemp, char* hash);
char* getHashCurrent(Block* blockTemp);
void setHashCurrent(Block* blockTemp, char* hash);
int getNonceBlock(Block* blockTemp);
void setNonceBlock(Block* blockTemp, int nonce);

//Fonction
char* getTimeStamp();
bool miningOK(char* hasTemp, int difficulty);
void miningBlock(Block* blockTemp, int difficulty);
bool blockIsValid(Block* blockTemp);
Block* GenesisBlock();
Block* GenBlock(Block* prevBlock);
void freeBlockTransI(Block* temp, int i);
#endif /* !BLOCK_H */
