public class Usuario{

  String email;
  String nombre;
  String apellido_paterno;
  String apellido_materno;
  String fecha_nacimiento;
  String telefono;
  String genero;
  byte[] foto;

  public Usuario(String email, String nombre, String apellido_paterno, String apellido_materno, String fecha_nacimiento, String telefono, String genero, byte[] foto){
    this.email = email;
    this.nombre = nombre;
    this.apellido_paterno = apellido_paterno;
    this.apellido_materno = apellido_materno;
    this.fecha_nacimiento = fecha_nacimiento;
    this.telefono = telefono;
    this.genero = genero;
    this.foto = foto;
  }

  public String toString(){
    return "\nEmail = " + email + "\nNombre = " + nombre + "\nApellido Paterno = " + apellido_paterno +
           "\nApellido Materno = " + apellido_materno + "\nFecha de Nacimiento = " + fecha_nacimiento +
           "\nTelefono = " + telefono + "\nGenero = " + genero;
  }

}
