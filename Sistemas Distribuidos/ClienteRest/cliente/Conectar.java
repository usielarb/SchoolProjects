public import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.lang.reflect.Type;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class Conectar{
    public static <T> String serializeJson(T object) {
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        return gson.toJson(object);
    }
    public static <T> T deserializeJson(String json, Type t) {
        Gson gson = new Gson();
        return gson.fromJson(json, t);
    }
    
    public static String opciones(String operacion, String parametro, String json, String ip)
            throws MalformedURLException, IOException, RuntimeException {
        URL url = new URL("http://" + ip + ":8080/Servicio/rest/ws/" + operacion);
        HttpURLConnection conectar = (HttpURLConnection)url.openConnection();
        
        conectar.setDoOutput(true);
        conectar.setRequestMethod("POST");
        conectar.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
        String parametros = parametro + "=" + URLEncoder.encode(json, "UTF-8");

        OutputStream os = conectar.getOutputStream();

        os.write(parametros.getBytes());
        os.flush();
        if (conectar.getResponseCode() != HttpURLConnection.HTTP_OK){
            throw new RuntimeException("ERROR " + conectar.getResponseCode());
        }
        BufferedReader buff = new BufferedReader(new InputStreamReader(conectar.getInputStream()));
        String res;
        String aux = "";
        while ((res = buff.readLine()) != null){
            aux += res;
        }
        conectar.disconnect();
        return aux;
    }
}class Conectar {
    
}
