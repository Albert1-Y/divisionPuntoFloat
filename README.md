# divisionPuntoFloat

## Descripción
Implementación detallada de la división en punto flotante IEEE 754 en C++. Este programa simula manualmente el proceso que realiza la CPU al dividir números de punto flotante, descomponiendo cada número en sus componentes binarios (signo, exponente y significando), realizando las operaciones correspondientes y ensamblando el resultado final.

## Características
- Entrada de dos números en formato `float` de 32 bits
- Descomposición completa en componentes IEEE 754:
  - 1 bit de signo
  - 8 bits de exponente
  - 23 bits de significando
- Visualización bit a bit de cada componente
- Implementación detallada del algoritmo conforme al estándar IEEE 754:
  - Casos especiales (división por cero, cero dividido por cualquier número)
  - Cálculo del signo resultante mediante XOR
  - Resta de exponentes en representación sesgada (biased representation)
  - Detección de overflow/underflow de exponente
  - División de significandos con precisión extendida
  - Normalización y redondeo del resultado
- Comparación con el resultado nativo de C++
- Salida formateada para visualización educativa

## Diagrama de flujo del algoritmo
![Diagrama de flujo de división en punto flotante](https://github.com/user-attachments/assets/737fa817-1d7a-4fdb-b7a6-e8185c631e7e)

## Ejemplo de ejecución

```
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
```
