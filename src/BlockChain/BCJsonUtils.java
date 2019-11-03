package BlockChain;
import java.io.FileReader;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;

import com.google.gson.Gson;

public class BCJsonUtils {

    public static BlockChain JSONReading(String filename) {

        Gson gson = new Gson();

        try (Reader reader = new FileReader(filename)) {

	// Convert JSON to Java Object
            BlockChain bc = gson.fromJson(reader, BlockChain.class);
            //System.out.println(bc);
            return bc;

			// Convert JSON to JsonElement, and later to String
            /*JsonElement json = gson.fromJson(reader, JsonElement.class);
            String jsonInString = gson.toJson(json);
            System.out.println(jsonInString);*/

        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void JSONWritting(BlockChain BlockC, String filename){
        // JSON Parser
        //1. Convert object to JSON string
        Gson gson = new Gson();
        String json = gson.toJson(BlockC);
        System.out.println(json);

        //2. Convert object to JSON string and save into a file directly
        try (FileWriter writer = new FileWriter(filename)) {

            gson.toJson(BlockC, writer);

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
