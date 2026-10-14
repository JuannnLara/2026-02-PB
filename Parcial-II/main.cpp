// =====================================================================
//  main.cpp -- PLANTILLA. Unico lugar donde se usa cin/cout.
//  Protocolo de entrada/salida: ver anexo_enunciado.md
//    1) Pedir correo y contrasena (cin >> ...). Si iniciarSesion falla -> imprimir
//       "Usuario invalido" y terminar.
//    2) Menu en ciclo hasta elegir 0:
//       1 Listar productos (stock < 15)      4 Adicionar producto al carrito (pide id)
//       2 Comentarios desde una fecha (pide fecha dd/mm/yyyy)   5 Listar productos del carrito
//       3 Listar usuarios                    0 Salir
// =====================================================================
#include <iostream>
#include <string>
#include <vector>

#include "plataforma.h"

using namespace std;

void mostrarMenuVisual() {
    cout << "------TIENDA ONLINE - MENU------\n" << endl;
    cout << "1. Listar productos con stock menor a 15" << endl;
    cout << "2. Comentarios desde una fecha" << endl;
    cout << "3. Listar usuarios" << endl;
    cout << "4. Adicionar producto al carrito" << endl;
    cout << "5. Listar productos del carrito" << endl;
    cout << "0. Salir" << endl;
    cout << "\n" << endl;
    cout << "Elija una opcion: " << flush;
}

void pausar() {
    cout << "\nPresione enter para continuar" << flush;
    string dummy;
    getline(cin >> ws, dummy);
}

int main() {
    vector<Usuario> usuarios = cargarUsuarios();
    vector<Producto> productos = cargarProductos();
    vector<Comentario> comentarios = cargarComentarios();
    vector<CarritoDeCompras> carritos;

    string correo, contrasena;
    
    // Inicio de sesión interactivo
    cout << "INICIO DE SESION" << endl;
    cout << "Correo electronico: " << flush;
    if (!(cin >> correo)) return 0;
    
    cout << "Contrasena: " << flush;
    if (!(cin >> contrasena)) return 0;

    Usuario usuarioLogueado;
    if (!iniciarSesion(usuarios, correo, contrasena, usuarioLogueado)) {
        cout << "Usuario invalido" << endl;
        return 0;
    }

    cout << "\n¡Bienvenido, " << usuarioLogueado.nombre << "!" << endl;

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenuVisual();
        if (!(cin >> opcion)) {
            break;
        }

        if (opcion == 1) {
            vector<Producto> bajos = productosBajoStock(productos);
            cout << "\nProductos con stock < 15" << endl;
            for (const auto& p : bajos) {
                cout << "ID: " << p.idProducto << " | " << p.nombre << " | Stock: " << p.stock << " | Precio: $" << p.precio << endl;
            }
            pausar();
        } 
        else if (opcion == 2) {
            string fecha;
            cout << "Introduzca la fecha de consulta (ej. 1/05/2025): " << flush;
            if (cin >> fecha) {
                vector<Comentario> comps = comentariosDesde(comentarios, fecha);
                cout << "\n--- Comentarios (total: " << comps.size() << ") ---" << endl;
                for (const auto& c : comps) {
                    cout << "[" << c.fecha << "] " << c.producto << " (" << c.usuario << "): " << c.comentario << endl;
                }
            }
            pausar();
        } 
        else if (opcion == 3) {
            vector<string> form = listarUsuariosFormateados(usuarios);
            cout << "\n---Listado de usuarios---" << endl;
            for (const auto& s : form) {
                cout << s << endl;
            }
            pausar();
        } 
        else if (opcion == 4) {
            int idProd;
            cout << "Introduzca el ID del producto que desea agregar al carrito (1-50): " << flush;
            if (cin >> idProd) {
                ResultadoCarrito res = agregarAlCarrito(carritos, productos, usuarioLogueado, idProd);
                if (res == CARRITO_OK) {
                    cout << "¡Producto agregado al carrito con exito!" << endl;
                } else if (res == CARRITO_PRODUCTO_INVALIDO) {
                    cout << "Error 404: El ID del producto no existe." << endl;
                } else if (res == CARRITO_SIN_STOCK) {
                    cout << "Error 409: Lo sentimos, el producto no tiene stock disponible." << endl;
                }
            }
            pausar();
        } 
        else if (opcion == 5) {
            int idCarritoActual = -1;
            for (const auto& c : carritos) {
                if (c.usuario.idUsuario == usuarioLogueado.idUsuario) {
                    idCarritoActual = c.idCarrito;
                    break;
                }
            }
            if (idCarritoActual != -1) {
                vector<Producto> prodsCarrito = listarProductosCarrito(carritos, idCarritoActual);
                double sub = 0.0, imp = 0.0;
                for (const auto& c : carritos) {
                    if (c.idCarrito == idCarritoActual) {
                        sub = c.subtotal;
                        imp = c.impuestos;
                        break;
                    }
                }
                cout << "\n--- Carrito de compras (ID: " << idCarritoActual << ") ---" << endl;
                for (size_t i = 0; i < prodsCarrito.size(); ++i) {
                    cout << i + 1 << ". " << prodsCarrito[i].nombre << " - $" << prodsCarrito[i].precio << endl;
                }
                cout << "------------------------------------------" << endl;
                cout << "Subtotal : $" << sub << endl;
                cout << "Impuestos (19% IVA): $" << imp << endl;
                cout << "Total a pagar: $" << (sub + imp) << endl;
            } else {
                cout << "\nSu carrito de compras esta actualmente vacio." << endl;
            }
            pausar();
        } 
        else if (opcion != 0) {
            cout << "Opcion invalida. Por favor, elija un numero del 0 al 5." << endl;
            pausar();
        }
    }

    cout << "\n¡Gracias por su compra! Saliendo..." << endl;
    return 0;
}
