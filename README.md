# divisionPuntoFloat
Simulación de división en punto flotante IEEE 754 en C++. Descompone float en signo, exponente y significando, realiza la operación binaria paso a paso y muestra el proceso completo, incluyendo normalización, overflow y underflow. Ideal para fines educativos.

# División en Punto Flotante

Este repositorio contiene una implementación en **C/C++** de la división entre dos números en punto flotante (`float`) de 32 bits, siguiendo el estándar IEEE 754. El algoritmo separa los componentes binarios del número (signo, exponente y significando), realiza la operación bit a bit y ensambla el resultado final.

## Características

- Entrada de dos números en `float`.
- Separación de bits: signo, exponente y significando.
- Resta de exponentes en representación sesgada (biased).
- División de significandos.
- Normalización, redondeo y ensamblado final.
- Verificación contra el resultado nativo (`/`) de C/C++.
- Visualización de los bits de entrada y salida.

![image](https://github.com/user-attachments/assets/737fa817-1d7a-4fdb-b7a6-e8185c631e7e)

## Ejemplo de ejecución

Ingrese dividendo (a): 15.5
Ingrese divisor (b): 2.0

--- INICIO DE DIVISIÓN: 15.5 / 2 ---

Descomposición de X = 15.5:
Signo [1 bit]: 0
Exponente [8 bits]: 10000011 (valor decimal: 131)
Significando [23 bits]: 11110000 00000000 00000000 (valor decimal: 7864320)
-----------------------------------------------------------------

Descomposición de Y = 2:
Signo [1 bit]: 0
Exponente [8 bits]: 10000000 (valor decimal: 128)
Significando [23 bits]: 00000000 00000000 00000000 (valor decimal: 0)
-----------------------------------------------------------------

Signo resultante: 0 (XOR de los signos)
Resta de exponentes: 131 - 128 + 127 = 130

Significando X con 1 implícito: 16711680
Significando Y con 1 implícito: 8388608
División de significandos: 16711680

Normalizando: desplazamiento a la derecha

Resultado Z:
Signo [1 bit]: 0
Exponente [8 bits]: 10000010 (valor decimal: 130)
Significando [23 bits]: 11100000 00000000 00000000 (valor decimal: 7340032)
-----------------------------------------------------------------

Resultado decimal: 7.75
--- FIN DE LA DIVISIÓN ---

Comparación de resultados:
Resultado emulado:      7.75
Resultado nativo (C++): 7.75
¡Los resultados son idénticos!
