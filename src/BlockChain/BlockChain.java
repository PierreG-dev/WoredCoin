package BlockChain;

import java.util.List;
import java.util.ArrayList;
import BlockChain.Block;
import BlockChain.BCJsonUtils;



public class BlockChain {

	//-----------------------------------------------//
	//----------------- Attributs -------------------//
	//-----------------------------------------------//

	@SuppressWarnings("unused")
	private int difficulty;
	private int nbBlock;
        private int nbTransMax;
	private List<Block> blockchain;


	//------------------------------------------------//
	//----------------- Constructeur -----------------//
	//------------------------------------------------//
	
	//Constructeur pour creer une blockchain de toute pieces (parametre inutile, simplement pour eviter le conflit avec l'autre constructeur)
	public BlockChain(boolean bool) {
                this.nbTransMax = Parametres.getNbtransMax();
		this.difficulty = Parametres.getDifficulty();
		this.nbBlock = Parametres.getNbBlock();
		blockchain = new ArrayList<Block>();
		System.out.println("Blockchain creee");
		blockchain.add(new Block(1, Date.chaine(), "0"));
		blockchain.get(0).createTransaction("Genesis");
		System.out.println("Block Genesis créé avec succes");
		this.generateBlockchain();
		System.out.println("\n\n\n");
		System.out.println("--------------------------------------------------------------------------------");
		System.out.println("La blockchain a ete generee avec succes, selon parametres suivants :");
		System.out.println("Difficulte : " + Parametres.getDifficulty());
		System.out.println("Nombre de blocks : " + Parametres.getNbBlock());
		System.out.println("Nombre maximal de transactions par block : " + Parametres.getNbtransMax());
	}


		//Constructeur pour l'importation de blockchain depuis un fichier JSON
        public BlockChain(String jsonFile) {
		BlockChain bc = BCJsonUtils.JSONReading(jsonFile);
		Parametres.setDifficult(bc.difficulty);
		Parametres.setNbBlock(bc.nbBlock);
		Parametres.setNbTransMax(bc.nbTransMax);
                this.nbTransMax = Parametres.getNbtransMax();
		this.difficulty = Parametres.getDifficulty();
		this.nbBlock = Parametres.getNbBlock();
		this.blockchain = bc.getBlockchain();
	}

        
        
        
	//--------------------------------------------//
	//----------------- Methodes -----------------//
	//--------------------------------------------//


    //Methode qui ecrit la blockchain courante dans un fichier JSON dans le fichier courant
    public void jsonWrite(String jsonFile) {
           BCJsonUtils.JSONWritting(this, jsonFile);
    }



	//Methode pour ajouter un block dans la blockchain (optionnel)
	public void createBlock() {
		Block prev = blockchain.get(nbBlock);
		nbBlock++;
		blockchain.add(new Block(nbBlock, Date.chaine(), prev.getHash()));
		blockchain.get(nbBlock).fillBlock();
		blockchain.get(nbBlock).calculateHash();
	}



	//Methode pour generer la blockchain
	public void generateBlockchain() {
		String prev;

		for(int i = 2; i <= Parametres.getNbBlock(); i++) {
			prev = blockchain.get(i - 2).getHash();
			blockchain.add(new Block(i, Date.chaine(), prev));
			blockchain.get(i - 1).fillBlock();
			blockchain.get(i - 1).calculateHash();
			System.out.println("Le block numero " + i + " a ete genere et mine : " + blockchain.get(i - 1).getNbTrans() + "    " + blockchain.get(i - 1).getHash());


		}
	}
	
    
	
        //Methode qui applique l'etape 1 des verifications sur la blockchain courante
        public String verif1() {
            Block block;
            
                

		System.out.println("\n\n\n\n---------------------------------- Verifications de la blockchain ----------------------------------");
		//Verification 1 :
		//Verification du gennesis
		Block genesis = blockchain.get(0);
		int nbGennesis = genesis.getNbTrans();
		String transGennesis = genesis.getTrans(0);
		if ((nbGennesis != 1) && (transGennesis.equals("Gennesis")))
			return("Erreur critique : le Genesis n'est pas present, la vérification ne peut se terminer.");

		//Verification de l'integrite des hashs et du chainage
		boolean hashErr = false;
		boolean chainErr = false;
                String merkTemp;
		for (int i = 1; i < Parametres.getNbBlock(); i++) {

			block = blockchain.get(i);
                        merkTemp = block.getHashMerk();
			String hash = block.getHash();
			String hashtemp = block.calculateHash();
			String hashPrevTemp = blockchain.get(i - 1).getHash();
			String hashPrev = block.getHashPrev();
                        block.setMerkle(merkTemp);

			if (!hash.equals(hashtemp)) {
				System.out.println("Erreur de hash.");
				hashErr = true;
			}
			if (!hashPrevTemp.equals(hashPrev)) {
				System.out.println("Erreur : Chainage de la blockchain corrompu (block " + i + ").");
				chainErr = true;
				break;
			}
		}
		if (hashErr == false && chainErr == true)
			return("Erreur : le chainage de la blockchain est corrompu, mais tous les hashs jusqu'à l'erreur de chainage sont corrects et le Genesis est présent.");
                else if (hashErr == false && chainErr == false)
			return("Tous les hash de blocks sont coherents, le chainage de la blockchain est correct et le Genesis est présent.");
                else if (hashErr == true && chainErr == false)
			return("Erreur : un ou plusieurs hashs sont incorrects, mais ont etes repares, le chainage de la blockchain quand à lui est correct et le Genesis est présent.");
                else if (hashErr == true && chainErr == true)
                        return("Erreur critique : Le chainage est corrompu, de plus, l'intégrité des hashs jusqu'à l'erreur de chainage n'est pas totale, malgrès tout le Genesis est présent..");
                return "0";
                 
        }
        
        
        
        //Methode qui applique la verification numero 2
        public String verif2() {
            Block block;
            
            //Verification 2 :
		//Verification de l'integrite du hash de merkle (hash root)
		boolean merkErr = false;

		for (int i = 0; i < Parametres.getNbBlock(); i++) {
			block = blockchain.get(i);
			String hashMerkle = block.getHashMerk();
			String hashMerkleTemp = block.merkle();
			if (!hashMerkle.equals(hashMerkleTemp)) {
				System.out.println("Erreur de hash root.");
				merkErr = true;
			}
		}

		if (merkErr == false) {
			return("Tous les hashs de Merkle sont corrects.");
                }
                else {
			return("Un ou plusieurs hashs de merkle sont incorrects.");
                }
        }
        
        
        
        //Methode qui retourne la liste de blocks de la blockchain
        public List<Block> getBlockchain() {
            return this.blockchain;
        }
        
        
        
        //Methode qui parcours chaque block de la blockchain (utile pour l'affichage
        public String parcourir() {
            String ret = "-------------------------- BlockChain --------------------------\n";
            for (int i = 0; i < nbBlock; i++) {
                ret = ret + "\n\n" + blockchain.get(i).printBlock();
            }
            
            return ret;
        }


}
