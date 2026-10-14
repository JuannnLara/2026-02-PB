// =====================================================================
//  plataforma.h  --  CONTRATO OFICIAL del Parcial II (Plataforma Online)
//
//  * Este archivo lo entrega el profesor. LOS ESTUDIANTES NO LO MODIFICAN.
//    El autocalificador lo sobrescribe con la versión oficial antes de compilar.
//  * Implementen TODAS las funciones en plataforma.cpp.
//  * main.cpp contiene el menu (unico lugar donde se usa cin/cout).
//    Las funciones de este archivo NO deben imprimir ni leer de consola.
//  * Estandar: C++17.
// =====================================================================
#pragma once

#include <string>
#include <vector>

// ---------------------------------------------------------------------
//  Estructuras (nombres de campo sin tildes ni ñ a proposito)
// ---------------------------------------------------------------------
struct Usuario {
    int idUsuario;
    std::string nombre;
    std::string correoElectronico;
    std::string contrasena;
    std::string direccion;
    std::string metodoDePago;
};

struct Producto {
    int idProducto;
    std::string nombre;
    std::string descripcion;
    double precio;
    int stock;
};

// En Comentario, `producto` y `usuario` guardan el NOMBRE (texto), tal como
// aparece en la tabla del enunciado ("Laptop", "Juan Pérez").
struct Comentario {
    int idComentario;
    std::string producto;
    std::string usuario;
    std::string comentario;
    std::string fecha;  // formato dd/mm/yyyy, por ejemplo "1/05/2025" o "10/05/2025"
};

struct CarritoDeCompras {
    int idCarrito = 0;
    Usuario usuario{};                // el dueño del carrito
    std::vector<Producto> productos;  // un elemento por unidad agregada
    double subtotal = 0.0;
    double impuestos = 0.0;
};

// Estas dos estructuras estan en el enunciado; no se evaluan en este parcial.
struct Categoria {
    int idCategoria;
    std::string nombre;
};

struct OrdenDeCompra {
    int idOrden = 0;
    std::vector<Producto> productos;
    double subtotal = 0.0;
    double impuestos = 0.0;
    double envio = 0.0;
    double total = 0.0;
};

// ---------------------------------------------------------------------
//  Constantes del parcial
// ---------------------------------------------------------------------
constexpr double TASA_IVA = 0.19;       // impuestos = subtotal * TASA_IVA
constexpr int UMBRAL_STOCK_BAJO = 15;   // "por debajo de 15 unidades"

enum ResultadoCarrito {
    CARRITO_OK = 0,
    CARRITO_PRODUCTO_INVALIDO = 1,  // no existe un producto con ese id
    CARRITO_SIN_STOCK = 2           // el producto existe pero stock == 0
};

// ---------------------------------------------------------------------
//  a) Inicializacion (0.5 pts)
//  Devuelven los datos EXACTOS de las tablas del enunciado, en el mismo
//  orden (usuarios 1..5, productos 1..50, comentarios 1..50).
// ---------------------------------------------------------------------
std::vector<Usuario> cargarUsuarios();
std::vector<Producto> cargarProductos();
std::vector<Comentario> cargarComentarios();

// ---------------------------------------------------------------------
//  b) Iniciar sesion (0.5 pts)
//  Busca en `usuarios` un usuario cuyo correoElectronico Y contrasena
//  coincidan EXACTAMENTE (distingue mayusculas y minusculas).
//  - Si lo encuentra: copia el usuario completo en `usuarioOut` y devuelve true.
//  - Si no: devuelve false (no hace falta tocar `usuarioOut`).
//  main.cpp es quien imprime "Usuario invalido" cuando devuelve false.
// ---------------------------------------------------------------------
bool iniciarSesion(const std::vector<Usuario>& usuarios,
                   const std::string& correo,
                   const std::string& contrasena,
                   Usuario& usuarioOut);

// ---------------------------------------------------------------------
//  c) Menu (1.5 pts: 0.5 por cada consulta)
// ---------------------------------------------------------------------

// i. Productos con stock ESTRICTAMENTE menor que `umbral` (por defecto 15),
//    en el mismo orden del inventario. No modifica nada.
std::vector<Producto> productosBajoStock(const std::vector<Producto>& productos,
                                         int umbral = UMBRAL_STOCK_BAJO);

// ii. Comentarios cuya fecha sea IGUAL O POSTERIOR a `fecha` (formato dd/mm/yyyy;
//     el dia puede venir con o sin cero inicial: "9/06/2025" y "09/06/2025").
//     Mismo orden de la lista original. Si `fecha` no es una fecha valida,
//     devuelve un vector vacio. OJO: comparar las fechas como texto NO funciona.
std::vector<Comentario> comentariosDesde(const std::vector<Comentario>& comentarios,
                                         const std::string& fecha);

// iii. Una cadena por usuario (mismo orden). Cada cadena debe contener el
//      NOMBRE EN MAYUSCULAS y NO debe contener la contrasena.
//      Formato sugerido: "1 | JUAN PÉREZ | juan.perez@email.com | Carrera 45 #10-20 | Tarjeta de crédito"
//      (las vocales con tilde pueden quedar como estan o pasarse a mayuscula).
std::vector<std::string> listarUsuariosFormateados(const std::vector<Usuario>& usuarios);

// ---------------------------------------------------------------------
//  d) Carrito de compras (1.5 pts)
// ---------------------------------------------------------------------

// Id para un carrito nuevo: (id del ULTIMO carrito del vector) + 1; si el
// vector esta vacio devuelve 1.
int siguienteIdCarrito(const std::vector<CarritoDeCompras>& carritos);

// Agrega UNA unidad del producto `idProducto` al carrito de `usuario`:
//  1. Si el producto no existe              -> CARRITO_PRODUCTO_INVALIDO (no cambia nada).
//  2. Si su stock es 0                      -> CARRITO_SIN_STOCK         (no cambia nada,
//                                              no se crea carrito, el stock no queda negativo).
//  3. Si el usuario aun no tiene carrito en `carritos`, se crea uno nuevo con
//     idCarrito = siguienteIdCarrito(carritos). Cada usuario tiene UN solo carrito:
//     las siguientes llamadas del mismo usuario reutilizan ese carrito.
//  4. Se descuenta 1 del stock del producto EN EL VECTOR `productos` ORIGINAL.
//  5. Se agrega el producto a carrito.productos (un elemento por unidad).
//  6. Se actualiza carrito.subtotal (suma de precios) y
//     carrito.impuestos = subtotal * TASA_IVA.
//  Devuelve CARRITO_OK si se agrego.
ResultadoCarrito agregarAlCarrito(std::vector<CarritoDeCompras>& carritos,
                                  std::vector<Producto>& productos,
                                  const Usuario& usuario,
                                  int idProducto);

// ---------------------------------------------------------------------
//  e) Listar productos del carrito (1.0 pts)
//  Devuelve los productos del carrito con ese idCarrito, en el orden en que
//  se agregaron. Si no existe ese carrito, devuelve un vector vacio.
// ---------------------------------------------------------------------
std::vector<Producto> listarProductosCarrito(const std::vector<CarritoDeCompras>& carritos,
                                             int idCarrito);
