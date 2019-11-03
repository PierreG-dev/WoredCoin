package Test;



import BlockChain.Date;
import BlockChain.BCJsonUtils;
import BlockChain.BlockChain;

/* CECI EST LE MAIN POUR TESTER DEPUIS LE PROGRAMME. IL N'UTILISERA QUE LA CONSOLE POUR AFFICHER, ET EXPLOITE LA TOTALITE DES CHOSES A FAIRE DANS 
 * L'ETAPE 1, SAUF L'INTERFACE BIEN ENTENDU. SI VOUS VOULEZ 
 */




@SuppressWarnings("unused")
public class TestProg {
	public static void main(String[] args) {
		
		BlockChain blockchain = new BlockChain(true); 
		System.out.println("[Blockchain] : Coucou c'est moi la BlockChain, je suis née le " + Date.chaine() + " // Blockchain créée. de manière aléatoire");
		System.out.println("[Blockchain] : Miné et prêt à servir !");
		System.out.println("[Blockchain] : Je vais maintenant m'enregistrer sur ton ordinateur ! //Sauvegarde terminée, sous le nom de Blockchain.JSON");
		BCJsonUtils.JSONWritting(blockchain, "Blockchain");
		System.out.println("\n[Blockchain] : Je m'en vais ...... et je reviens !!!  //Importation terminée");
		BCJsonUtils.JSONReading("Blockchain");
		System.out.println(blockchain.verif1());
		System.out.println(blockchain.verif2());
		System.out.println("\n\n[Blockchain] : Comme vous pouvez le voir! je suis en pleine santée :)");
		System.out.println("[Blockchain] : Voyons voir à quoi je ressemble ...");
		System.out.println(blockchain.parcourir());
		
	}
}