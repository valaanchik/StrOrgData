
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
using namespace std;
    int remem = 0;
     //  int c = 0,b = 0;
class Sort
{
    int n[4] {5000,30000,100000,120000};
    string file[4] {"C:\\Univirsity\\Str_3_1\\f1_10.txt",
                "C:\\Univirsity\\Str_3_1\\f2_100.txt",
                "C:\\Univirsity\\Str_3_1\\f3_500.txt",
                "C:\\Univirsity\\Str_3_1\\f4_1000.txt"};
    int *arr;
    long long sr_boss = 0, sr_ = 0;

    ifstream fin;
public:
    Sort () {
        arr = nullptr;
        fin.open("C:\\Univirsity\\Str_3_1\\test_numbers.txt");
        cout << "Конструктор без параметра"<< endl;
    };

    void _print_sr()
    {
        cout << "Главные сравнения: " << sr_boss<< endl;
         cout << "Побочные сравнения: " << sr_<< endl;
                 cout << "Память заниманмая сортировкой "<< remem<< endl<<endl;
        sr_boss = 0;
        sr_ = 0;
        remem = 0;
       // b=0;
      //  c=0;
    };

    int* sort_get_arr ()
    {
        return arr;
    }
    int sort_get_n (int i)
    {
        return n[i];
    }

    int Num (int j)
    {
         if (arr) delete [] arr;
            arr = new int[n[j]];
        for (int i = 0; i < n[j]; ++i)
        {
           fin >> arr[i];
        };
        fin.seekg(0, ios::beg);
        return *arr;
    };

    int Num_4_120_twin (int j)
    {
        if (arr) delete [] arr;
        ifstream f;
        f.open(file[j]);
        arr = new int[n[3]];
        for (int i = 0; i < n[3]; ++i)
        {
           f >> arr[i];
        };
        f.seekg(0, ios::beg);
        f.close();
        return *arr;
    };



    void Sort_upr (int a)
    {
        for (int i = 0; i < n[a]/2; ++i) swap(arr[i],arr[n[a]-i-1]);
    };


    void sift_revers (int *a,int L, int R) /*Просеивание сквозь пирамиду (вспомогательная функция)*/
       {

           int i = L, j = 2*L+1, x = a[L];
           if (++sr_ && j < R && ++sr_boss && a[j+1] < a[j])	  /*если элемент j не последний в рассматр. последовательности*/
               j++;/*и левый брат больше правого, переставляем указатель на него*/
           while (++sr_&& j <= R && ++sr_boss && a[j] < x)	  /*просматриваем потомков до конца последовательности,*/
           {				         /*если они меньше текущего (х) элемента, т.е. нарушена*/
               arr[i] = arr[j];       	/*упорядоченность пирамиды, то восстанавливаем ее,*/
               i = j;		        /*поднимая потомков на уровень выше*/
               j = 2*j + 1;
               if (++sr_ && j < R && ++sr_boss && a[j+1] < a[j])	/*и каждый раз выбираем для анализа меньшего из*/
                   j++;			/*братьев*/
           }
           arr[i] = x;
       }


       void HeapSort_revers (int a)// Пирамидальная сортировка по убыванию
       {
            remem+=sizeof (int)*8+sizeof (int*);
           int L = n[a]/2, R=n[a]-1, x;
           while (++sr_&&L>0)
               sift_revers(arr, --L, R);

           while (++sr_&&R>0)
           {

               x = arr[0];
               arr[0] = arr[R];
               arr[R] = x;
               sift_revers(arr, L, --R);
           }
       }

       void BubbleSort (int a)
       {
            remem+=sizeof (int)*3;
           int i, j, x;
           for (i=1;++sr_ && i<n[a]; i++)
               for (j=n[a]-1;++sr_ && j>=i; j--)
                   if (++sr_boss && arr[j-1]<arr[j])
                   {
                       x = arr[j-1];
                       arr[j-1] = arr[j];
                       arr[j] = x;
                   }
       }

       void StraightSelection (int a)
       {
            remem+=sizeof (int)*4;
           int i, j, tmp, *max;
           for (i=0;++sr_, i<n[a]-1; i++)
           {
               max = arr+i;
               for (j=i+1;++sr_, j<n[a]; j++)
                   if (++sr_boss,arr[j]>*max)
                       max = arr+j;
               tmp = *max;
               *max = arr[i];
               arr[i] = tmp;
           }
       }
       int QuickSort (int *a, int n)
       {
           int x, w, i, j;
           x = a[n/2];
           i=0; j=n-1;
             int c = 0, b = 0;
           do
           {
               while ( ++sr_boss && a[i]>x) i++;
               while (++sr_boss && x>a[j]) j--;
               if (++sr_ && i<=j)
               {
                   w = a[i];
                   a[i] = a[j];
                   a[j] = w;
                   i++; j--;
               }
           }
           while (++sr_ && i<j);
           if (++sr_ && j>0)
              {c = QuickSort (a, j+1);};
           if (++sr_ && i<n-1)
           {b= QuickSort (a+i, n-i);};

           if (c > b )  return sizeof (int)*4 +c;
           else  return sizeof (int)*4 +b;
       }

    void _print ()
    {
        cout << "Array 10"<<endl;
        for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    };
    ~Sort () {delete [] arr;
              fin.close();
             }
};

int main()
{
      system ("chcp 65001");
   clock_t t;
   Sort mas;
   int marker;

   int choice;
   while (true)
   {

       cout <<endl<< "1.Массив 5.000 элеметов" << endl
            << "2.Массив 30.000 элементов" << endl
            << "3.Массив 100.000 элементов" << endl
            << "4.Массив 120.000 элементов" << endl
            << "5.Сортировка выбором по убыванию" << endl
            << "6.Сортировка Пузырьком" << endl
            << "7.Пирамидальная сортировка" << endl
            << "8.Быстрая сортировка" << endl
            << "9.Сделать упорядоченным " << endl
            << "0. Выход" << endl;

       cout<<"Ввод ";
    cin>>choice ;
   switch (choice) {
   case 1: {
       cout<<mas.sort_get_n(0)<<endl;
       marker = 0;
       mas.Num(0);
       mas._print();
       break;
     };
   case 2: {
       marker = 1;
        mas.Num(1);
       mas._print();
       break;
     };
   case 3: {
       marker = 2;
        mas.Num(2);
       mas._print();
       break;
     };
   case 4: {
       cout <<endl<< "1.Массив без повтроных ключей" << endl
            << "2.Массив 10 повторных ключей " << endl
            << "3.Массив 100 повторных ключей" << endl
            << "4.Массив 500 повторных ключей" << endl
            << "5.Массив 1000 повторных ключей" << endl;
       cout << "" << endl;
       marker = 3;
       cout<<"Ввод ";
       cin >> choice;
       if (choice == 1)
       {
            mas.Num(3);
            mas._print();
       } else if (choice == 2)
       {
           mas.Num_4_120_twin(0);
           mas._print();
       } else if (choice == 3)
       {
           mas.Num_4_120_twin(1);
           mas._print();
       } else if (choice == 4)
       {
           mas.Num_4_120_twin(2);
           mas._print();
       } else if (choice == 5)
       {
           mas.Num_4_120_twin(3);
           mas._print();
       } else cout << " Не правильный ввод " << endl;
       break;
     };
   case 5: {
       mas.Sort_upr(marker);
        cout << " СОРТИРОВКА ВЫБОРОМ " << endl;
       t = clock();
       mas.StraightSelection(marker);
       cout<< endl << "Время выполнения: " << clock() - t<< " мс " << endl;
       mas._print_sr();
       mas._print();

       break;
     };
   case 6: {
       mas.Sort_upr(marker);
        cout << " ПУЗЫРЬКОВАЯ СОРТИРОВКА " << endl;
       t = clock();
       mas.BubbleSort(marker);
       cout<< endl << "Время выполнения: " << clock() - t<< " мс " << endl;
       mas._print_sr();
       mas._print();

       break;
     };
   case 7: {
       mas.Sort_upr(marker);
       cout << " ПИРАМИДАЛЬНАЯ СОРТИРОВКА " << endl;
       t = clock();
       mas.HeapSort_revers(marker);
       cout<< endl << "Время выполнения: " << clock() - t << " мс " << endl;
       mas._print_sr();
       mas._print();
       break;
     };
   case 8: {
       cout << " БЫСТРАЯ СОРТИРОВКА " << endl;
       t = clock();
       mas.Sort_upr(marker);
       remem = mas.QuickSort(mas.sort_get_arr(),mas.sort_get_n(marker));
       cout<< endl << "Время выполнения: " << clock() - t << " мс " << endl;
       mas._print_sr();
       mas._print();
       break;
     };
   case 9: {

       cout << " Упорядочивание от меньшего к большему " << endl;
       mas.Sort_upr(marker);
       mas._print();
       break;
     };

   case 0: {
       return 0;
       break;
     };
   default: cout<<"Не правильный ввод"<<endl;
    }

   }

    return 0;
}
