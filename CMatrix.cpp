#include <iostream>
using namespace std;

/*
============================================================================
GUÍA PARA ADAPTAR ESTE ARCHIVO AL EXAMEN
----------------------------------------------------------------------------
A) SI SOLO PIDEN CLASE MATRIZ + SOBRECARGA DE OPERADORES:
- CONSERVA el BLOQUE 2 (clase CMatrix, constructores, destructor y TODOS
los operadores sobrecargados).
- Conserva el main de demostración de operadores, o adapta el main que dé
el profesor.
- Puedes borrar el BLOQUE 3 COMPLETO (los cinco métodos de ordenamiento)
y las líneas de ordenamiento del main.
- Si NO piden iteradores, borra el BLOQUE 1, las tres líneas typedef/begin/end
marcadas en CMatrix y el bloque de recorrido con iterador del main.

B) SI PIDEN SOBRECARGA DE OPERADORES PERO NO PIDEN PROBARLOS:
- Conserva las funciones operator... dentro de CMatrix.
- Puedes borrar del main las líneas de demostración que empiezan con
"PRUEBAS DE OPERADORES"; NO borres las implementaciones dentro de CMatrix.

C) SI PIDEN SOLO UNOS OPERADORES:
- Conserva los operator... que mencione el enunciado y los que necesiten
esos operadores para funcionar. Por ejemplo, operator!= de CMatrix usa ==.
- El operator= de Matrix_Iterator es DISTINTO del operator= de CMatrix.

D) SI PIDEN ORDENAMIENTO:
- Conserva el BLOQUE 3 y solo descomenta el método solicitado en main.
- Los intercambios están hechos manualmente con una variable aux; no usan
std::swap.

E) SI PIDEN SIN TEMPLATES (solo int): elimina template<class T> y cambia T
por int con cuidado en todas las funciones y clases.
============================================================================
*/

// Declaración adelantada de la matriz para el iterador
template <class T>
class CMatrix;


// ============================================================================
// BLOQUE 1: ITERADOR DE MATRIZ
// (SI EL EXAMEN PIDE "SIN ITERADORES", BORRA ESTE BLOQUE COMPLETO)
// ============================================================================
template <class T>
class Matrix_Iterator {
private:
	CMatrix<T>* ptr; // Puntero a la matriz
	int id;          // Índice plano (0 hasta rows*cols - 1)
	
public:
	Matrix_Iterator(CMatrix<T>* p = nullptr, int _id = 0) {
		ptr = p;
		id = _id;
	}
	
	Matrix_Iterator& operator=(const Matrix_Iterator& r) {
		ptr = r.ptr;
		id = r.id;
		return *this;
	}
	
	bool operator!=(const Matrix_Iterator& r) const {
		return ptr != r.ptr || id != r.id;
	}
	
	Matrix_Iterator& operator++() {
		++id;
		return *this;
	}
	
	// Convierte el ID lineal a coordenadas (fila, columna)
	T& operator*() {
		int fila = id / ptr->getCols();
		int col = id % ptr->getCols();
		return (*ptr)(fila, col);
	}
};


// ============================================================================
// BLOQUE 2: CLASE MATRIZ CON TEMPLATES Y TODAS LAS SOBRECARGAS DE OPERADORES
// ============================================================================
template <class T>
class CMatrix {
private:
	T** mat;
	int rows, cols;
	
public:
	// ------------------------------------------------------------------------
	// CONSTRUCTORES Y DESTRUCTOR
	// ------------------------------------------------------------------------
	
	// Constructor con parámetros
	CMatrix(int r, int c) {
		rows = r;
		cols = c;
		mat = new T*[rows];
		for (int i = 0; i < rows; ++i) {
			mat[i] = new T[cols];
		}
	}
	
	// Constructor por defecto
	CMatrix() {
		rows = 0;
		cols = 0;
		mat = nullptr;
	}
	
	// Constructor de copia (Copia Profunda)
	CMatrix(const CMatrix& r) {
		rows = r.rows;
		cols = r.cols;
		mat = new T*[rows];
		for (int i = 0; i < rows; ++i) {
			mat[i] = new T[cols];
			for (int j = 0; j < cols; ++j) {
				mat[i][j] = r.mat[i][j];
			}
		}
	}
	
	// Destructor
	~CMatrix() {
		if (mat != nullptr) {
			for (int i = 0; i < rows; ++i) {
				delete[] mat[i];
			}
			delete[] mat;
		}
	}
	
	// ------------------------------------------------------------------------
	// CONSERVA ESTA SECCIÓN SI EL EXAMEN PIDE SOBRECARGA DE OPERADORES.
	// Si pide solo algunos, conserva los operator... solicitados y sus dependencias.
	// SOBRECARGA DE TODOS LOS OPERADORES
	// ------------------------------------------------------------------------
	
	// 1. Operador de Asignación (=)
	CMatrix& operator=(const CMatrix& r) {
		if (this == &r) return *this; // Evitar autoasignación
		
		// Liberar la memoria actual SIN llamar manualmente al destructor
		if (mat != nullptr) {
			for (int i = 0; i < rows; ++i) {
				delete[] mat[i];
			}
			delete[] mat;
		}
		
		rows = r.rows;
		cols = r.cols;
		
		if (rows == 0 || cols == 0) {
			mat = nullptr;
			return *this;
		}
		
		mat = new T*[rows];
		for (int i = 0; i < rows; ++i) {
			mat[i] = new T[cols];
			for (int j = 0; j < cols; ++j) {
				mat[i][j] = r.mat[i][j];
			}
		}
		return *this;
	}
	
	// 2. Operador Acceso Parentesis () -> m(i, j)
	T& operator()(int i, int j) {
		return mat[i][j];
	}
	
	// 3. Operador Acceso Corchetes [] -> m[i][j]
	T* operator[](int i) {
		return mat[i];
	}
	
	// 4. Operador Igualdad (==)
	bool operator==(const CMatrix& r) const {
		if (rows != r.rows || cols != r.cols) return false;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (mat[i][j] != r.mat[i][j]) return false;
			}
		}
		return true;
	}
	
	// 5. Operador Desigualdad (!=)
	bool operator!=(const CMatrix& r) const {
		return !(*this == r);
	}
	
	// 6. Operador Suma de matrices (+)
	CMatrix operator+(const CMatrix& r) {
		CMatrix res(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				res.mat[i][j] = mat[i][j] + r.mat[i][j];
			}
		}
		return res;
	}
	
	// 7. Operador Resta de matrices (-)
	CMatrix operator-(const CMatrix& r) {
		CMatrix res(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				res.mat[i][j] = mat[i][j] - r.mat[i][j];
			}
		}
		return res;
	}
	
	// 8. Operador Multiplicación por Escalar (*) -> m * 2
	CMatrix operator*(T val) {
		CMatrix res(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				res.mat[i][j] = mat[i][j] * val;
			}
		}
		return res;
	}
	
	// 9. Operador Suma Acumulada (+=)
	CMatrix& operator+=(T val) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				mat[i][j] += val;
			}
		}
		return *this;
	}
	
	// 10. Operador Resta Acumulada (-=)
	CMatrix& operator-=(T val) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				mat[i][j] -= val;
			}
		}
		return *this;
	}
	
	// 11. Operador de Impresión (<<)
	friend ostream& operator<<(ostream& os, const CMatrix& m) {
		for (int i = 0; i < m.rows; ++i) {
			for (int j = 0; j < m.cols; ++j) {
				os << m.mat[i][j] << "\t";
			}
			os << endl;
		}
		return os;
	}
	
	// ------------------------------------------------------------------------
	// MÉTODOS AUXILIARES
	// ------------------------------------------------------------------------
	int getRows() const { return rows; }
	int getCols() const { return cols; }
	T** getMat() { return mat; }
	
	// ------------------------------------------------------------------------
	// MÉTODOS DEL ITERADOR 
	// (SI EL EXAMEN PIDE "SIN ITERADORES", BORRA ESTAS 3 LÍNEAS)
	// ------------------------------------------------------------------------
	typedef Matrix_Iterator<T> iterator;
	iterator begin() { return iterator(this, 0); }
	iterator end() { return iterator(this, rows * cols); }
};


// ============================================================================
// BLOQUE 3 OPCIONAL: LOS 5 MÉTODOS DE ORDENAMIENTO.
// SI SOLO PIDEN SOBRECARGA DE OPERADORES, PUEDES BORRAR TODO ESTE BLOQUE.
// ============================================================================
// Los cinco métodos no son operadores sobrecargados: son ordenamientos.
// ============================================================================

// ----------------------------------------------------------------------------
// MÉTODO 1: NORMAL (Comparación directa implícita)
// ----------------------------------------------------------------------------
template <class T>
void xsort_1_Normal(T** mat, int rows, int cols) {
	int total = rows * cols;
	for (int i = 0; i < total - 1; ++i) {
		for (int j = i + 1; j < total; ++j) {
			// Nota: Cambia '<' por '>' si quieres de Mayor a Menor
			if (mat[j / cols][j % cols] < mat[i / cols][i % cols]) {
				T aux = mat[i / cols][i % cols];
				mat[i / cols][i % cols] = mat[j / cols][j % cols];
				mat[j / cols][j % cols] = aux;
			}
		}
	}
}

// ----------------------------------------------------------------------------
// MÉTODO 2: PUNTERO A FUNCIÓN
// ----------------------------------------------------------------------------
template <class T>
	bool esMenor(T a, T b) { return a < b; } // Menor a Mayor
	
	template <class T>
		bool esMayor(T a, T b) { return a > b; } // Mayor a Menor
		
		template <class T>
			void xsort_2_PunteroFuncion(T** mat, int rows, int cols, bool (*PF)(T, T)) {
			int total = rows * cols;
			for (int i = 0; i < total - 1; ++i) {
				for (int j = i + 1; j < total; ++j) {
					if ((*PF)(mat[j / cols][j % cols], mat[i / cols][i % cols])) {
						T aux = mat[i / cols][i % cols];
						mat[i / cols][i % cols] = mat[j / cols][j % cols];
						mat[j / cols][j % cols] = aux;
					}
				}
			}
		}
			
			// ----------------------------------------------------------------------------
			// MÉTODO 3: POLIMORFISMO (Clase Abstracta + Herencia)
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
				bool cmp(T a, T b) override { return a < b; } // Menor a Mayor
			};
			
			template <class T>
			class CGreaterPoly : public CComp<T> {
			public:
				bool cmp(T a, T b) override { return a > b; } // Mayor a Menor
			};
			
			template <class T>
			void xsort_3_Polimorfismo(T** mat, int rows, int cols, CComp<T>* p) {
				int total = rows * cols;
				for (int i = 0; i < total - 1; ++i) {
					for (int j = i + 1; j < total; ++j) {
						if (p->cmp(mat[j / cols][j % cols], mat[i / cols][i % cols])) {
							T aux = mat[i / cols][i % cols];
							mat[i / cols][i % cols] = mat[j / cols][j % cols];
							mat[j / cols][j % cols] = aux;
						}
					}
				}
			}
			
			// ----------------------------------------------------------------------------
			// MÉTODO 4: FUNCTION OBJECTS (FUNCTORS)
			// ----------------------------------------------------------------------------
			template <class T>
				struct SLess {
				bool operator()(T a, T b) { return a < b; } // Menor a Mayor
			};
			
			template <class T>
			struct SGreater {
				bool operator()(T a, T b) { return a > b; } // Mayor a Menor
			};
			
			template <class T, class Comparador>
			void xsort_4_Functor(T** mat, int rows, int cols, Comparador c) {
				int total = rows * cols;
				for (int i = 0; i < total - 1; ++i) {
					for (int j = i + 1; j < total; ++j) {
						if (c(mat[j / cols][j % cols], mat[i / cols][i % cols])) {
							T aux = mat[i / cols][i % cols];
							mat[i / cols][i % cols] = mat[j / cols][j % cols];
							mat[j / cols][j % cols] = aux;
						}
					}
				}
			}
			
			// ----------------------------------------------------------------------------
			// MÉTODO 5: FUNCTION OBJECTS + INLINE
			// ----------------------------------------------------------------------------
			template <class T>
				struct SLessInline {
				inline bool operator()(T a, T b) { return a < b; } // Menor a Mayor
			};
			
			template <class T>
			struct SGreaterInline {
				inline bool operator()(T a, T b) { return a > b; } // Mayor a Menor
			};
			
			template <class T, class Comparador>
			void xsort_5_Inline(T** mat, int rows, int cols, Comparador c) {
				int total = rows * cols;
				for (int i = 0; i < total - 1; ++i) {
					for (int j = i + 1; j < total; ++j) {
						if (c(mat[j / cols][j % cols], mat[i / cols][i % cols])) {
							T aux = mat[i / cols][i % cols];
							mat[i / cols][i % cols] = mat[j / cols][j % cols];
							mat[j / cols][j % cols] = aux;
						}
					}
				}
			}
			
			
			// ============================================================================
			// BLOQUE 4: DEMOSTRACIÓN COMPLETA EN EL MAIN
			// ============================================================================
			int main() {
				cout << "=== CREANDO MATRIZ M1 DE 2x3 ===" << endl;
				CMatrix<int> m1(2, 3);
				
				// Probando Operador Accesso Parentesis ()
				m1(0, 0) = 40; m1(0, 1) = 10; m1(0, 2) = 50;
				
				// Probando Operador Acceso Corchetes []
				m1[1][0] = 20; m1[1][1] = 60; m1[1][2] = 30;
				
				// Probando Operador de Impresión <<
				cout << "Matriz M1 Original:" << endl << m1;
				
				// ------------------------------------------------------------------------
				// DEMOSTRACIÓN DE OPERADORES: ESTE BLOQUE ES SOLO PARA PROBARLOS.
				// Si el enunciado no pide demostración/pruebas, puedes borrar este bloque
				// del main; NO borres las implementaciones operator... dentro de CMatrix.
				// ------------------------------------------------------------------------
				cout << "--- DEMOSTRACION DE OPERADORES ---" << endl;
				
				CMatrix<int> m2 = m1; // Constructor de copia (NO es operator=)
				
				CMatrix<int> m3(2, 3);
				m3 = m1;              // operator= de CMatrix
				
				if (m1 == m2) {       // operator==
					cout << "m1 y m2 son iguales" << endl;
				}
				if (m1 != m3) {       // operator!=; en este caso no debería entrar
					cout << "m1 y m3 son diferentes" << endl;
				}
				
				CMatrix<int> suma = m1 + m2; // operator+
				cout << "m1 + m2:" << endl << suma; // operator<<
				
				CMatrix<int> resta = m1 - m2; // operator-
				cout << "m1 - m2:" << endl << resta;
				
				CMatrix<int> producto = m1 * 2; // operator* por escalar
				cout << "m1 * 2:" << endl << producto;
				
				m2 += 5; // operator+=: suma 5 a cada elemento de m2
				cout << "m2 despues de += 5:" << endl << m2;
				
				m2 -= 3; // operator-=: resta 3 a cada elemento de m2
				cout << "m2 despues de -= 3:" << endl << m2;
				
				// ------------------------------------------------------------------------
				// BLOQUE OPCIONAL: DEMOSTRACIÓN DEL ITERADOR.
				// Si el examen no pide iteradores, borra todo este bloque for.
				// ------------------------------------------------------------------------
				// DEMOSTRACIÓN DEL ITERADOR 
				// (SI EL EXAMEN PIDE "SIN ITERADORES", BORRA ESTE BLOQUE FOR)
				// ------------------------------------------------------------------------
				cout << "--- RECORRIDO CON ITERADOR ---" << endl;
				CMatrix<int>::iterator it;
				for (it = m1.begin(); it != m1.end(); ++it) {
					cout << *it << " ";
				}
				cout << endl << endl;
				
				// ------------------------------------------------------------------------
				// BLOQUE OPCIONAL: PRUEBAS DE ORDENAMIENTO.
				// Si solo piden sobrecarga de operadores, borra desde aquí hasta antes
				// de la impresión final "Matriz M1 Ordenada" y borra esa impresión también.
				// ------------------------------------------------------------------------
				// PRUEBAS DE LOS MÉTODOS DE ORDENAMIENTO
				// (Descomenta ÚNICAMENTE el método que te pida el examen)
				// ------------------------------------------------------------------------
				// cout << "--- ORDENANDO LA MATRIZ ---" << endl; // Descomenta si piden ordenar
				
				// --- MÉTODO 1: NORMAL ---
				// xsort_1_Normal(m1.getMat(), m1.getRows(), m1.getCols());
				
				// --- MÉTODO 2: PUNTERO A FUNCIÓN ---
				// xsort_2_PunteroFuncion(m1.getMat(), m1.getRows(), m1.getCols(), esMenor<int>); // Menor a Mayor
				// xsort_2_PunteroFuncion(m1.getMat(), m1.getRows(), m1.getCols(), esMayor<int>); // Mayor a Menor
				
				// --- MÉTODO 3: POLIMORFISMO ---
				// CLessPoly<int> reglaMenorPoly;
				// xsort_3_Polimorfismo(m1.getMat(), m1.getRows(), m1.getCols(), &reglaMenorPoly); // Menor a Mayor
				// CGreaterPoly<int> reglaMayorPoly;
				// xsort_3_Polimorfismo(m1.getMat(), m1.getRows(), m1.getCols(), &reglaMayorPoly); // Mayor a Menor
				
				// --- MÉTODO 4: FUNCTOR ---
				// SLess<int> reglaMenorFunctor;
				// xsort_4_Functor(m1.getMat(), m1.getRows(), m1.getCols(), reglaMenorFunctor); // Menor a Mayor
				
				// --- MÉTODO 5: FUNCTOR + INLINE ---
				// SLessInline<int> reglaMenorInline;
				// xsort_5_Inline(m1.getMat(), m1.getRows(), m1.getCols(), reglaMenorInline); // Menor a Mayor
				
				// SGreaterInline<int> reglaMayorInline;
				// xsort_5_Inline(m1.getMat(), m1.getRows(), m1.getCols(), reglaMayorInline); // Mayor a Menor
				
				// cout << "Matriz M1 Ordenada:" << endl << m1; // Descomenta si piden ordenar
				
				return 0;
			}
