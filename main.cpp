#include <iostream>
#include <cstdint>
#include <cmath>

using namespace std;

struct FloatIEEE {
    int signo;
    int exponente[8];
    int significando[23];
};

// Función para mostrar los bits de cada componente
void mostrarBits(const FloatIEEE& num) {

    cout << endl; cout << endl;
    cout << "punto flotante: " << num.signo << " " ;
    for (int i = 0; i < 8; i++)
    {
        cout << num.exponente[i];
    }
    cout << " ";
    for (int i = 0; i < 23; i++)
    {
        cout << num.significando[i];
    }


    int exp_decimal = 0;
    for (int i = 0; i < 8; i++) {
        exp_decimal = exp_decimal * 2 + num.exponente[i];
    }
    cout << "\n\n (valor decimal del exponente: " << exp_decimal << ")" << endl;

    uint32_t sig_decimal = 0;
    for (int i = 0; i < 23; i++) {
        sig_decimal = sig_decimal * 2 + num.significando[i];
    }
    cout << "\n\n (valor decimaldel significando: " << sig_decimal << ")" << endl;

    cout << "\n-----------------------------------------------------------------" << endl;
}

FloatIEEE descomponerNumero(float num) {
    FloatIEEE resultado;

    uint32_t bits;
    memcpy(&bits, &num, sizeof(float));

    resultado.signo = (bits >> 31) & 1;

    for (int i = 0; i < 8; i++) {
        resultado.exponente[i] = (bits >> (30 - i)) & 1;
    }

    for (int i = 0; i < 23; i++) {
        resultado.significando[i] = (bits >> (22 - i)) & 1;
    }

    return resultado;
}

int exponenteADecimal(const int exponente[8]) {
    int valor = 0;
    for (int i = 0; i < 8; i++) {
        valor = valor * 2 + exponente[i];
    }
    return valor;
}

void decimalAExponente(int valor, int exponente[8]) {
    for (int i = 7; i >= 0; i--) {
        exponente[i] = valor & 1;
        valor >>= 1;
    }
}

uint32_t significandoADecimal(const int significando[23]) {
    uint32_t valor = 0;
    for (int i = 0; i < 23; i++) {
        valor = valor * 2 + significando[i];
    }
    return valor;
}

void decimalASignificando(uint32_t valor, int significando[23]) {
    for (int i = 22; i >= 0; i--) {
        significando[i] = valor & 1;
        valor >>= 1;
    }
}

float recomponerNumero(const FloatIEEE& componentes) {
    uint32_t bits = 0;

    bits |= static_cast<uint32_t>(componentes.signo) << 31;

    for (int i = 0; i < 8; i++) {
        bits |= static_cast<uint32_t>(componentes.exponente[i]) << (30 - i);
    }

    for (int i = 0; i < 23; i++) {
        bits |= static_cast<uint32_t>(componentes.significando[i]) << (22 - i);
    }

    float resultado;
    memcpy(&resultado, &bits, sizeof(float));
    return resultado;
}

float dividirPuntoFlotante(float x, float y) {
    cout << "\n--- INICIO DE DIVISIÓN: " << x << " / " << y << " ---\n" << endl;

    FloatIEEE X = descomponerNumero(x);
    FloatIEEE Y = descomponerNumero(y);

    cout << "Descomposición de X = " << x << ":" << endl;
    mostrarBits(X);
    cout << "\nDescomposición de Y = " << y << ":" << endl;
    mostrarBits(Y);
    cout << endl;

    FloatIEEE Z;

    // Caso 1: X = 0
    if (x == 0.0f) {
        cout << "X es 0, asignando Z = 0" << endl;
        Z.signo = 0;
        for (int i = 0; i < 8; i++) Z.exponente[i] = 0;
        for (int i = 0; i < 23; i++) Z.significando[i] = 0;
        return recomponerNumero(Z);
    }

    // Caso 2: Y = 0
    if (y == 0.0f) {
        cout << "Y es 0, asignando Z = infinito" << endl;
        Z.signo = X.signo;
        for (int i = 0; i < 8; i++) Z.exponente[i] = 1;  // Todos 1s = 255 = infinito
        for (int i = 0; i < 23; i++) Z.significando[i] = 0;
        return recomponerNumero(Z);
    }

    // Caso 3: Operación normal

    Z.signo = X.signo ^ Y.signo;
    cout << "Signo resultante: " << Z.signo << " (XOR de los signos)" << endl;

    int exp_X = exponenteADecimal(X.exponente);
    int exp_Y = exponenteADecimal(Y.exponente);

    int exp_resultado = exp_X - exp_Y + 127;
    cout << "Resta de exponentes: " << exp_X << " - " << exp_Y << " + 127 = " << exp_resultado << endl;

    // overflow del exponente
    if (exp_resultado >= 255)
    {
        cout << "Detectado overflow del exponente, reportando infinito" << endl;
        for (int i = 0; i < 8; i++) Z.exponente[i] = 1;
        for (int i = 0; i < 23; i++) Z.significando[i] = 0;
        return recomponerNumero(Z);
    }

    // underflow del exponente
    if (exp_resultado <= 0)
    {
        cout << "Detectado underflow del exponente, reportando 0" << endl;
        for (int i = 0; i < 8; i++) Z.exponente[i] = 0;
        for (int i = 0; i < 23; i++) Z.significando[i] = 0;
        return recomponerNumero(Z);
    }

    // Dividir significandos
    uint32_t sig_X_decimal = significandoADecimal(X.significando) | 0x800000; 
    uint32_t sig_Y_decimal = significandoADecimal(Y.significando) | 0x800000;

    cout << "Significando X con 1 implícito: " << sig_X_decimal << endl;
    cout << "Significando Y con 1 implícito: " << sig_Y_decimal << endl;

    // División de significandos
    uint64_t numerador = static_cast<uint64_t>(sig_X_decimal) << 23;
    uint32_t sig_resultado = static_cast<uint32_t>(numerador / sig_Y_decimal);

    cout << "División de significandos: " << sig_resultado << endl;

    if (sig_resultado & 0x1000000) {
        cout << "Normalizando: desplazamiento a la derecha" << endl;
        sig_resultado >>= 1;
        exp_resultado++;

        if (exp_resultado >= 255) {
            cout << "Overflow después de normalización, reportando infinito" << endl;
            for (int i = 0; i < 8; i++) Z.exponente[i] = 1;
            for (int i = 0; i < 23; i++) Z.significando[i] = 0;
            return recomponerNumero(Z);
        }
    }

    // resultado del exponente a bits
    decimalAExponente(exp_resultado, Z.exponente);

    sig_resultado &= 0x7FFFFF;  // eliminar el bit implícito
    decimalASignificando(sig_resultado, Z.significando);

    cout << "\nResultado Z:" << endl;
    mostrarBits(Z);

    float resultado = recomponerNumero(Z);
    cout << "\nResultado decimal: " << resultado << endl;
    cout << "--- FIN DE LA DIVISIÓN ---\n" << endl;

    return resultado;
}

int main() {
    float a, b;

    cout << "Ingrese dividendo (a): ";
    cin >> a;
    cout << "Ingrese divisor (b): ";
    cin >> b;

    float resultado_emulado = dividirPuntoFlotante(a, b);

    float resultado_nativo = a / b;

    cout << "Comparación de resultados:" << endl;
    cout << "Resultado emulado:        " << resultado_emulado << endl;
    cout << "Resultado nativo (C++):   " << resultado_nativo << endl;

    if (resultado_emulado != resultado_nativo) {
        cout << "Diferencia: " << fabs(resultado_emulado - resultado_nativo) << endl;
    }
    else {
        cout << "¡Los resultados son idénticos!" << endl;
    }

    return 0;
}