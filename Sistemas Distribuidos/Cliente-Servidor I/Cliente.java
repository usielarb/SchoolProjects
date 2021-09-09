import java.net.Socket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.nio.ByteBuffer;

class Cliente
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

    // envia una cadena
    salida.write("hola".getBytes());

    // recibe una cadena
    byte[] buffer = new byte[4];
    read(entrada,buffer,0,4);
    System.out.println(new String(buffer,"UTF-8"));

    // envia 5 numeros punto flotante
    ByteBuffer b = ByteBuffer.allocate(10000*64);
    double i;
    long ms = System.currentTimeMillis();
    // b.putDouble(1.1);
    // b.putDouble(1.2);
    // b.putDouble(1.3);
    // b.putDouble(1.4);
    // b.putDouble(1.5);
    // byte[] a = b.array();
    // salida.write(a);
    // System.out.println(ms);
    for(i=0;i<10000;i++)
      b.putDouble(i);
    byte[] a = b.array();
    salida.write(a);
    ms = System.currentTimeMillis() - ms;
    System.out.println(ms);

    salida.close();
    entrada.close();
    conexion.close();    
  }
}
