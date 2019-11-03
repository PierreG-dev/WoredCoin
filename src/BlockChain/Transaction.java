package BlockChain;

/* Ma classe transaction, qui n'est pas terminée. */


public class Transaction {
	@SuppressWarnings("unused")
	private int index;
	@SuppressWarnings("unused")
	private String timestamp;
	@SuppressWarnings("unused")
	private String source;
	@SuppressWarnings("unused")
	private String destination;
	@SuppressWarnings("unused")
	private int montant;
	
	public Transaction(String source, String destination, int montant) {
		this.source = source;
		this.destination = destination;
		this.montant = montant;
		this.timestamp = Date.chaine();
	}
}
