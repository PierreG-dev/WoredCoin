package BlockChain;

import java.util.Random;

/* Classe qui gere les paramètres de la blockchain de manière globale
 * Alors oui, je sais c'est pas bien les variables statiques, mais je trouvais 
 * ça beaucoup plus efficace dans ce cas la, pas besoin d'instacier 0:)
 */

public class Parametres {
	
	//Parametres generaux du programme
	private static int difficulty = 4;
	private static int nbBlock = 4;
	private static int nbTransMax = 4;
	
	
	//Methode qui génère et retourne un nombre aleatoire entre nb transmax et 1,
	//fonction utilisée dans Block pour générer le nombre de transactions de ce dernier.
	public static int GenerateNbTransMax() {
		Random random = new Random();
		return random.nextInt(nbTransMax) + 1;
	}
	
	
	//Modification de difficulty
	public static void setDifficult(int diff) {
		difficulty = diff;
	}
	
	//Obtention de Difficulty
	public static int getDifficulty() {
		return difficulty;
	}
	
	
	//Modification de nbBlock
	public static void setNbBlock(int nb) {
		nbBlock = nb;
	}
	
	//Obtention de nbBlock
	public static int getNbBlock() {
		return nbBlock;
	}
	
	//Obtention de nbTransMax
	public static int getNbtransMax() {
		return nbTransMax;
	}
    
	//Modification de nbTransMax
    public static void setNbTransMax(int nb) {
        nbTransMax = nb;
    }
}
