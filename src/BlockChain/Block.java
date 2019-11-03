package BlockChain;

import java.security.MessageDigest;
import java.util.Random;

public class Block {

	//-----------------------------------------------//
	//----------------- Attributs -------------------//
	//-----------------------------------------------//

	private int index;//Numero du block dans la continuite
	private String timestamp;//date de creation du bloc
	private String hash;//Hash final avec le Hash de merkel et les Hash des caracteristiques du block
	private String hashMerk;//Hash de l'arbre de Merkel
	private String hashPrev;//Hash du block qui precede
	private int nbTrans; // Nombre de transactions
	private int nonce;//Indice pour le minage
	private String[] transactions;//Liste des transactions
	private int nbTransMax = Parametres.GenerateNbTransMax(); //Entier unite genere aleatoirement representant le nombre maximum de transactions qu'un bloc peut avoir



	//------------------------------------------------//
	//----------------- Constructeur -----------------//
	//------------------------------------------------//


	public Block(int index, String timestamp, String hashPrev) {
		this.index = index;
		this.timestamp = timestamp;
		this.hashPrev = hashPrev;
		this.nonce = 0;
		this.nbTrans = 0;
		this.transactions = new String[nbTransMax];
	}



	//--------------------------------------------//
	//----------------- Methodes -----------------//
	//--------------------------------------------//


	//Methode pour calculer le hash d'une chaine de caracteres en parametre
	 public static String sha256(String input) {

		 try {
			 MessageDigest digest = MessageDigest.getInstance("SHA-256");

			 //Applique le SHA-256 e notre input
			 byte[] hash = digest.digest(input.getBytes("UTF-8"));

			 StringBuffer hexString = new StringBuffer(); // Cela contiendra le Hash sous forme Hexadecimale
			 for (int i = 0; i < hash.length; i++) {
				 String hex = Integer.toHexString(0xff & hash[i]);
				 if(hex.length() == 1) hexString.append('0');
				 hexString.append(hex);
			 }
			 return hexString.toString();
		 }
		 catch(Exception e) {
			 throw new RuntimeException(e);
		 }
	}


	//Methode qui retourne true si le hash correspond e la difficultee de la blockchain
	public static boolean isHashOk(int difficult, String hash) {

		char[] tab = hash.toCharArray();

		for (int i = 0; i < difficult; i++) {
			if (tab[i] != '0')
				return false;
		}
		return true;
	}



	//Methode pour creer une transaction (optionnel)
	public void createTransaction(String trans) {
		transactions[nbTrans] = trans;
		nbTrans++;
		calculateHash();
	}



	//Methode pour obtenir le hash d'une transaction dont le numero dans le tableau est fourni
	public String hashTrans(int nb) {
		return sha256(transactions[nb]);
	}
	


	//Methode pour obtenir le Hash de Merkle pour la liste de transactions
	public String merkle() {
		String[] listeHash = new String[nbTrans + 1];

		for (int i = 0; i < nbTrans; i++) {
			listeHash[i] = transactions[i];
		}

		if (nbTrans == 1)
			return sha256(listeHash[0]);

		int i = nbTrans - 1;
		int temp = nbTrans;
		int inc = 0;

		while (temp != 1) {

			if (temp % 2 != 0) {
				listeHash[temp] = listeHash[temp - 1];
				temp++;
			}

			i = temp - 1;

			for (int indice = 0; indice < i; indice += 2) {
				listeHash[inc] = sha256(listeHash[indice] + listeHash[indice + 1]);
				inc++;
			}

			temp /= 2;
			inc = 0;

		}
		return listeHash[0];
	}



	//Methode pour generer une transaction aleatoire
	public static String generateTrans() {
		String sender;
		String receiver;
		int amount;



		Random random = new Random();

		switch (random.nextInt(8)) {

			case 1:
				sender = "Jean-Kevin";
				break;
			case 2:
				sender = "Jean-Louis";
				break;
			case 3:
				sender = "Jean-Michel";
				break;
			case 4:
				sender = "Jean-Marie";
				break;
			case 5:
				sender = "Jean-Claude";
				break;
			case 6:
				sender = "Jean-Jacques";
				break;
			case 7:
				sender = "Jean-Bernard";
				break;
			default :
				sender = "Jean-Luc";
				break;
		}

		switch (random.nextInt(8)) {

		case 1:
			receiver = "Louis-Kevin";
			break;
		case 2:
			receiver = "Louis-Luc";
			break;
		case 3:
			receiver = "Louis-Michel";
			break;
		case 4:
			receiver = "Louis-George";
			break;
		case 5:
			receiver = "Louis-Lucas";
			break;
		case 6:
			receiver = "Louis-Jean";
			break;
		case 7:
			receiver = "Louis-Alexandre";
			break;
		default :
			receiver = "Louis-David";
			break;
		}

		amount = random.nextInt(9999);

		return sender + " envoie " + amount + " WC à " + receiver;
	}

	//Methode pour remplir le block avec des transactions
	public void fillBlock() {
		for (int i = 0; i < nbTransMax; i++) {
			transactions[i] = generateTrans();
			nbTrans++;
		}
	}



	//Methode pour calculer le hash du bloc entier et set le hash du merkle root
	public String calculateHash() {
		nonce = 0;
		String hashTemp = null;
		this.hashMerk = merkle();
		boolean state = false;

		while (!state) {

			hashTemp = sha256(String.valueOf(index) + timestamp + hashPrev + hashMerk + String.valueOf(nbTrans) + nonce);
			if (isHashOk(Parametres.getDifficulty(), hashTemp))
				state = true;

			nonce += 1;
		}
		this.hash = hashTemp;

		return hash;

	}


	//--------------------------------------------//
	//------------------ Getter ------------------//
	//--------------------------------------------//


	//Methode pour obtenir le hash du bloc courant
	public String getHash() {
		return hash;
	}

	//Methode pour obtenir le nombre de transactions du bloc
	public int getNbTrans() {
		return nbTrans;
	}

	//Methode pour obtenir le nombre de transactions max du bloc
	public int getNbTransMax() {
		return nbTransMax;
	}

	//Methode pour obtenir la chaine de caracteres correspondant a une transaction
	public String getTrans(int index) {
		return transactions[index];
	}

	//Methode pour obtenir le hash du bloc precedent
	public String getHashPrev() {
		return hashPrev;
	}

	//Methode pour obtenir le Hash de l'arbre de merkle
	public String getHashMerk() {
		return hashMerk;
	}



	//--------------------------------------------//
	//------------------ Divers ------------------//
	//--------------------------------------------//


	//Methode pour print toutes les transactions du block
	public String printBlock() {
                String ret = "\n----- Block numéro " + index + " -----";
                ret = ret + "\nnbTrans = " + nbTrans + "\nHashPrev = " + hashPrev + "\nHash = " + hash + "\nHashMerk = " + hashMerk;
		for (int i = 0; i < nbTrans; i++) {
			ret = ret + "\n	  Transaction n°" + (i+1) + " : " + transactions[i];
		}
            return ret;        
	}
        
    //Methode pour placer le hash merkle, pour compenser le fait que la verification 1 repare le hash, et empeche la verification 2 de fonctionner
    public void setMerkle(String merkle) {
        this.hashMerk = merkle;
    }
}
