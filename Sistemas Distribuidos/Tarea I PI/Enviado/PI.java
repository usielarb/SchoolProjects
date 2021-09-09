import java.net.Socket;
import java.net.ServerSocket;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.lang.Thread;
import java.nio.ByteBuffer;

import jdk.dynalink.beans.StaticClass;

class PI
{
  static Object lock = new Object();
  static double pi = 0;
  
  static class Worker extends Thread{
    Socket conexion;
    Worker(Socket conexion)
    {
      this.conexion = conexion;
    }
    public void run()
    {
      // Algoritmo 1
      try{
        DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
        DataInputStream entrada = new DataInputStream(conexion.getInputStream());
        double x;
        x = entrada.readDouble();
        synchronized(lock)
        {
          pi = x +  pi;
        }
        salida.close();
        entrada.close();
        conexion.close();
      }
      catch (Exception e)
      {
        System.out.println("Error, catch 1");
      }
    }
  }
  public static void main(String[] args) throws Exception
  {
    if (args.length != 1)
    {
      System.err.println("Uso:");
      System.err.println("java PI <nodo>");
      System.exit(0);
    }
    int nodo = Integer.valueOf(args[0]);
    if (nodo == 0)
    {
      // Algoritmo 2
      ServerSocket servidor = new ServerSocket(50000);
      Worker [] w = new Worker[3];
      int i = 0;
        for(;;)
        {
            if (i==3)
                break;
            Socket conexion;
            conexion = servidor.accept();
            w[i] = new Worker(conexion);
            w[i].start();
            i++;
        }
        double suma = 0;
        i = 0;
        
        for (;;)
        {
            if (i == 10000000)
                break;
            suma = 4.0/(8*i+1)+ suma;
            i++;
        }

        synchronized(lock){
            System.out. println(suma + " " +  pi);
            pi = suma + pi;
        }
        i=0;
        for(;;)
        {
            if (i==3)
                break;
            w[i].join();
            i++;
        }
        System.out.println("Valor de PI: " + pi);
    }
    else
    {
      // Algoritmo 3
      Socket conexion = null;
      for(;;)
      try
      {
    	  conexion = new Socket("localhost",50000);
        break;
      }
      catch (Exception e)
      {
        Thread.sleep(100);
      }
      DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
      DataInputStream entrada = new DataInputStream(conexion.getInputStream());
      double suma  = 0;
      int i =0 ;
      for(;;)
      {
          if (i == 10000000)
            break;
          suma = 4.0/(8*i+2*(nodo-1)+3)+suma;
          i++;
      }
      System.out. println(suma + " " +  nodo);
      suma = nodo%2==0?suma:-suma;
      System.out. println(suma + " " +  nodo);
      salida.writeDouble(suma);
      salida.close();
      entrada.close();
      conexion.close();
    }
  }
}