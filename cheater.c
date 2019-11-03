#include "cheater.h"

void alteredTransactionBlock(BlockChain* blockChain, Block* blockTemp, int removeTransaction){

  for(int i = removeTransaction; i < getNbTransationBlock(blockTemp) - 1; ++i){
      setListTransactionBlockI(blockTemp, getListTransationBlockI(blockTemp, i + 1), i);
  }//On décale la transaction pour "remplir" le tableau vers la droite.
  //On actualise le nombre de transaction dans le block.
  setNbTransactionBlock(blockTemp, getNbTransationBlock(blockTemp) - 1);
  for(int i = getIndexBlock(blockTemp); i < getNbBlock(blockChain); ++i){
    //On actualise les Hashprevious pour chaque bloque et on les remines
      setHashPrevious(getBlockInChain(blockChain, i), getHashCurrent(getBlockInChain(blockChain, i - 1)));
    miningBlock(getBlockInChain(blockChain, i), getDifficulty(blockChain));
  }
}

void alteredRemoveBlock(BlockChain* blockChain, int index){

  removeBlock(blockChain, index);
  for(int i = index; i < getNbBlock(blockChain); ++i){
    //On actualise les Hashprevious pour chaque bloque et on les remines
      setHashPrevious(getBlockInChain(blockChain, i), getHashCurrent(getBlockInChain(blockChain, i - 1)));
    miningBlock(getBlockInChain(blockChain, i), getDifficulty(blockChain));
  }
}
