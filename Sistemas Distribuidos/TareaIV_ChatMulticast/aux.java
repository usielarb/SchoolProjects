public class aux {
    
}
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;

public class ServidorMulticast
{
  static void envia_mensaje(byte[] buffer,String ip,int puerto) throws IOException
  {
    DatagramSocket socket = new DatagramSocket();
    InetAddress grupo = InetAddress.getByName(ip);
    DatagramPacket paquete = new DatagramPacket(buffer,buffer.length,grupo,puerto);
    socket.send(paquete);
    socket.close();
  }

  public static void main(String[] args) throws Exception
  {
    /* envia una string */
    envia_mensaje("hola".getBytes(),"230.0.0.0",50000);

    /* envia 5 doubles */
    ByteBuffer b = ByteBuffer.allocate(5*8);
    b.putDouble(1.1);
    b.putDouble(1.2);
    b.putDouble(1.3);
    b.putDouble(1.4);
    b.putDouble(1.5);
    envia_mensaje(b.array(),"230.0.0.0",50000);
  }
}

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.nio.ByteBuffer;

public class ClienteMulticast
{
  static byte[] recibe_mensaje(MulticastSocket socket,int longitud) throws IOException
  {
    byte[] buffer = new byte[longitud];
    DatagramPacket paquete = new DatagramPacket(buffer,buffer.length);
    socket.receive(paquete);
    return buffer;
  }

  public static void main(String[] args) throws Exception
  {
    InetAddress grupo = InetAddress.getByName("230.0.0.0");
    MulticastSocket socket = new MulticastSocket(50000);
    socket.joinGroup(grupo);

    System.out.println("Esperando datagrama...");

    /* recibe una string */
    byte[] a = recibe_mensaje(socket,4);
    System.out.println(new String(a,"UTF-8"));

    /* recibe 5 doubles */
    byte[] buffer = recibe_mensaje(socket,5*8);
    ByteBuffer b = ByteBuffer.wrap(buffer);

    for (int i = 0; i < 5; i++)
      System.out.println(b.getDouble());

    socket.leaveGroup(grupo);
    socket.close();
  }
}
