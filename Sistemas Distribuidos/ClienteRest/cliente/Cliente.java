public import java.io.BufferedReader;
import java.util.Scanner;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import com.google.gson.reflect.TypeToken;

public class Cliente
{
    static String IP="157.55.183.76";
    public static void main(String[] args)throws Exception{
        
        Scanner input = new Scanner (System.in); 
        char opcion;


        while(true)
        {


            System.out.println("\t\t MENU");
            System.out.println("\ta. Alta usuario");
            System.out.println("\tb. Consulta usuario");
            System.out.println("\tc. Borra usuario");
            System.out.println("\td. Borra todos los usuarios");
            System.out.println("\te. Salir\n\n");
            System.out.print("Opcion:_");
            opcion = input.next().charAt(0); 
            
            

            switch(opcion)
            {
                case 'a': alta();break;
                case 'b': consulta();break;
                case 'c': borrar();break;
                case 'd': borrarTodo();break;
                case 'e': System.exit(0);break;
                default: System.out.println("Opcion invalida, intente de nuevo\n");
            }
            
        }
        
    }

    public static void alta() throws Exception{
        String email, nombre, apellidoP, apellidoM, fechaN, tel, genero;

        Scanner input = new Scanner (System.in);
        
        System.out.println("ALTA USUARIO");
        System.out.print("\tEmail : ");
        email = input.nextLine();

        System.out.print("\tNombre : ");
        nombre = input.nextLine();

        System.out.print("\tApellido paterno :");
        apellidoP = input.nextLine();

        System.out.print("\tApellido materno : ");
        apellidoM = input.nextLine();

        System.out.print("\tFecha nacimiento (YYYY-MM-DD) :");
        fechaN = input.nextLine();

        System.out.print("\tTelefono : ");
        tel = input.nextLine();

        System.out.print("\tGenermo (M/F) : ");
        genero = input.nextLine();
        input.close();

        Usuario nUsuario = new Usuario(email,nombre,apellidoP,apellidoM,fechaN,tel,genero);
        String json = Conectar.serializeJson(nUsuario);
        String respuesta = Conectar.opciones("alta","usuario",json,IP);
        if(respuesta.equals(""))System.out.print("OK");
    }

    public static void consulta( )throws Exception{
        Scanner input = new Scanner (System.in);
        System.out.println("COSNULTA");
        System.out.print("\tEmail : ");
        String email = input.nextLine();
        
        String respuesta = Conectar.opciones("consulta","email",email,IP);
        Usuario usuario = Conectar.deserializeJson(respuesta,new TypeToken<Usuario>(){}.getType());
        usuario.mostrar();
    }

    public static void borrar( )throws Exception{
        Scanner input = new Scanner (System.in);
        System.out.println("BORRAR USUARIO");
        System.out.print("\tEmail : ");
        String email = input.nextLine();

        String respuesta = Conectar.opciones("borra","email",email,IP);
        if(respuesta.equals(""))System.out.println("OK");
        input.close();
    }

    public static void borrarTodo( )throws Exception{
        Scanner input = new Scanner (System.in);
        System.out.println("BORRAR USUARIOS");

        String respuesta = Conectar.opciones("borratodo","","",IP);
        if(respuesta.equals(""))System.out.println("OK");
        input.close();
    }
}class Cliente2 {
    
}
