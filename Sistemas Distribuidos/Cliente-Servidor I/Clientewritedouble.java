import java.net.Socket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;

class Clientewritedouble
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
    Socket conexion = new Socket("localhost",50000);

    DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
    DataInputStream entrada = new DataInputStream(conexion.getInputStream());

    // enva un entero de 32 bits
    salida.writeInt(123);

    // envia un numero punto flotante
    salida.writeDouble(1234567890.1234567890);
    double i;
    long ms = System.currentTimeMillis();
    for(i=0;i<10000;i++)
    {
      salida.writeDouble(i);
      //System.out.println(i);
    }
    //   b.putDouble(i);
    // byte[] a = b.array();
    // salida.write(a);
    ms = System.currentTimeMillis() - ms;
    System.out.println(ms);

    salida.close();
    entrada.close();
    conexion.close();    
  }
}
