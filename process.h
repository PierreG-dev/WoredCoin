#ifndef PROCESS_H
#define PROCESS_H

//Librairie
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Fichier h
#include "blockchain.h"
#include "block.h"
#include "transaction.h"
#include "cheater.h"
#include "merkel.h"
#include "sha256_utils.h"
#include "config.h"


void printBlockChain(BlockChain* blockChain);
int hackBlockChain(BlockChain* blockChain, int i, int transaction);
BlockChain* genBlockChain(int difficulty, int nbBlock);

//Fonction pour pouvoir rajouter des actions plus spécifique. Pas utile dans l'état actuel du programme.

//void createBlock(BlockChain* temp);
//void printBlock(Block* blockTemp);
//bool verifBlockChain(BlockChain* blockChain);
//bool verifHashRoot(BlockChain* blockChain);

#endif /* !PROCESS_H */
