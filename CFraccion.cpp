
#include <iostream>
using namespace std;

// ============================================================================
// BLOQUE 1: CLASE FRACCION
// ============================================================================

class Fraccion {
private:
    int num, den;

public:
    Fraccion(int n = 0, int d = 1) {
        num = n;
        den = (d == 0) ? 1 : d;

        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

    int getNum() const {
        return num;
    }

    int getDen() const {
        return den;
    }

    double valor() const {
        return (double)num / den;
    }

    bool operator==(const Fraccion& r) const {
        return (long long)num * r.den ==
               (long long)r.num * den;
    }

    bool operator!=(const Fraccion& r) const {
        return !(*this == r);
    }

    bool operator<(const Fraccion& r) const {
        return (long long)num * r.den <
               (long long)r.num * den;
    }

    bool operator>(const Fraccion& r) const {
        return r < *this;
    }

    Fraccion operator+(const Fraccion& r) const {
        return Fraccion(
            num * r.den + r.num * den,
            den * r.den
        );
    }

    Fraccion operator-(const Fraccion& r) const {
        return Fraccion(
            num * r.den - r.num * den,
            den * r.den
        );
    }

    Fraccion operator*(int val) const {
        return Fraccion(num * val, den);
    }

    Fraccion& operator+=(int val) {
        num += val * den;
        return *this;
    }

    Fraccion& operator-=(int val) {
        num -= val * den;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Fraccion& f) {
        os << f.num << "/" << f.den;
        return os;
    }
};


// ============================================================================
// BLOQUE 2: DECLARACION ADELANTADA
// ============================================================================

template <class T>
class CFraccion;


// ============================================================================
// BLOQUE 3: ITERADOR
// ============================================================================

template <class T>
class Fraccion_Iterator {
private:
    CFraccion<T>* ptr;
    int id;

public:
    Fraccion_Iterator(CFraccion<T>* p = nullptr, int _id = 0) {
        ptr = p;
        id = _id;
    }

    Fraccion_Iterator& operator=(const Fraccion_Iterator& r) {
        ptr = r.ptr;
        id = r.id;
        return *this;
    }

    bool operator!=(const Fraccion_Iterator& r) const {
        return ptr != r.ptr || id != r.id;
    }

    Fraccion_Iterator& operator++() {
        ++id;
        return *this;
    }

    T& operator*() {
        return (*ptr)[id];
    }
};


// ============================================================================
// BLOQUE 4: CONTENEDOR CFraccion
// ============================================================================

template <class T>
class CFraccion {
private:
    T* datos;
    int n;

public:

    // Constructor con tamaño
    CFraccion(int tam) {
        n = tam;
        datos = (n > 0) ? new T[n] : nullptr;
    }

    // Constructor por defecto
    CFraccion() {
        n = 0;
        datos = nullptr;
    }

    // Constructor de copia
    CFraccion(const CFraccion& r) {
        n = r.n;
        datos = (n > 0) ? new T[n] : nullptr;

        for (int i = 0; i < n; ++i)
            datos[i] = r.datos[i];
    }

    // Destructor
    ~CFraccion() {
        delete[] datos;
    }

    // Operador de asignacion
    CFraccion& operator=(const CFraccion& r) {
        if (this == &r)
            return *this;

        delete[] datos;

        n = r.n;
        datos = (n > 0) ? new T[n] : nullptr;

        for (int i = 0; i < n; ++i)
            datos[i] = r.datos[i];

        return *this;
    }

    // Operador ()
    T& operator()(int i) {
        return datos[i];
    }

    // Operador []
    T& operator[](int i) {
        return datos[i];
    }

    // Operador ==
    bool operator==(const CFraccion& r) const {
        if (n != r.n)
            return false;

        for (int i = 0; i < n; ++i) {
            if (datos[i] != r.datos[i])
                return false;
        }

        return true;
    }

    // Operador !=
    bool operator!=(const CFraccion& r) const {
        return !(*this == r);
    }

    // Operador +
    CFraccion operator+(const CFraccion& r) const {
        CFraccion res(n);

        for (int i = 0; i < n; ++i)
            res.datos[i] = datos[i] + r.datos[i];

        return res;
    }

    // Operador -
    CFraccion operator-(const CFraccion& r) const {
        CFraccion res(n);

        for (int i = 0; i < n; ++i)
            res.datos[i] = datos[i] - r.datos[i];

        return res;
    }

    // Operador * por entero
    CFraccion operator*(int val) const {
        CFraccion res(n);

        for (int i = 0; i < n; ++i)
            res.datos[i] = datos[i] * val;

        return res;
    }

    // Operador +=
    CFraccion& operator+=(int val) {
        for (int i = 0; i < n; ++i)
            datos[i] += val;

        return *this;
    }

    // Operador -=
    CFraccion& operator-=(int val) {
        for (int i = 0; i < n; ++i)
            datos[i] -= val;

        return *this;
    }

    // Operador <<
    friend ostream& operator<<(ostream& os, const CFraccion& v) {
        for (int i = 0; i < v.n; ++i)
            os << v.datos[i] << "\t";

        os << endl;
        return os;
    }

    // Metodos auxiliares
    int getSize() const {
        return n;
    }

    T* getData() {
        return datos;
    }

    // Iteradores
    typedef Fraccion_Iterator<T> iterator;

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, n);
    }
};


// ============================================================================
// BLOQUE 5: METODOS DE ORDENAMIENTO
// ============================================================================

// Metodo 1: comparacion directa

template <class T>
void xsort_1_Normal(T* datos, int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (datos[j] < datos[i]) {
                T aux = datos[i];
                datos[i] = datos[j];
                datos[j] = aux;
            }
        }
    }
}

// Metodo 2: puntero a funcion

template <class T>
bool esMenor(T a, T b) {
    return a < b;
}

template <class T>
bool esMayor(T a, T b) {
    return a > b;
}

template <class T>
void xsort_2_PunteroFuncion(
    T* datos, int n, bool (*PF)(T, T)
) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (PF(datos[j], datos[i])) {
                T aux = datos[i];
                datos[i] = datos[j];
                datos[j] = aux;
            }
        }
    }
}

// Metodo 3: polimorfismo

template <class T>
class CComp {
public:
    virtual bool cmp(T a, T b) = 0;
    virtual ~CComp() {}
};

template <class T>
class CLessPoly : public CComp<T> {
public:
    bool cmp(T a, T b) override {
        return a < b;
    }
};

template <class T>
class CGreaterPoly : public CComp<T> {
public:
    bool cmp(T a, T b) override {
        return a > b;
    }
};

template <class T>
void xsort_3_Polimorfismo(T* datos, int n, CComp<T>* p) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (p->cmp(datos[j], datos[i])) {
                T aux = datos[i];
                datos[i] = datos[j];
                datos[j] = aux;
            }
        }
    }
}

// Metodo 4: functors

template <class T>
struct SLess {
    bool operator()(T a, T b) {
        return a < b;
    }
};

template <class T>
struct SGreater {
    bool operator()(T a, T b) {
        return a > b;
    }
};

template <class T, class Comparador>
void xsort_4_Functor(T* datos, int n, Comparador c) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (c(datos[j], datos[i])) {
                T aux = datos[i];
                datos[i] = datos[j];
                datos[j] = aux;
            }
        }
    }
}

// Metodo 5: functors + inline

template <class T>
struct SLessInline {
    inline bool operator()(T a, T b) {
        return a < b;
    }
};

template <class T>
struct SGreaterInline {
    inline bool operator()(T a, T b) {
        return a > b;
    }
};

template <class T, class Comparador>
void xsort_5_Inline(T* datos, int n, Comparador c) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (c(datos[j], datos[i])) {
                T aux = datos[i];
                datos[i] = datos[j];
                datos[j] = aux;
            }
        }
    }
}


// ============================================================================
// BLOQUE 6: MAIN
// ============================================================================

int main() {
    cout << "=== CREANDO CONTENEDOR DE FRACCIONES ===" << endl;

    CFraccion<Fraccion> v1(6);

    v1(0) = Fraccion(3, 4);
    v1(1) = Fraccion(1, 2);
    v1(2) = Fraccion(5, 6);
    v1[3] = Fraccion(1, 3);
    v1[4] = Fraccion(7, 4);
    v1[5] = Fraccion(2, 5);

    cout << "Fracciones originales:" << endl;
    cout << v1;

    cout << "--- DEMOSTRACION DE OPERADORES ---" << endl;

    CFraccion<Fraccion> v2 = v1;

    CFraccion<Fraccion> v3(6);
    v3 = v1;

    if (v1 == v2)
        cout << "v1 y v2 son iguales" << endl;

    if (v1 != v3)
        cout << "v1 y v3 son diferentes" << endl;

    CFraccion<Fraccion> suma = v1 + v2;
    cout << "v1 + v2:" << endl << suma;

    CFraccion<Fraccion> resta = v1 - v2;
    cout << "v1 - v2:" << endl << resta;

    CFraccion<Fraccion> producto = v1 * 2;
    cout << "v1 * 2:" << endl << producto;

    v2 += 1;
    cout << "v2 despues de += 1:" << endl << v2;

    v2 -= 1;
    cout << "v2 despues de -= 1:" << endl << v2;

    cout << "--- RECORRIDO CON ITERADOR ---" << endl;

    CFraccion<Fraccion>::iterator it;

    for (it = v1.begin(); it != v1.end(); ++it)
        cout << *it << " ";

    cout << endl << endl;

    // Descomentar solamente el metodo solicitado.

    // xsort_1_Normal(v1.getData(), v1.getSize());

    // xsort_2_PunteroFuncion(
    //     v1.getData(), v1.getSize(), esMenor<Fraccion>
    // );

    // xsort_2_PunteroFuncion(
    //     v1.getData(), v1.getSize(), esMayor<Fraccion>
    // );

    // CLessPoly<Fraccion> menor;
    // xsort_3_Polimorfismo(
    //     v1.getData(), v1.getSize(), &menor
    // );

    // CGreaterPoly<Fraccion> mayor;
    // xsort_3_Polimorfismo(
    //     v1.getData(), v1.getSize(), &mayor
    // );

    // SLess<Fraccion> menorFunctor;
    // xsort_4_Functor(v1.getData(), v1.getSize(), menorFunctor);

    // SGreater<Fraccion> mayorFunctor;
    // xsort_4_Functor(v1.getData(), v1.getSize(), mayorFunctor);

    // SLessInline<Fraccion> menorInline;
    // xsort_5_Inline(v1.getData(), v1.getSize(), menorInline);

    // SGreaterInline<Fraccion> mayorInline;
    // xsort_5_Inline(v1.getData(), v1.getSize(), mayorInline);

    // cout << "Fracciones ordenadas:" << endl << v1;

    return 0;
}
