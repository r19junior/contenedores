
#include <iostream>
using namespace std;

template <class T>
class CMatrix3D;


// ============================================================================
// BLOQUE 1: ITERADOR
// ============================================================================

template <class T>
class Matrix3D_Iterator {
private:
    CMatrix3D<T>* ptr;
    int id;

public:
    Matrix3D_Iterator(CMatrix3D<T>* p = nullptr, int _id = 0) {
        ptr = p;
        id = _id;
    }

    Matrix3D_Iterator& operator=(const Matrix3D_Iterator& r) {
        ptr = r.ptr;
        id = r.id;
        return *this;
    }

    bool operator!=(const Matrix3D_Iterator& r) const {
        return ptr != r.ptr || id != r.id;
    }

    Matrix3D_Iterator& operator++() {
        ++id;
        return *this;
    }

    T& operator*() {
        int plano = ptr->getRows() * ptr->getCols();
        int k = id / plano;
        int resto = id % plano;
        int i = resto / ptr->getCols();
        int j = resto % ptr->getCols();

        return (*ptr)(k, i, j);
    }
};


// ============================================================================
// BLOQUE 2: CLASE MATRIZ TRIDIMENSIONAL
// ============================================================================

template <class T>
class CMatrix3D {
private:
    T*** mat;
    int profundidad, rows, cols;

    void reservar() {
        if (profundidad <= 0 || rows <= 0 || cols <= 0) {
            mat = nullptr;
            return;
        }

        mat = new T**[profundidad];

        for (int k = 0; k < profundidad; ++k) {
            mat[k] = new T*[rows];

            for (int i = 0; i < rows; ++i)
                mat[k][i] = new T[cols];
        }
    }

    void liberar() {
        if (mat != nullptr) {
            for (int k = 0; k < profundidad; ++k) {
                for (int i = 0; i < rows; ++i)
                    delete[] mat[k][i];

                delete[] mat[k];
            }

            delete[] mat;
        }
    }

public:

    // ------------------------------------------------------------------------
    // CONSTRUCTOR CON PARAMETROS
    // ------------------------------------------------------------------------

    CMatrix3D(int p, int r, int c) {
        profundidad = p;
        rows = r;
        cols = c;
        reservar();
    }

    // ------------------------------------------------------------------------
    // CONSTRUCTOR POR DEFECTO
    // ------------------------------------------------------------------------

    CMatrix3D() {
        profundidad = 0;
        rows = 0;
        cols = 0;
        mat = nullptr;
    }

    // ------------------------------------------------------------------------
    // CONSTRUCTOR DE COPIA
    // ------------------------------------------------------------------------

    CMatrix3D(const CMatrix3D& r) {
        profundidad = r.profundidad;
        rows = r.rows;
        cols = r.cols;

        reservar();

        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    mat[k][i][j] = r.mat[k][i][j];
            }
        }
    }

    // ------------------------------------------------------------------------
    // DESTRUCTOR
    // ------------------------------------------------------------------------

    ~CMatrix3D() {
        liberar();
    }

    // ------------------------------------------------------------------------
    // 1. OPERADOR DE ASIGNACION =
    // ------------------------------------------------------------------------

    CMatrix3D& operator=(const CMatrix3D& r) {
        if (this == &r)
            return *this;

        liberar();

        profundidad = r.profundidad;
        rows = r.rows;
        cols = r.cols;

        reservar();

        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    mat[k][i][j] = r.mat[k][i][j];
            }
        }

        return *this;
    }

    // ------------------------------------------------------------------------
    // 2. OPERADOR () -> m(k, i, j)
    // ------------------------------------------------------------------------

    T& operator()(int k, int i, int j) {
        return mat[k][i][j];
    }

    // ------------------------------------------------------------------------
    // 3. OPERADOR [] -> m[k][i][j]
    // ------------------------------------------------------------------------

    T** operator[](int k) {
        return mat[k];
    }

    // ------------------------------------------------------------------------
    // 4. OPERADOR ==
    // ------------------------------------------------------------------------

    bool operator==(const CMatrix3D& r) const {
        if (profundidad != r.profundidad ||
            rows != r.rows || cols != r.cols)
            return false;

        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (mat[k][i][j] != r.mat[k][i][j])
                        return false;
                }
            }
        }

        return true;
    }

    // ------------------------------------------------------------------------
    // 5. OPERADOR !=
    // ------------------------------------------------------------------------

    bool operator!=(const CMatrix3D& r) const {
        return !(*this == r);
    }

    // ------------------------------------------------------------------------
    // 6. OPERADOR +
    // ------------------------------------------------------------------------

    CMatrix3D operator+(const CMatrix3D& r) const {
        CMatrix3D res(profundidad, rows, cols);

        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    res.mat[k][i][j] = mat[k][i][j] + r.mat[k][i][j];
            }
        }

        return res;
    }

    // ------------------------------------------------------------------------
    // 7. OPERADOR -
    // ------------------------------------------------------------------------

    CMatrix3D operator-(const CMatrix3D& r) const {
        CMatrix3D res(profundidad, rows, cols);

        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    res.mat[k][i][j] = mat[k][i][j] - r.mat[k][i][j];
            }
        }

        return res;
    }

    // ------------------------------------------------------------------------
    // 8. OPERADOR * POR ESCALAR
    // ------------------------------------------------------------------------

    CMatrix3D operator*(T val) const {
        CMatrix3D res(profundidad, rows, cols);

        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    res.mat[k][i][j] = mat[k][i][j] * val;
            }
        }

        return res;
    }

    // ------------------------------------------------------------------------
    // 9. OPERADOR +=
    // ------------------------------------------------------------------------

    CMatrix3D& operator+=(T val) {
        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    mat[k][i][j] += val;
            }
        }

        return *this;
    }

    // ------------------------------------------------------------------------
    // 10. OPERADOR -=
    // ------------------------------------------------------------------------

    CMatrix3D& operator-=(T val) {
        for (int k = 0; k < profundidad; ++k) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j)
                    mat[k][i][j] -= val;
            }
        }

        return *this;
    }

    // ------------------------------------------------------------------------
    // 11. OPERADOR <<
    // ------------------------------------------------------------------------

    friend ostream& operator<<(ostream& os, const CMatrix3D& m) {
        for (int k = 0; k < m.profundidad; ++k) {
            os << "Plano " << k << ":" << endl;

            for (int i = 0; i < m.rows; ++i) {
                for (int j = 0; j < m.cols; ++j)
                    os << m.mat[k][i][j] << "\t";

                os << endl;
            }

            os << endl;
        }

        return os;
    }

    // ------------------------------------------------------------------------
    // METODOS AUXILIARES
    // ------------------------------------------------------------------------

    int getProfundidad() const {
        return profundidad;
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    int getSize() const {
        return profundidad * rows * cols;
    }

    T*** getMat() {
        return mat;
    }

    // ------------------------------------------------------------------------
    // ITERADORES
    // ------------------------------------------------------------------------

    typedef Matrix3D_Iterator<T> iterator;

    iterator begin() {
        return iterator(this, 0);
    }

    iterator end() {
        return iterator(this, getSize());
    }
};


// ============================================================================
// BLOQUE 3: ORDENAMIENTOS
// ============================================================================

// ----------------------------------------------------------------------------
// METODO 1: COMPARACION DIRECTA
// ----------------------------------------------------------------------------

template <class T>
void xsort_1_Normal(T*** mat, int p, int r, int c) {
    int total = p * r * c;

    for (int a = 0; a < total - 1; ++a) {
        for (int b = a + 1; b < total; ++b) {
            int k1 = a / (r * c);
            int i1 = (a % (r * c)) / c;
            int j1 = a % c;

            int k2 = b / (r * c);
            int i2 = (b % (r * c)) / c;
            int j2 = b % c;

            if (mat[k2][i2][j2] < mat[k1][i1][j1]) {
                T aux = mat[k1][i1][j1];
                mat[k1][i1][j1] = mat[k2][i2][j2];
                mat[k2][i2][j2] = aux;
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
    T*** mat, int p, int r, int c, bool (*PF)(T, T)
) {
    int total = p * r * c;

    for (int a = 0; a < total - 1; ++a) {
        for (int b = a + 1; b < total; ++b) {
            int k1 = a / (r * c);
            int i1 = (a % (r * c)) / c;
            int j1 = a % c;

            int k2 = b / (r * c);
            int i2 = (b % (r * c)) / c;
            int j2 = b % c;

            if (PF(mat[k2][i2][j2], mat[k1][i1][j1])) {
                T aux = mat[k1][i1][j1];
                mat[k1][i1][j1] = mat[k2][i2][j2];
                mat[k2][i2][j2] = aux;
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
    T*** mat, int p, int r, int c, CComp<T>* comp
) {
    int total = p * r * c;

    for (int a = 0; a < total - 1; ++a) {
        for (int b = a + 1; b < total; ++b) {
            int k1 = a / (r * c);
            int i1 = (a % (r * c)) / c;
            int j1 = a % c;

            int k2 = b / (r * c);
            int i2 = (b % (r * c)) / c;
            int j2 = b % c;

            if (comp->cmp(mat[k2][i2][j2], mat[k1][i1][j1])) {
                T aux = mat[k1][i1][j1];
                mat[k1][i1][j1] = mat[k2][i2][j2];
                mat[k2][i2][j2] = aux;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// METODO 4: FUNCTOR
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
    T*** mat, int p, int r, int c, Comparador comp
) {
    int total = p * r * c;

    for (int a = 0; a < total - 1; ++a) {
        for (int b = a + 1; b < total; ++b) {
            int k1 = a / (r * c);
            int i1 = (a % (r * c)) / c;
            int j1 = a % c;

            int k2 = b / (r * c);
            int i2 = (b % (r * c)) / c;
            int j2 = b % c;

            if (comp(mat[k2][i2][j2], mat[k1][i1][j1])) {
                T aux = mat[k1][i1][j1];
                mat[k1][i1][j1] = mat[k2][i2][j2];
                mat[k2][i2][j2] = aux;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// METODO 5: FUNCTOR + INLINE
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
    T*** mat, int p, int r, int c, Comparador comp
) {
    int total = p * r * c;

    for (int a = 0; a < total - 1; ++a) {
        for (int b = a + 1; b < total; ++b) {
            int k1 = a / (r * c);
            int i1 = (a % (r * c)) / c;
            int j1 = a % c;

            int k2 = b / (r * c);
            int i2 = (b % (r * c)) / c;
            int j2 = b % c;

            if (comp(mat[k2][i2][j2], mat[k1][i1][j1])) {
                T aux = mat[k1][i1][j1];
                mat[k1][i1][j1] = mat[k2][i2][j2];
                mat[k2][i2][j2] = aux;
            }
        }
    }
}


// ============================================================================
// BLOQUE 4: MAIN
// ============================================================================

int main() {
    cout << "=== CREANDO MATRIZ 3D DE 2x2x3 ===" << endl;

    CMatrix3D<int> m1(2, 2, 3);

    int valor = 10;

    for (int k = 0; k < m1.getProfundidad(); ++k) {
        for (int i = 0; i < m1.getRows(); ++i) {
            for (int j = 0; j < m1.getCols(); ++j) {
                m1(k, i, j) = valor;
                valor += 10;
            }
        }
    }

    // OPERADOR ()

    m1(0, 0, 0) = 40;

    // OPERADOR []

    m1[1][1][2] = 30;

    cout << "Matriz 3D original:" << endl;
    cout << m1;

    // ------------------------------------------------------------------------
    // PRUEBAS DE OPERADORES
    // ------------------------------------------------------------------------

    cout << "--- DEMOSTRACION DE OPERADORES ---" << endl;

    CMatrix3D<int> m2 = m1;

    CMatrix3D<int> m3(2, 2, 3);
    m3 = m1;

    if (m1 == m2)
        cout << "m1 y m2 son iguales" << endl;

    if (m1 != m3)
        cout << "m1 y m3 son diferentes" << endl;

    CMatrix3D<int> suma = m1 + m2;
    cout << "m1 + m2:" << endl << suma;

    CMatrix3D<int> resta = m1 - m2;
    cout << "m1 - m2:" << endl << resta;

    CMatrix3D<int> producto = m1 * 2;
    cout << "m1 * 2:" << endl << producto;

    m2 += 5;
    cout << "m2 despues de += 5:" << endl << m2;

    m2 -= 3;
    cout << "m2 despues de -= 3:" << endl << m2;

    // ------------------------------------------------------------------------
    // ITERADOR
    // ------------------------------------------------------------------------

    cout << "--- RECORRIDO CON ITERADOR ---" << endl;

    CMatrix3D<int>::iterator it;

    for (it = m1.begin(); it != m1.end(); ++it)
        cout << *it << " ";

    cout << endl << endl;

    // ------------------------------------------------------------------------
    // ORDENAMIENTOS: DESCOMENTAR SOLO EL SOLICITADO
    // ------------------------------------------------------------------------

    // xsort_1_Normal(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols()
    // );

    // xsort_2_PunteroFuncion(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), esMenor<int>
    // );

    // xsort_2_PunteroFuncion(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), esMayor<int>
    // );

    // CLessPoly<int> menor;
    // xsort_3_Polimorfismo(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), &menor
    // );

    // CGreaterPoly<int> mayor;
    // xsort_3_Polimorfismo(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), &mayor
    // );

    // SLess<int> menorFunctor;
    // xsort_4_Functor(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), menorFunctor
    // );

    // SGreater<int> mayorFunctor;
    // xsort_4_Functor(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), mayorFunctor
    // );

    // SLessInline<int> menorInline;
    // xsort_5_Inline(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), menorInline
    // );

    // SGreaterInline<int> mayorInline;
    // xsort_5_Inline(
    //     m1.getMat(), m1.getProfundidad(),
    //     m1.getRows(), m1.getCols(), mayorInline
    // );

    // cout << "Matriz 3D ordenada:" << endl << m1;

    return 0;
}
