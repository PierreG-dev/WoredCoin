#include "blockchain.h"

struct sBlockList {
  Block* block;                //Block
  struct sBlockList *next;    //Pointeur vers prochain block
};

struct sBlockChain {
  int nbBlocks;               //Nombre de nbBlock
  int difficulty;             //Difficulté de la blockchain
  BlockList *blocklist;        //Liste des blocks
  BlockList *lastBlockList;    //Dernier block
  //BlockList firstBlockList;
};

Block* firstBlock(){
  Block* first = GenesisBlock();
  miningBlock(first, 0);
  return first;
}

BlockList* addBlockList(Block* block){

  BlockList* bl = (BlockList*)malloc(sizeof(struct sBlockList));
	bl->block = block;
	bl->next = NULL;
	return bl;
}



BlockChain* createBlockChain(int difficulty){
  BlockChain *blockChain = malloc(sizeof(struct sBlockList));
  blockChain->nbBlocks = 1;
  blockChain->difficulty = difficulty;
  blockChain->blocklist = addBlockList(firstBlock(difficulty));
  blockChain->lastBlockList = blockChain->blocklist;
  return blockChain;

}

Block* getLastBlock(BlockChain* blockChain){
  return blockChain->lastBlockList->block;
}

void addBlock(BlockChain* blockChain, Block* block){
  blockChain->lastBlockList->next = addBlockList(block);
  blockChain->lastBlockList = blockChain->lastBlockList->next;
  ++(blockChain->nbBlocks);
}

void removeBlock(BlockChain* blockChain, int indexBlock){
  BlockList* bl = blockChain->blocklist;
  BlockList* bl2 = blockChain->blocklist;
  int nbBlocks = blockChain->nbBlocks;

  for(int i = 0; i < indexBlock - 1; i++){
    if(i < nbBlocks){
      bl = bl->next;
    }
    else{
      break;
    }
  }
  for(int i = 0; i < indexBlock + 1; i++){
    if(i < nbBlocks){
      bl2 = bl2->next;
    }
    else{
      break;
    }
  }

  bl->next = bl2;
  blockChain->lastBlockList->next = bl;
  blockChain->lastBlockList = blockChain->lastBlockList->next;
  blockChain->nbBlocks = blockChain->nbBlocks - 1;

}



Block* getBlockInChain(BlockChain* blockChain, int index){
  BlockList* bl = blockChain->blocklist;

  int nbBlocks = blockChain->nbBlocks;
  for(int i = 0; i < index; i++){
    if(i < nbBlocks){
      bl = bl->next;
    }
    else{
      break;
    }
  }
  return bl->block;
}




bool chainIsValid(BlockChain* blockChain){
  //Vérification du génésis
  if(getIndexBlock(blockChain->blocklist->block) == 0 && strcmp(getHashPrevious(blockChain->blocklist->block), "0") == 0){
    //On vérifie ça contenance:
    if(getNbTransationBlock(blockChain->blocklist->block) == 1 && strcmp(getListTransationBlock(blockChain->blocklist->block)[0], "Genesis") == 0){
      //On vérifie MERKLE
      if(blockIsValid(getBlockInChain(blockChain, 0)) != true){
        return false;
      }else{
      printf("### BLOCK GENESIS IS CORRECT ###\n");
    }
  }else{
        printf("### BLOCK GENESIS IS NOT CORRECT\n");}
  }

//Vérifacation des ordres blocks.
  for(int i = 1; i<blockChain->nbBlocks; ++i){
    Block* temp = getBlockInChain(blockChain, i);
    setHashPrevious(temp,getHashCurrent(getBlockInChain(blockChain, i - 1)));
    if(blockIsValid(getBlockInChain(blockChain, i)) != true){
      printf("#### BLOCK %d IS NOT CORRECT ###\n", i);
      return false;
    }
    printf("#### BLOCK %d IS CORRECT ###\n", i);

  }
  return true;
}

bool merkleIsValid(BlockChain* blockChain){
  for(int i = 0; i < getNbBlock(blockChain); ++i){
    if(strcmp(getHashMerkleRoot(getBlockInChain(blockChain, i)), getMerkelRoot(getListTransationBlock(getBlockInChain(blockChain, i)), getNbTransationBlock(getBlockInChain(blockChain, i)))) != 0){
      printf("### HASH MERKLEROOT IN BLOCK %d IS NOT CORRECT ###\n", i);
      return false;
    }
    printf("### HASH MERKLEROOT IN BLOCK %d IS CORRECT ###\n", i);
  }
  return true;
}


int getNbBlock(BlockChain* blockChain){
  return blockChain->nbBlocks;
}

int getDifficulty(BlockChain* blockChain){
  return blockChain->difficulty;
}
