import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.net.URL;
import java.net.HttpURLConnection;
import java.net.URLEncoder;
import java.io.OutputStream;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class Client{

  public static String server_ip = "157.55.183.76";
  public static Gson j;

  public static void menu(){
    System.out.println("\nMENU\n");
    System.out.println("a. Alta usuario");
    System.out.println("b. Consulta usuario");
    System.out.println("c. Borra usuario");
    System.out.println("d. Borra todos los usuarios");
    System.out.println("e. Salir\n");
    System.out.print("Opción: ");
  }

  public static void alta(BufferedReader br){
    try{
      System.out.println("\nIngresa el email del usuario que deseas dar de alta:");
      String email = br.readLine();
      System.out.println("Ingresa el nombre del usuario:");
      String nombre = br.readLine();
      System.out.println("Ingresa el apellido paterno del usuario:");
      String ap = br.readLine();
      System.out.println("Ingresa el apellido materno del usuario:");
      String am = br.readLine();
      System.out.println("Ingresa la fecha de nacimiento del usuario con formato aaaa-mm-dd:");
      String fecha = br.readLine();
      System.out.println("Ingresa el teléfono del usuario:");
      String tele = br.readLine();
      System.out.println("Ingresa el género del usuario ('M' O 'F'):");
      String gen = br.readLine();
      while(!gen.equals("M") && !gen.equals("F")){
        System.out.println("Ingresa el género del usuario ('M' O 'F'):");
        gen = br.readLine();
      }

      URL url = new URL("http://" + server_ip + ":8080/Servicio/rest/ws/alta");
      HttpURLConnection huc = (HttpURLConnection) url.openConnection();
      huc.setDoOutput(true);
      huc.setRequestMethod("POST");
      huc.setRequestProperty("Content-Type","application/x-www-form-urlencoded");

      Usuario u = new Usuario(email,nombre,ap,am,fecha,tele,gen,null);
      String params = "usuario=" + j.toJson(u);
      OutputStream os = huc.getOutputStream();
      os.write(params.getBytes());
      os.flush();
      if (huc.getResponseCode() != HttpURLConnection.HTTP_OK){
        System.out.println("Codigo de error HTTP: " + huc.getResponseCode());
        return ;
      }
      System.out.println("\nOK");
      huc.disconnect();
    }
    catch(IOException ie){ System.out.println("\nError en el alta\n"); }
  }

  public static void consulta(BufferedReader br){
    try{
      System.out.println("\nIngresa el email del usuario que deseas consultar:");
      String email = br.readLine();

      URL url = new URL("http://" + server_ip + ":8080/Servicio/rest/ws/consulta");
      HttpURLConnection huc = (HttpURLConnection) url.openConnection();
      huc.setDoOutput(true);
      huc.setRequestMethod("POST");
      huc.setRequestProperty("Content-Type","application/x-www-form-urlencoded");

      String params = "email=" + URLEncoder.encode(email,"UTF-8");
      OutputStream os = huc.getOutputStream();
      os.write(params.getBytes());
      os.flush();
      if (huc.getResponseCode() != HttpURLConnection.HTTP_OK){
        System.out.println("Codigo de error HTTP: " + huc.getResponseCode());
        return ;
      }

      BufferedReader br2 = new BufferedReader(new InputStreamReader((huc.getInputStream())));
      String ans;
      Usuario u = null;
      while((ans = br2.readLine()) != null)
        u = (Usuario)j.fromJson(ans,Usuario.class);
      System.out.println(u);
      huc.disconnect();
    }
    catch(IOException ie){ System.out.println("\nError en la consulta\n"); }
  }

  public static void borra(BufferedReader br){
    try{
      System.out.println("\nIngresa el email del usuario que deseas borrar:");
      String email = br.readLine();

      URL url = new URL("http://" + server_ip + ":8080/Servicio/rest/ws/borra");
      HttpURLConnection huc = (HttpURLConnection) url.openConnection();
      huc.setDoOutput(true);
      huc.setRequestMethod("POST");
      huc.setRequestProperty("Content-Type","application/x-www-form-urlencoded");

      String params = "email=" + URLEncoder.encode(email,"UTF-8");
      OutputStream os = huc.getOutputStream();
      os.write(params.getBytes());
      os.flush();
      if (huc.getResponseCode() != HttpURLConnection.HTTP_OK){
        System.out.println("Codigo de error HTTP: " + huc.getResponseCode());
        return ;
      }
      System.out.println("\nOK");
      huc.disconnect();
    }
    catch(IOException ie){ System.out.println("\nError al borrar\n"); }
  }

  public static void borra_todo(){
    try{
      URL url = new URL("http://" + server_ip + ":8080/Servicio/rest/ws/borratodo");
      HttpURLConnection huc = (HttpURLConnection) url.openConnection();
      huc.setDoOutput(true);
      huc.setRequestMethod("POST");
      huc.setRequestProperty("Content-Type","application/x-www-form-urlencoded");

      String params = "empty=";
      OutputStream os = huc.getOutputStream();
      os.write(params.getBytes());
      os.flush();
      if (huc.getResponseCode() != HttpURLConnection.HTTP_OK){
        System.out.println("Codigo de error HTTP: " + huc.getResponseCode());
        return ;
      }
      System.out.println("\nOK");
      huc.disconnect();
    }
    catch(IOException ie){ System.out.println("\nError al borrar\n"); }
  }

  public static void main(String [] args) throws IOException{
    InputStreamReader isr = new InputStreamReader(System.in);
    BufferedReader br = new BufferedReader(isr);
    j = new GsonBuilder().setDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS").create();
    boolean exec = true;
    while(exec){
      menu();
      String opt = br.readLine();
      switch(opt){
        case "a":
          alta(br);
          break;
        case "b":
          consulta(br);
          break;
        case "c":
          borra(br);
          break;
        case "d":
          borra_todo();
          break;
        case "e":
          exec = false;
          break;
        default:
          System.out.println("\nOpción no válida\n");
      }
    }
  }

}
