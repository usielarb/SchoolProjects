import java.net.Socket;
import java.net.ServerSocket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;

class Servidorwritedouble
{
  // lee del DataInputStream todos los bytes requeridos

  static void read(DataInputStream f,byte[] b,int posicion,int longitud) throws Exception
  {
    while (longitud > 0)
    {
      int n = f.read(b,posicion,longitud);
      posicion += n;
      longitud -= n;
    }
  }

  public static void main(String[] args) throws Exception
  {
    ServerSocket servidor = new ServerSocket(50000);

    Socket conexion = servidor.accept();

    DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
    DataInputStream entrada = new DataInputStream(conexion.getInputStream());

    // recibe un entero de 32 bits
    int n = entrada.readInt();
    System.out.println(n);

    // recibe un numero punto flotante
    double x = entrada.readDouble();
    System.out.println(x);
    
    long ms = System.currentTimeMillis();
    // read(entrada,a,0,64);
    //ByteBuffer b = ByteBuffer.wrap(a);
    double y;
    for (int i = 0; i < 10000; i++)
    {
      //System.out.println(entrada.readDouble());
       y = entrada.readDouble();
       //System.out.println(y);    
    }
    ms = System.currentTimeMillis() - ms;
    System.out.println(ms);
    salida.close();
    entrada.close();
    conexion.close();
  }
}
