# WoredCoin _ Level_1
# Programme C

Notice du Logiciel du WoredCoin 0.1:

Commande: ./woredCoin -b (bombreDeBlock) -d (difficulté) -cb (Optionnel -> supprime le block n°x) -ct (Optionnel -> supprime la transaction n°x NECCESSITE -cb)

Configuration: Toutes les variables de configuration sont disponibles dans le fichier config.h

Exemple:

\\#define MAX_BLOCK 3 //nb de caract du Nombre
\\#define MAX_TRANSACTION_CHAR 3 //nb de caract du Nombre de Transaction
\\#define MAX_NONCE_CHAR 10 //Nb caract max de la nonce
\\#define TRANSACTION_SIZE 30 // Taille de la chaine de caractère d'une transaction
\\#define TIMESTAMP_SIZE 25 //nb de caract du timeStamp

\\#define MAX_TRANSACTION 100 //nb max de transaction
\\#define HASH_SIZE 64 //Taille du hash
\\#define MAX_NONCE 9999999 //Nonce max
\\#define MAX_VALUE_RAND 1000000 //Max nombre random pour simuler transaction
