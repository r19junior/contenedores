
#include <iostream>
using namespace std;

// ============================================================================
// DECLARACION ADELANTADA
// ============================================================================

template <class T>
class CVector;


// ============================================================================
// BLOQUE 1: ITERADOR PROPIO
// ============================================================================

template <class T>
class Vector_Iterator {
private:
    CVector<T>* ptr;
    int id;

public:
    Vector_Iterator(CVector<T>* p = nullptr, int _id = 0) {
        ptr = p;
        id = _id;
    }

    Vector_Iterator& operator=(const Vector_Iterator& r) {
        ptr = r.ptr;
        id = r.id;
        return *this;
    }

    bool operator!=(const Vector_Iterator& r) const {
        return ptr != r.ptr || id != r.id;
    }

    Vector_Iterator& operator++() {
        ++id;
        return *this;
    }

    T& operator*() {
        return (*ptr)[id];
    }
};


// ============================================================================
// BLOQUE 2: CLASE CVECTOR
// ============================================================================

template <class T>
class CVector {
private:
    T* datos;
    int n;

public:

    // ------------------------------------------------------------------------
    // CONSTRUCTOR CON PARAMETROS
    // ------------------------------------------------------------------------

    CVector(int tam) {
        n = tam;

        if (n > 0)
            datos = new T[n];
        else
            datos = nullptr;
    }

    // ------------------------------------------------------------------------
    // CONSTRUCTOR POR DEFECTO
    // ------------------------------------------------------------------------

    CVector() {
        n = 0;
        datos = nullptr;
    }

    // ------------------------------------------------------------------------
    // CONSTRUCTOR DE COPIA
    // ------------------------------------------------------------------------

    CVector(const CVector& r) {
        n = r.n;

        if (n > 0) {
            datos = new T[n];

            for (int i = 0; i < n; ++i)
                datos[i] = r.datos[i];
        }
        else {
            datos = nullptr;
        }
    }

    // ------------------------------------------------------------------------
    // DESTRUCTOR
    // ------------------------------------------------------------------------

    ~CVector() {
        delete[] datos;
    }

    // ------------------------------------------------------------------------
    // 1. OPERADOR DE ASIGNACION =
    // ------------------------------------------------------------------------

    CVector& operator=(const CVector& r) {
        if (this == &r)
            return *this;

        delete[] datos;

        n = r.n;

        if (n > 0) {
            datos = new T[n];

            for (int i = 0; i < n; ++i)
                datos[i] = r.datos[i];
        }
        else {
            datos = nullptr;
        }

        return *this;
    }

    // ------------------------------------------------------------------------
    // 2. OPERADOR DE ACCESO ()
    // v(i)
    // ------------------------------------------------------------------------

    T& operator()(int i) {
        return datos[i];
    }

    // ------------------------------------------------------------------------
    // 3. OPERADOR DE ACCESO []
    // v[i]
    // ------------------------------------------------------------------------

    T& operator[](int i) {
        return datos[i];
    }

    // ------------------------------------------------------------------------
    // 4. OPERADOR DE IGUALDAD ==
    // ------------------------------------------------------------------------

    bool operator==(const CVector& r) const {
        if (n != r.n)
            return false;

        for (int i = 0; i < n; ++i) {
            if (datos[i] != r.datos[i])
                return false;
        }

        return true;
    }

    // ------------------------------------------------------------------------
    // 5. OPERADOR DE DESIGUALDAD !=
    // ------------------------------------------------------------------------

    bool operator!=(const CVector& r) const {
        return !(*this == r);
    }

    // ------------------------------------------------------------------------
    // 6. OPERADOR DE SUMA +
    // ------------------------------------------------------------------------

    CVector operator+(const CVector& r) const {
        CVector res(n);

        for (int i = 0; i < n; ++i)
            res.datos[i] = datos[i] + r.datos[i];

        return res;
    }

    // ------------------------------------------------------------------------
    // 7. OPERADOR DE RESTA -
    // ------------------------------------------------------------------------

    CVector operator-(const CVector& r) const {
        CVector res(n);

        for (int i = 0; i < n; ++i)
            res.datos[i] = datos[i] - r.datos[i];

        return res;
    }

    // ------------------------------------------------------------------------
    // 8. OPERADOR DE MULTIPLICACION POR ESCALAR *
    // ------------------------------------------------------------------------

    CVector operator*(T val) const {
        CVector res(n);

        for (int i = 0; i < n; ++i)
            res.datos[i] = datos[i] * val;

        return res;
    }

    // ------------------------------------------------------------------------
    // 9. OPERADOR DE SUMA ACUMULADA +=
    // ------------------------------------------------------------------------

    CVector& operator+=(T val) {
        for (int i = 0; i < n; ++i)
            datos[i] += val;

        return *this;
    }

    // ------------------------------------------------------------------------
    // 10. OPERADOR DE RESTA ACUMULADA -=
    // ------------------------------------------------------------------------

    CVector& operator-=(T val) {
        for (int i = 0; i < n; ++i)
            datos[i] -= val;

        return *this;
    }

    // ------------------------------------------------------------------------
    // 11. OPERADOR DE IMPRESION <<
    // ------------------------------------------------------------------------

    friend ostream& operator<<(ostream& os, const CVector& v) {
        for (int i = 0; i < v.n; ++i)
            os << v.datos[i] << "\t";

        os << endl;
        return os;
    }

    // ------------------------------------------------------------------------
    // METODOS AUXILIARES
    // ------------------------------------------------------------------------

    int getSize() const {
        return n;
    }

    T* getData() {
        return datos;
    }

    // ------------------------------------------------------------------------
    // ITERADORES
    // ------------------------------------------------------------------------

    typedef Vector_Iterator<T> iterator;

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, n);
    }
};


// ============================================================================
// BLOQUE 3: METODOS DE ORDENAMIENTO
// ============================================================================

// ----------------------------------------------------------------------------
// METODO 1: COMPARACION DIRECTA
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// METODO 2: PUNTERO A FUNCION
// ----------------------------------------------------------------------------

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
            if ((*PF)(datos[j], datos[i])) {
                T aux = datos[i];
                datos[i] = datos[j];
                datos[j] = aux;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// METODO 3: POLIMORFISMO
// ----------------------------------------------------------------------------

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
void xsort_3_Polimorfismo(
    T* datos, int n, CComp<T>* p
) {
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

// ----------------------------------------------------------------------------
// METODO 4: FUNCTORS
// ----------------------------------------------------------------------------

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
void xsort_4_Functor(
    T* datos, int n, Comparador c
) {
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

// ----------------------------------------------------------------------------
// METODO 5: FUNCTORS + INLINE
// ----------------------------------------------------------------------------

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
void xsort_5_Inline(
    T* datos, int n, Comparador c
) {
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
// BLOQUE 4: MAIN
// ============================================================================

int main() {

    cout << "=== CREANDO VECTOR V1 DE 6 ELEMENTOS ===" << endl;

    CVector<int> v1(6);

    // OPERADOR ()

    v1(0) = 40;
    v1(1) = 10;
    v1(2) = 50;

    // OPERADOR []

    v1[3] = 20;
    v1[4] = 60;
    v1[5] = 30;

    cout << "Vector V1 Original:" << endl;
    cout << v1;

    // ------------------------------------------------------------------------
    // DEMOSTRACION DE OPERADORES
    // ------------------------------------------------------------------------

    cout << "--- DEMOSTRACION DE OPERADORES ---" << endl;

    CVector<int> v2 = v1;

    CVector<int> v3(6);
    v3 = v1;

    if (v1 == v2)
        cout << "v1 y v2 son iguales" << endl;

    if (v1 != v3)
        cout << "v1 y v3 son diferentes" << endl;

    CVector<int> suma = v1 + v2;
    cout << "v1 + v2:" << endl << suma;

    CVector<int> resta = v1 - v2;
    cout << "v1 - v2:" << endl << resta;

    CVector<int> producto = v1 * 2;
    cout << "v1 * 2:" << endl << producto;

    v2 += 5;
    cout << "v2 despues de += 5:" << endl << v2;

    v2 -= 3;
    cout << "v2 despues de -= 3:" << endl << v2;

    // ------------------------------------------------------------------------
    // DEMOSTRACION DEL ITERADOR
    // ------------------------------------------------------------------------

    cout << "--- RECORRIDO CON ITERADOR ---" << endl;

    CVector<int>::iterator it;

    for (it = v1.begin(); it != v1.end(); ++it)
        cout << *it << " ";

    cout << endl << endl;

    // ------------------------------------------------------------------------
    // PRUEBAS DE ORDENAMIENTO
    // Descomentar solo el metodo solicitado.
    // ------------------------------------------------------------------------

    // xsort_1_Normal(v1.getData(), v1.getSize());

    // xsort_2_PunteroFuncion(
    //     v1.getData(), v1.getSize(), esMenor<int>
    // );

    // xsort_2_PunteroFuncion(
    //     v1.getData(), v1.getSize(), esMayor<int>
    // );

    // CLessPoly<int> reglaMenorPoly;
    // xsort_3_Polimorfismo(
    //     v1.getData(), v1.getSize(), &reglaMenorPoly
    // );

    // CGreaterPoly<int> reglaMayorPoly;
    // xsort_3_Polimorfismo(
    //     v1.getData(), v1.getSize(), &reglaMayorPoly
    // );

    // SLess<int> reglaMenorFunctor;
    // xsort_4_Functor(
    //     v1.getData(), v1.getSize(), reglaMenorFunctor
    // );

    // SGreater<int> reglaMayorFunctor;
    // xsort_4_Functor(
    //     v1.getData(), v1.getSize(), reglaMayorFunctor
    // );

    // SLessInline<int> reglaMenorInline;
    // xsort_5_Inline(
    //     v1.getData(), v1.getSize(), reglaMenorInline
    // );

    // SGreaterInline<int> reglaMayorInline;
    // xsort_5_Inline(
    //     v1.getData(), v1.getSize(), reglaMayorInline
    // );

    // cout << "Vector V1 Ordenado:" << endl << v1;

    return 0;
}
