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
  static int N = 4;
  static int[][] A = new int[N][N];
  static int[][] B = new int[N][N];
  static int[][] C = new int[N][N];

  static void read(DataInputStream f,byte[] b,int posicion,int longitud) throws Exception
  {
    while (longitud > 0)
    {
      int n = f.read(b,posicion,longitud);
      posicion += n;
      longitud -= n;
    }
  }
  
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
        
        int i, j;
        DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
        DataInputStream entrada = new DataInputStream(conexion.getInputStream());
        int nhilo = entrada.readInt();
        byte[] recbir = new byte[4 * N];

        ByteBuffer A1 = ByteBuffer.allocate(N * 4);
        ByteBuffer A2 = ByteBuffer.allocate(N * 4);
        ByteBuffer B1 = ByteBuffer.allocate(N * 4);
        ByteBuffer B2 = ByteBuffer.allocate(N * 4);
          
        for (i = 0; i < N; i++)
          for (j = 0; j < N; j++)
          {
            if (i < N/2){
              A1.putInt(A[i][j]);
              B1.putInt(B[i][j]);
            }
            else
            {
              A2.putInt(A[i][j]);
              B2.putInt(B[i][j]);
            }
          }
          
        byte[] enviarA1 = A1.array();
        byte[] enviarA2 = A2.array();
        byte[] enviarB1 = B1.array();
        byte[] enviarB2 = B2.array();

        switch(nhilo)
        {
          case 1:
          {
            salida.write(enviarA1);
            salida.write(enviarB1);
            read(entrada,recbir, 0, 8 * N);
            ByteBuffer recibido = ByteBuffer.wrap(recbir);
            for (i=0; i<N/2; i++)
            {
              for ( j=0; j<N/2; j++)
              {
                C[i][j] = recibido.getInt(); 
              }
            }
          }
          break;
          case 2:
          {
            salida.write(enviarA1);
            salida.write(enviarB2);
            read(entrada,recbir, 0, 4 * N);
            ByteBuffer recibido = ByteBuffer.wrap(recbir);
            for (i=N/2; i<N; i++)
            {
              for ( j=0; j<N/2; j++)
              {
                C[i][j] = recibido.getInt(); 
              }
            }
          }
          break;
          case 3:
          {
            salida.write(enviarA2);
            salida.write(enviarB1);
            read(entrada,recbir, 0, 4 * N);
            ByteBuffer recibido = ByteBuffer.wrap(recbir);
            for (i=0; i<N/2; i++)
            {
              for ( j=N/2; j<N; j++)
              {
                C[i][j] = recibido.getInt(); 
              }
            }
          }
          break;
        case 4:
          {
            salida.write(enviarA2);
            salida.write(enviarB2);
            read(entrada,recbir, 0, 4 * N);
            ByteBuffer recibido = ByteBuffer.wrap(recbir);
            for (i=N/2; i<N; i++)
            {
              for ( j=N/2; j<N; j++)
              {
                C[i][j] = recibido.getInt(); 
              }
            }
          }
          break;
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
    int i, j;
    if (args.length != 1)
    {
      System.err.println("Uso:");
      System.err.println("java MATRICES <nodo>");
      System.exit(0);
    }
    

    int nodo = Integer.valueOf(args[0]);
    if (nodo == 0)
    {
      
      for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
            {
              A[i][j] = 2 * i - j;
              B[i][j] = i + 2 * j;
              C[i][j] = 0;
            }
      for (i = 0; i < N; i++)
        for (j = 0; j < i; j++)
        {
          int x = B[i][j];
          B[i][j] = B[j][i];
          B[j][i] = x;
        }

        

        
      ServerSocket servidor = new ServerSocket(50000);
      Worker [] w = new Worker[4];
      System.out.println("Prubea");
        for(i=0;i<4; i++)
        {
            Socket conexion;
            conexion = servidor.accept();
            w[i] = new Worker(conexion);
            w[i].start();
            System.out.println("Prubea" + i);
        }
        for(;;)
        {
          if (i==4)
            break;
          w[i].join();
          i++;
        }
      
        //hacer checksum
        //imprimir tiempo rde procesamiento

        

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
      salida.writeInt(nodo);
      int a[][] = new int [N][N/2];
      int b[][] = new int [N][N/2];
      int c[][] = new int [N/2][N/2];
      byte[] auxbyte = new byte[N * 4];
      byte[] auxbyte2 = new byte[N * 4];
      read(entrada,auxbyte, 0, 4 * N);
      ByteBuffer recibido = ByteBuffer.wrap(auxbyte);
      read(entrada,auxbyte2, 0, 4 * N);
            ByteBuffer recibido2 = ByteBuffer.wrap(auxbyte2);
            for (i=0; i<N; i++)
            {
              for ( j=0; j<N/2; j++)
              {
                a[i][j] = recibido.getInt(); 
                b[i][j] = recibido2.getInt(); 
              }
            }
            for (i=0; i<N; i++)
            {
              for ( j=0; j<N/2; j++)
              {
                c[i][j]= a[i][j]* b[i][j];
              }
            }
      
      salida.close();
      entrada.close();
      conexion.close();
    }
  }
}