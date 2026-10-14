# Anexo técnico al Parcial II (pegar al final del enunciado)

## 1. Qué se entrega
- Una carpeta con **`plataforma.cpp`** (toda la lógica) y **`main.cpp`** (login y menú; único lugar con `cin`/`cout`).
- **No modifiquen `plataforma.h`**: lo entrega el profesor y se usa siempre la versión oficial al calificar.
- C++17. Los nombres de funciones, parámetros y campos son exactamente los de `plataforma.h`.
- Las funciones de `plataforma.cpp` **no leen ni imprimen** en consola.
- Al definir `productosBajoStock` en el .cpp **no repitan** el valor por defecto del parámetro.

## 2. Aclaraciones al enunciado
| Tema | Decisión |
|---|---|
| Iniciar sesión | Se busca por **correo y contraseña** (distingue mayúsculas). Si no existe: `Usuario invalido` |
| Comentario | `producto` y `usuario` son el **nombre** (texto), como en la tabla |
| Carrito | `usuario` es un `Usuario` completo. **Un carrito por usuario**; `idCarrito` = id del último carrito + 1 (el primero es 1) |
| Agregar al carrito | Cada llamada agrega **una unidad**; descuenta 1 del stock en el vector original; sin stock no se agrega |
| Impuestos | `subtotal` = suma de precios; `impuestos` = subtotal × 0.19 |
| Stock bajo | Estrictamente menor que 15 (stock 15 no entra) |
| Fechas | Formato `dd/mm/yyyy` (`1/05/2025` o `01/05/2025`). "De una fecha en adelante" es **inclusivo**. Comparar fechas como texto es incorrecto |
| Listar usuarios | Nombre en MAYÚSCULA y sin contraseña; las vocales con tilde pueden quedar como están |
| Estructuras | `OrdenDeCompra` y `Categoria` se declaran pero no se evalúan |

## 3. Protocolo del programa (para la verificación automática)
1. Pide correo y contraseña (`cin >>`). Si fallan: imprime `Usuario invalido` y termina.
2. Menú en ciclo hasta elegir `0`:

| Opción | Acción | Entrada adicional |
|---|---|---|
| 1 | Listar productos con stock < 15 | — |
| 2 | Comentarios desde una fecha | fecha `dd/mm/yyyy` |
| 3 | Listar usuarios | — |
| 4 | Adicionar producto al carrito | id del producto |
| 5 | Listar productos del carrito (con subtotal e impuestos) | — |
| 0 | Salir | — |

3. El programa no debe quedarse en ciclo infinito ante texto no numérico o fin de entrada.

## 4. Calificación
| Bloque | Puntos |
|---|---|
| Inicialización | 0.5 |
| Iniciar sesión | 0.5 |
| Listar productos (stock < 15) | 0.5 |
| Comentarios desde una fecha | 0.5 |
| Listar usuarios | 0.5 |
| Adicionar al carrito | 1.5 |
| Listar productos del carrito | 1.0 |

Si no compila con `g++ -std=c++17`, la nota automática es 0.
