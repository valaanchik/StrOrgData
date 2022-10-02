#include <iostream>
#include <fstream>
#include<windows.h>

const int mark = 150;
using namespace std;

int Alg_FW(int **_matrix, int n);
int Init_File(int **_matrix);


int main()
{
  system ("chcp 65001");
 int **_matrix;
 int _village;


_village = Init_File(_matrix);


cout<< endl<< "\t\tРеализация матрицей весов " << endl<< endl;;


cout<< endl<< "Фельдшерский пункт нужно расположить в " << _village+1 << " деревне. "<< endl;


return 0;
}

int Alg_FW(int **_matrix, int n)
{
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = i;  j < n; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                _matrix[i][j] = min(_matrix[i][j], _matrix[i][k] + _matrix[k][j]);
            }
        }
    }

    for(int i = 0; i < n; ++i)
    {
        cout << endl;
        for (int b = 0; b < i; b++) cout <<' ';
        for(int j = 0; j < n; ++j)
        {

           cout << _matrix[i][j] << " ";
        };
    };


int j, rad = mark, g, p = 0;
    for(int i = 0 ; i < n; i++)
        {
             for(int j = 0; j < n; j++)   p = max(p,_matrix[i][j]);

            rad = min(rad, p);
            if (rad==p) g = i;
            p=0;
    }


 return g;
};

int Init_File(int **_matrix)
{
    int n;
    int ret_Vil;
    char F_reliz;
    char buf;
    ifstream fin;
fin.open("C:\\Univirsity\\Pr_2_3-DOS\\G_List_5.txt");
if (fin){
  fin >> n;
  fin >> F_reliz;

  cout << n << endl;
    int **_matrix;
        _matrix = new int*[n];
        for (int i = 0; i < n; ++i) _matrix[i] = new int[n];

    if  (F_reliz == 'M')
    {
      for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
        {
           fin >> _matrix[i][j];
        };

    for(int i = 0; i < n; ++i)
    {
        cout << endl;
        for (int b = 0; b < i; b++) cout <<' ';
        for(int j = i; j < n; ++j)
        {

           cout << _matrix[i][j] << " ";
        };
    };


    cout << endl;


    for (int i = 0; i < n; ++i)
    {   for(int j = 0; j < n; ++j)
        {

                if (_matrix[i][j] == -1) _matrix[i][j] = mark;

           }

        };

    for(int i = 0; i < n; ++i)
    {
        cout << endl;
        for (int b = 0; b < i; b++) cout <<' ';
        for(int j = i; j < n; ++j)
        {

           cout << _matrix[i][j] << " ";
        };
    };
    }
else
    {
        bool sop = true;
        int _j = 0,_i = 0;


        for(int i = 0; i < n ; ++i)
          for(int j = 0 ; j  < n ; ++j)
          {
             if (sop)
             {
                 fin >> _i;
                 fin >> _j;
                 sop = false;
             }
             if (i == j) _matrix[i][j] = 0;
             else _matrix[i][j] = mark;
             if (j == _i)
                {
                 _matrix[i][j] = _j;
                 sop = true;
                }

          };

        for(int i = 0; i < n; ++i)
        {
            cout << endl;
            for (int b = 0; b < i; b++) cout <<' ';
            for(int j = 0; j < n; ++j)
            {

               cout << _matrix[i][j] << " ";
            };
        };
    };


    fin.close();

   ret_Vil = Alg_FW(_matrix, n);
   for (int i = 0; i < n; ++i) delete[] _matrix[i];
   delete[] _matrix;

}
else cout <<"Ошибка открытия файла ";
return ret_Vil;
};
