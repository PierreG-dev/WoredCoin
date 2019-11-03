#include "merkel.h"


char* getMerkelRoot(char** tabTransaction, int nbTransaction){

    char** tabHash = malloc((nbTransaction+1) * (sizeof(char*)));
    for(int i = 0; i < nbTransaction + 1; ++i){
      tabHash[i] = malloc(((HASH_SIZE) + 1) * (sizeof(char)));
    }
    //Hashage de chaque transaction si impair on duplique la dernière case du tableau
    for(int i = 0; i < nbTransaction; ++i){
      BYTE buffer[TRANSACTION_SIZE];
      sprintf((char*)buffer, "%s", tabTransaction[i]);
      sha256ofString(buffer, tabHash[i]);
    }

    //Calcul des hash en concaténant. Fonction Identique au code java.
    int i = nbTransaction - 1;
    int temp = nbTransaction;
    int inc = 0;

    while(temp != 1){

      if(temp%2 != 0){
        //On s'assure d'avoir un nombre de hash a concaténé pair, sinon on double le dernier hash
        tabHash[temp] = tabHash[temp - 1];
        temp++;
      }
      i = temp - 1;

      for(int indice = 0; indice < i; indice += 2){
          //On concatène et on hash
          BYTE buffer[sizeof(tabHash[indice]) + sizeof(tabHash[indice+1])];
          snprintf((char*)buffer, sizeof(buffer), "%s%s", tabHash[indice], tabHash[indice+1]);
          sha256ofString(buffer, tabHash[inc]);
          inc++;
        }
        temp = temp/2;
        inc = 0;

  }
  return tabHash[0];
}
