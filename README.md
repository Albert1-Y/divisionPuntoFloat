# divisionPuntoFloat
Simulación de división en punto flotante IEEE 754 en C++. Descompone float en signo, exponente y significando, realiza la operación binaria paso a paso y muestra el proceso completo, incluyendo normalización, overflow y underflow. Ideal para fines educativos.

# División en Punto Flotante

Implementación en **C/C++** de la división entre dos números `float` de 32 bits, siguiendo el algoritmo del estándar IEEE 754. El programa separa signo, exponente y significando, realiza la operación bit a bit, y reconstruye el resultado en formato flotante.

## Características

- Entrada de dos `float` reales.
- Separación y manejo de componentes binarios.
- Control de `overflow` y `underflow`.
- Comparación con la división nativa (`/`).
- Visualización de patrones de bits (opcional).

Ingrese el primer número: 15.5
Ingrese el segundo número: 2.0

[Entrada]
X = 15.5 -> Signo: 0 | Exponente: 10000011 | Significand: 11110000000000000000000
Y = 2.0  -> Signo: 0 | Exponente: 10000000 | Significand: 00000000000000000000000

[Operación]
Exponente resultado: 10000011 - 10000000 + 01111111 = 10000010
Significand dividido: 11110000000000000000000 ÷ 00000000000000000000000 = ...

[Resultado final]
Z = 7.75
Bits: Signo: 0 | Exponente: 10000010 | Significand: 11100000000000000000000

Verificación con operador nativo: 15.5 / 2.0 = 7.75 ✅
