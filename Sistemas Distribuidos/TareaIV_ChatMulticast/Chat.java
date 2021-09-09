import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
//import java.nio.ByteBuffer;
import java.net.MulticastSocket;
import java.io.BufferedReader;
import java.io.InputStreamReader;

class Chat
{
    static void envia_mensaje(byte[] buffer,String ip,int puerto) throws IOException
  {
    DatagramSocket socket = new DatagramSocket();
    InetAddress grupo = InetAddress.getByName(ip);
    DatagramPacket paquete = new DatagramPacket(buffer,buffer.length,grupo,puerto);
    socket.send(paquete);
    socket.close();
  }

  static byte[] recibe_mensaje(MulticastSocket socket,int longitud) throws IOException
  {
    byte[] buffer = new byte[longitud];
    DatagramPacket paquete = new DatagramPacket(buffer,buffer.length);
    socket.receive(paquete);
    return buffer;
  }




  static class Worker extends Thread
  {
    public void run()
    {
      try{
        InetAddress grupo = InetAddress.getByName("230.0.0.0");
    MulticastSocket socket = new MulticastSocket(50000);
    socket.joinGroup(grupo);

    System.out.println("Esperando datagrama...");

    /* recibe una string */
    while(true)
    {
      //System.out.println(" ");
      //byte[] n = recibe_mensaje(socket,1500);
      //System.out.print(new String(n,"UTF-8") + " escribio: ");
      byte[] a = recibe_mensaje(socket,1500);
      System.out.println(new String(a,"UTF-8"));

    }
      }
      catch(Exception e)
      {
        System.err.println("Exeption: "+ e.getClass() +  " with " + e);
      }
     // En un ciclo infinito se recibirán los mensajes enviados al grupo 
     // 230.0.0.0 asocket.close(); través del puerto 50000 y se desplegarán en la pantalla.
    }
  }
  public static void main(String[] args) throws Exception
  {
    Worker w = new Worker();
    w.start();

    String nombre = args[0];
    String  buffer;
    BufferedReader b = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("Bienvenido " + nombre);
    while(true)
    {
      System.out.println("Escribe el mensaje: ");
        buffer = b.readLine();
        //System.out.println(nombre + " escribio: " + buffer);
        //envia_mensaje(nombre.getBytes(), "230.0.0.0",50000);
        buffer = nombre + ": " +  buffer;
        envia_mensaje(buffer.getBytes(), "230.0.0.0",50000);
    }
    // En un ciclo infinito se leerá los mensajes del teclado y se enviarán
    // al grupo 230.0.0.0 a través del puerto 50000.
  }
}