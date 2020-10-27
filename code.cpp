#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
//ГЛОБАЛЬНЫЕ ИЗМЕНЕНИЯ)
//добавил ещё один комментарий
//новый комментарий
//создание и заполнение СЛАУ
float** create_matrix(unsigned n) {
    float** m = new float*[n];//указатель на указатели
    for (unsigned i = 0; i < n; i++) {
        m[i] = new float [n+1];
    }
    //Цикл заполнения
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j <= n; j++) {
            if (j < n) {
            cout << "a[" << i+1 << "][" << j+1 << "]= ";
                              cin >> m[i][j];
            }
            else {
                cout << "y[" << i+1 << "]= ";
                                  cin >> m[i][j];
            }

        }

    }
    return m;
}

//выделение памяти под СЛАУ
float** create_matrix_NULL(unsigned n) {
    float** m = new float* [n];
    for (unsigned i = 0; i <= n; i++) {
        m[i] = new float[n+1];
    }
    return m;
}


//вывод СЛАУ на экран
void out_sistem(float **a, unsigned n)
{
  for (unsigned i = 0; i < n; i++)
  {
    for (unsigned j = 0; j < n; j++)
    {
      cout << a[i][j] << "*x" << j+1;
      if (j < n - 1)
        cout << " + ";
      else
       cout << " = " << a[i][j+1] << endl;
    }
  }
  return;
}

//деление массива на элемент
float* division_array(float* mas, unsigned n, unsigned ind) {
    float r = mas[ind];
    float* m = new float[n];
    for (unsigned i = 0; i <= n; i++) {
        m[i] = mas[i] / r;
    }
    return m;

}

//обмен строк
void swap_rows(float** m, unsigned n, unsigned ind1, unsigned ind2) {
    float a;
    for (unsigned l = 0; l <= n; l++) {//метод пузырька
        a = m[ind1][l];
        m[ind1][l] = m[ind2][l];
        m[ind2][l] = a;
    }
}

//копирование матрицы в новую
void copy_mat(float** m, float** newm, unsigned n) {
    for (unsigned p = 0; p < n; p++) {
        for (unsigned l = 0; l <= n; l++) {
            m[p][l] = newm[p][l];
        }
    }
}

//обратный ход
float* reverse_step(float** m, unsigned n) {
    float* Xs = new float[n];
    for (int i = n - 1; i >= 0; i--) {
        Xs[i] = m[i][n];
        for (int p = n-1; p > i; p--) {
            Xs[i] -= m[i][p]*Xs[p];
        }
    }
    return Xs;
}

//Функция Метод Гауса
float* method_Gayyss(float** m, unsigned n) {
    float** newm = create_matrix_NULL(n);
    for (unsigned k = 0; k < n; k++) {
        //Получение единиц на главной диагонали
        if (m[k][k] != 1) {
            if (m[k][k] != 0) {
                newm[k] = division_array(m[k], n, k);
            }
            else {
                for (unsigned i = k + 1; i < n; i++) {
                    if (m[i][k] != 0) {
                        swap_rows(m, n, k, i);
                        if (m[k][k] != 1) {
                            newm[k] = division_array(m[k], n, k);
                        }
                    }
                }
            }
        }
        else {
            for (unsigned i = 0; i <= n; i++) {
                newm[k][i] = m[k][i];
            }
        }
        //Подсчет элементов последующих строк
        for (unsigned i = k + 1; i < n; i++) {
            for (unsigned j = k + 1; j <= n; j++) {
                newm[i][j] = (m[i][j] * m[k][k] - m[k][j] * m[i][k]) / m[k][k];
            }
        }

        //Обнуление элементов под k-тым стобцом
        for (unsigned i = k + 1; i < n; i++) {
            newm[i][k] = 0;
        }
        //Сохранение изменений
        copy_mat(m, newm, n);
    }
    return reverse_step(m, n);//вызов функции подсчета корней и возврат результат работы функции
}

//функция для поиска невязок
void nevazky(float**m, float*r, unsigned n) {
    float* D = new float[n];
    bool F = false;
    float eps = 0.001; //необходимая точность
        for (unsigned i = 0; i < n; i++) {//Подсчет значений
            D[i] = m[i][n];
            for (unsigned k = 0; k < n; k++) {
                D[i] -= m[i][k] * r[k];
            }
            if (D[i] >= eps) { F = true;}//сравнение значений с eps
        }
        //если невязки присутствуют
        if (F) {
            float** NM = create_matrix_NULL(n);
            float* Y = new float[n];
            //Создание и заполнение новой системы
            copy_mat(NM, m, n);
            for (unsigned i = 0; i < n; i++) {
                NM[i][n] = D[i];
            }
            //Решение новой системы
            Y = method_Gayyss(NM,n);
            //Пересчитывание Корней
            for (unsigned i = 0; i < n; i++) {
                r[i] += Y[i];
            }
            //Рекурсия
            nevazky(m, r, n);
        }
        //Вывод сообщения о завершении процедуры
        cout << "test completed" << endl;

}

//Вывод решения на экран
void out_X (float* a, unsigned n){
    for (unsigned i = 0; i < n; i++) {//Цикл для вывода Корней на экран
        cout << "X" << i + 1 << "=" << a[i]<<endl;
    }
}

void delete_matrix(float**a, unsigned n){
    for (unsigned i = 0; i <n;i++) {//Очистка памяти
        delete[] a[i];
    }
    delete[] a;
}

int main()

{
    unsigned n;
    cout<<"The number of equations SLOUGH = ";
    cin >> n ;
    float** mat;// матрица для работы
    float** smat;//матрица, в которой сохранены начальные кэфициенты
    float* X;//масcив для решений СЛАУ
    mat = create_matrix(n); //Выделение памяти и заполнение робочей матрицы
    smat = create_matrix_NULL(n); //Выделение памяти под матрицу начальных коэф.
    copy_mat(smat,mat,n); //Копирование данных
    out_sistem(mat, n); //Вывод СЛАУ на экран
    X = method_Gayyss (mat, n);
    nevazky(smat, X, n); //Проверка на невязки
    out_X(X,n);
    delete_matrix(mat,n);//освобождение памяти
    return 0;
}
