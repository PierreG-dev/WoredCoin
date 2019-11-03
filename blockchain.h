#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "block.h"
#include "config.h"

//Structure Block
typedef struct sBlockList BlockList;
//Structure Block
typedef struct sBlockChain BlockChain;

//Fonction
Block* firstBlock();
BlockList* addBlockList(Block* block);
BlockChain* createBlockChain(int difficulty);
BlockList* genBlockList(Block* block);
Block* getLastBlock(BlockChain* blockChain);
void addBlock(BlockChain* blockChain, Block* block);
void removeBlock(BlockChain* blockChain, int indexBlock);
bool chainIsValid(BlockChain* blockChain);
bool merkleIsValid(BlockChain* blockChain);
Block* getBlockInChain(BlockChain* blockChain, int index);
int getNbBlock(BlockChain* blockChain);
int getDifficulty(BlockChain* blockChain);

#endif /* !BLOCKCHAIN_H */
