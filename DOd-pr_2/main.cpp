/*
Бабушка печет внукам блинчики с разными рисунками: цветочком,
грибочком, котенком, – и складывает их в стопку. Поджарив 25 блинчиков, она
зовет внуков к столу, продолжая выпечку. Верхний блин горячий, поэтому
внуки переворачивают стопку и берут блинчики, оказавшиеся теперь сверху
стопки. Бабушка вновь испеченный блинчик опять кладет на верх стопки, он
горячий, и внуки сразу стопку переворачивают. Один блинчик бабушка печет
минуту, каждый внук успевает съесть блинчик за 30 секунд. Теста у бабушки
хватает на 50 блинчиков. Каждый внук может съесть от 8 до 15 блинчиков
(задается случайным образом). Насытившись, ребенок уходит от стола.
Бабушка продолжает выпечку, пока не кончится тесто. Число внуков (от 2 до
4) задается пользователем.
Работа программы должна сопровождаться выводом на экран
сообщений: какой (с каким рисунком) блин испекла бабушка, какой блин съел
внук, хватило ли внукам блинчиков, чтобы наесться, осталось ли что-нибудь
самой бабушке и другим домочадцам (если блинчики остались, то в каком
количестве).
*/

/*
1. Исправила удаление передает значение
2. Добавила проверку переполнености
3. Убрала дублирующий код  с помощью тетрарной операции
4. Убрала ошибку у массива(выход за пределы)
*/
#include <iostream>


#define count_blini 50
#define StartCountBlini 25 // при изменении + изменить ренд

using namespace std;

enum picture {
    flower,
    mashroom,
    kitten,
    last
};


class Deque
{
 public:
  virtual bool addStart(const int a) = 0;
  virtual bool addEnd(const int a) = 0;
  virtual int delStart(void) = 0;
  virtual int delEnd(void) = 0;
  virtual int readStart(void) = 0;
  virtual int readEnd(void) = 0;
  virtual bool isEmpty(void) = 0;
  virtual bool isCrowded(void) = 0;

  virtual ~Deque() = default;
};

class ListDeque : public Deque
{
 private:
    typedef struct node
  {
    int num;
    int const n = count_blini;
 node *next = nullptr;
    node *prev = nullptr;
  } node;

  node *_first = nullptr;
  node *_last = nullptr;

 public:
  bool addStart(const int a) override
  {
    if (!_first)
    {
      _first = new node;
      _first->num = a;
      _last = _first;
      return true;
    }
    else
    {
      node *new_node = new node;
      new_node->num = a;
      new_node->next = _first;
      _first->prev = new_node;
      _first = new_node;
      return true;
    }

    return false;
  }

  bool addEnd(const int a) override
  {
    if (!_last)
    {
      _last = new node;
      _last->num = a;
      _first = _last;
      return true;
    }
    else
    {
      node *new_node = new node;
      new_node->num = a;
      new_node->prev = _last;
      _last->next = new_node;
      _last = new_node;
      return true;
    }

    return false;
  }

  int delStart(void) override
  {
    int _getDel;
    _getDel = _first -> num;
    if (_first)
    {
      if (_first->next)
      {
        node *p = _first->next;
        p->prev = nullptr;
        delete _first;
        _first = p;
      }
      else
      {
        delete _first;
        _first = nullptr;
        _last = nullptr;
      }
    }
    return _getDel;
  };

  int delEnd(void) override
  {
    int _getDel;
    _getDel = _last -> num;
    if (_last)
    {
      if (_last->prev)
      {
        node *p = _last->prev;
        p->next = nullptr;
        delete _last;
        _last = p;
      }
      else
      {
        delete _last;
        _last = nullptr;
        _first = nullptr;
      }
    }
    return _getDel;
  }

  int readStart(void) override { return _first->num; }

  int readEnd(void) override { return _last->num; }

  virtual bool isEmpty(void) override
  {
    if (!_first)
      return true;
    else
      return false;
  }
  virtual bool isCrowded(void) override
  {
    if (_first)
      return true;
    else
      return false;
  }

  ~ListDeque()
  {
    while (_first)
    {
      _last = _first->next;  // сохраняем ссылку на следующий элемент
      delete _first;         // удаляем текущий
      _first = _last;
    }
  }
};

class VectorDeque : public Deque
{
 private:
  int _size = 0;

  int *_end = nullptr;
  int *_head = nullptr;

  int *_first = nullptr;
  int *_last = nullptr;

 public:
  VectorDeque(const int size)
  {
    _size = size;
    _head = new int[size];
    _end = _head + _size - 1;
  }

  bool addStart(const int a) override
  {

    if (!_first)
    {
      _first = _last = _head;
      *_first = a;
      return true;
    }
    else if ( _head == _first)
    {
      _first = _end;
      *_first = a;
      return true;
    }
    else
    {
      _first--;
      *_first = a;
      return true;
    }

  }

  bool addEnd(const int a) override
  {

    if (!_first)
    {
      _first = _last = _head;
      *_last = a;
      return true;
    }
    else if (_last == _end)
    {
      _last = _head;
      *_last = a;
      return true;
    }
    else
    {
      _last++;
      *_last = a;
      return true;
    }

  }

  int delStart(void) override
  {
    int _getDel;
    _getDel = *_first;
    if (_first == _last)
      _first = _last = nullptr;
    else if (_first == _end)
      _first = _head;
    else
      _first++;
    return _getDel;
  };

  int delEnd(void) override
  {
      int _getDel;
      _getDel = *_last;
    if (_first == _last)
      _first = _last = nullptr;
    else if (_last == _head)
      _last = _end;
    else
      _last--;
    return _getDel;
  }

  int readStart(void) override
  {
    if (_first) return *_first;
    return -1;
  }

  int readEnd(void) override
  {
    if (_last) return *_last;
    return -1;
  }

  bool isCrowded(void) override
  {
    if (_first)
      return true;
    else
      return false;
  }
  bool isEmpty(void) override
  {
    if (_first)
      return false;
    else
      return true;
  }


  ~VectorDeque() { delete[] _head; }
};



int main()
{

    system ("chcp 65001");
    Deque *_deque;
    picture blini;
    int choice, vnuchata = 0, _count = 0,  testo = 0, a;
    string message;

    do
    {
      cout << "1. Дек с помощью связной структуры данных" << endl
           << "2. Дек с помощью векторной структуры данных" << endl;

      cout << "Ввод: ";
      cin >> choice;
      switch (choice)
      {
        case 1:
          _deque = new ListDeque();
          break;
        case 2:
          _deque = new VectorDeque(count_blini); //У бабушки тесто на 50 блинчиков
          break;
        default:
          cout << "Ошибка ввода!" << endl;
      }
    } while (choice != 1 && choice != 2);

    cout << "\n\tБабушка решила испечь блинчики. " << endl << endl;
    for (int i = 0; i < StartCountBlini ; i++ )
    {
            testo++;
            blini = static_cast<picture>(rand() % last);
            message = (blini == flower) ? "Цветочком" : (blini == kitten) ? "Котенком" : "Грибочком";
            cout << testo << ". Бабушка испекла блинчики с " << message << endl;
            _deque -> addEnd(blini);


    };

    cout << "\nБабушка зовёт внуков кушать блинчики. " << endl << endl;

    cout << "\n Сколько пришло внуков (от 2 до 4): ";
    cin >> vnuchata;

    int _vnuchata[vnuchata];
    for (int i = 0; i < vnuchata; i++)
    {
        _vnuchata[i] = rand() % 10 + 8; //Сколько блинов нужно внукам чтобы наесться
        _count+=_vnuchata[i];
        cout << "Внучок "<< i + 1 <<" может съесть " << _vnuchata[i] << " блинчиков." << endl << endl;
    }

   do
    {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < vnuchata; j++)
                {
                 if (_vnuchata[j] != 0 && !_deque->isEmpty())
                     {
                    testo % 2 ?  blini = static_cast<picture>(_deque ->readStart()) :
                                 blini = static_cast<picture>(_deque ->readEnd());
                    message = (blini == flower) ? "Цветочком" : (blini == kitten) ? "Котенком" : "Грибочком";
                     cout << "Внучок "<< j + 1 <<" съел блинчик с " << message << endl;
                     a = testo % 2 ? _deque->delStart() : _deque->delEnd(); ;
                    // cout << a << endl;
                      _vnuchata[j]--;
                     }
                };
            };

            blini = static_cast<picture>(rand() % last);
            message = (blini == flower) ? "Цветочком" : (blini == kitten) ? "Котенком" : "Грибочком";
            cout << endl << testo <<". Бабушка испекла блинчики с " << message << endl<< endl;
            testo % 2 ? _deque -> addStart(blini) : _deque ->addEnd(blini);

            testo++;

     } while (testo < count_blini);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < vnuchata; j++)
        {
         if (_vnuchata[j] != 0 && !_deque->isEmpty())
             {
             blini = static_cast<picture>(_deque ->readEnd());
            message = (blini == flower) ? "Цветочком" : (blini == kitten) ? "Котенком" : "Грибочком";
             cout << "Внучок "<< j <<" съел блинчик с " << message << endl;
             _deque->delEnd();
             _vnuchata[j]--;
             }
        };
    };

   if (_deque ->isEmpty())
   {
       cout << "\n\nВсе блинчики съедены. " <<endl;
       for (int i = 1; i < vnuchata + 1; i++)
       {
        if (_vnuchata[i] > 0)
            cout << "Внучок " <<  i + 1 << " не наелся." << endl;
       }
   }
   else
       cout << "Осталось " << testo-_count  << " блинчиков. "<<endl;


  delete _deque;
  return 0;
}
