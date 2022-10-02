
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define UP"�------------------------T--------T-----------T---------------T---------------T---------------�\n��������� �������        �   ���� �   ���-��  �    ������� �� � ������� ��    ������������    �"
#define MIDDLE "�------------------------+--------+-----------+---------------+---------------+---------------�"
#define STR "\n� %-22s �%-8g�%-11d�%-15d�%-15d�%-15s�"
#define BOTTOM "L---------------------------------------------------------------------------------------------"
#define Matr "�������� �������: %s\n"
#define Det "���-�� �������: %d\n"


#define N 90
#define TOY_PAGE 3

/* */


using namespace std;

typedef struct toy
{
  char name[N];
  double price;
  int quantity;
  char age_min;
  char age_max;
  char type;// 0 ����������� 1 ������
    union
    {
        int details;
        char material [15];
    } avaible;



} toy;

void Menu();
int Open(FILE **file, char path[], char rights[]);
void Close(FILE **file);
void View();
void View_Revers();
void AddData();
void CreateFilef();
void ToySearch();
void MaxConstructor();
void ToyDelete();


class List
{
 private:
  typedef struct node
  {
    struct toy item;
    node *next = nullptr;
    node *prev = nullptr;
  } node;


  node *_first = nullptr;
  node *_last = nullptr;
  node *_cur = nullptr;
  bool _direction = true;

  void _add_start(const struct toy a)
  {
    if (!_first)
    {
      _first = new node;
      _first->item = a;
      _last = _first;
    }
    else
    {
      node *new_node = new node;
      new_node->item = a;
      new_node->next = _first;
      _first->prev = new_node;
      _first = new_node;
    }
  }

  void _add_end(const struct toy a)
  {
    if (!_last)
    {
      _last = new node;
      _last->item = a;
      _first = _last;
    }
    else
    {
      node *new_node = new node;
      new_node->item = a;
      new_node->prev = _last;
      _last->next = new_node;
      _last = new_node;
    }
  }

 public:

     int Schet = 0;

  void add(const struct toy a)
  {
    Schet++;
    if (!_first)
    {
      _add_start(a);
    }
    else
    {
      node *p = _first, *new_node = new node;
      new_node->item = a;

      while (p->next && p->item.price > a.price) p = p->next;

      if (p->next)
      {
        new_node->next = p;
        new_node->prev = p->prev;
        p->prev = new_node;
        if (new_node->prev)
          new_node->prev->next = new_node;
        else
          _first = new_node;
      }
      else
      {
        _add_end(a);
      }
    }
  }



  void del(const unsigned int a)
  {
    --Schet;
    node *p = _first;
    for (int i = 0; i < a; i++) p = p->next;

    if (p->next)
    {
      p->next->prev = p->prev;

      if (p->prev)
        p->prev->next = p->next;
      else
        _first = p->next;
    }
    else
    {
      if (p->prev)
      {
        p->prev->next = nullptr;
        _last = p->prev;
      }
      else
      {
        _first = nullptr;
        _last = nullptr;
      }
    }
  }

  toy getn(void)
  {
    if (_direction)
      if (_cur && _cur->next)
        _cur = _cur->next;
      else
        _cur = _first;
    else if (_cur && _cur->prev)
      _cur = _cur->prev;
    else
      _cur = _last;

    return _cur->item;
  }

  toy getn_revers(void)
  {

    if ( _direction)

        if (_cur && _cur->prev)
            _cur = _cur->prev;
        else
            _cur = _last;
       else if (_cur && _cur->next)
         _cur = _cur->next;
   else
      _cur = _first;

    return _cur->item;
  }


  void changeDirection(void) { _direction = !_direction; }

  bool eol(void)
  {
    if (_direction && _cur == _last || !_direction && _cur == _first)
      return true;
    else
      return false;
  }

    bool start_check(void)
  {
    if (_direction && _cur == _first)
      return true;
    else
      return false;
  }

  void resetCur() { _cur = _last; }

  void resetCur_revers() { _cur = _first; }


  void set(const int a, const toy t)
  {
    node *p = _first;
    for (int i = 0; i < a; i++) p = p->next;
    p->item = t;
  }


  ~List()
  {
    while (_first)
    {
      _cur = _first->next;  // ��������� ������ �� ��������� �������
      delete _first;        // ������� �������
      _first = _cur;
    }
    _last = nullptr;
  }
};

List *list = new List();
char filename[N];

int main(int argc, char *argv[])
{

SetConsoleCP(1251);
SetConsoleOutputCP(1251);
  //  setlocale(LC_ALL, "Rus");
  //system("chcp 1251");
  if (argc == 2)
  {
    strcpy(filename, argv[1]);
  }
  else if (argc == 1)
  {

    printf (" ������� ��� �����: ");
    scanf ("%s", filename);
  }
  else
  {
    return -1;
  }

  FILE *f;

  if (Open(&f, filename, "rb"))
  {
    struct toy current;
    fread(&current, sizeof(struct toy), 1, f);
    while (!feof(f))
    {
      list->add(current);
      fread(&current, sizeof(struct toy), 1, f);
    }

    Close(&f);
  }

  Menu();

  if (Open(&f, filename, "wb"))
  {
    toy current;

    for (int i = 0; i < list -> Schet; i++)
    {
      current = list->getn();
      fwrite(&current, sizeof(struct toy), 1, f);
    }

    Close(&f);
  }

  delete list;
  return 0;
}

void Menu()
{
  int choice;

  do
  {

    puts("1. �������� �����");
    puts("2. ���������� ������");
    puts("3. �������� ����������� ������");
    puts("4. �������� ����������� � �������� ������� ������");
    puts("5. ����� �������");
    puts("6. �������� � ����� ������� ������������");
    puts("7. �������� ������");
    puts("0. ��������� ���������\n");

    printf("������� ����� ����: ");
    while (!scanf("%d", &choice))
    {
      printf("������� �������� ������!\n������� ����� ����: ");

    }

    switch (choice)
    {
      case 1:
        CreateFilef();
        break;
      case 2:
        AddData();
        break;
      case 3:
        View();
        break;
      case 4:
        View_Revers();
        break;
      case 5:
        ToySearch();
        break;
      case 6:
        MaxConstructor();
        break;
      case 7:
        ToyDelete();
        break;

      case 0:

        break;
      default:
        puts("������ �������� ����� ����!");
    }

  } while (choice);
}

int Open(FILE **file, char path[], char rights[])
{
  if ((*file = fopen(path, rights)) == NULL)
  {

    printf("������ �������� �����!\n");
    getchar();
    return 0;
  }
  else
  {
    return 1;
  }
}

void Close(FILE **file)
{
  if (*file != NULL)
  {
    fclose(*file);
  }
}


void View()
{
  // �������� ���� ������� � �����

    int i, j;
  toy current;
  char choice;
  while (true)
  {


    if (list -> Schet)  // ���� �� � ������ ������?
    {
      puts(UP);
      for (i = 0; i < TOY_PAGE; i++)  // �������� TOY_PAGE ��������� �������
      {
        printf(MIDDLE);

        current = list->getn();  // �������� ��������� ������� ������


        printf(STR, current.name, current.price, current.quantity,
               current.age_min, current.age_max,
               current.type == '0' ? " �� " : " ��� ");
               (current.type == '0') ?  printf(Det, current.avaible.details) : printf(Matr,current.avaible.material);

        if (list->eol())  // �������� �� ����� ������
          break;
      }
      puts(BOTTOM);
      puts("<--1   0-�����   2-->");

      do
      {
        printf("����: ");
        while (!scanf("%*c%c", &choice))
        {
          printf("������ �����!\n����: ");
        }

        if (choice != '1' && choice != '0' && choice != '2') printf("����������� �������!\n");
      } while (choice != '1' && choice != '0' && choice != '2');

      if (choice == '1')  // ���� ��������� �������
      {
        list->changeDirection();  // ������ ����������� ������ ������

        for (j = 0; j < TOY_PAGE + i + 1; j++)  // ������������ �� �������� �����
        {
          list->getn();

          if (list->eol())  // �������� �� ����� ������
          {
            list->getn();
            break;
          }
        }

        list->changeDirection();
      }
      else if (choice == '0')
      {
        list->resetCur();  // ������ ��������� � ��������� ���������
        return;
      }
    }
    else
    {
      puts("� ������ ����������� ������");
      getchar();
      break;
    }
  }
}

void View_Revers()
{

  //    �������� ���� ������� � ������
int i, j;
  toy current;
  char choice;
  list ->resetCur_revers(); // ���������� ��������� �� ������ ��� �� ������ ���������� ��������
  while (true)
  {

    if (list->Schet)  // ���� �� � ������ ������?
    {
      puts(UP);
      for (i = 0; i < TOY_PAGE; i++)  // �������� TOY_PAGE ��������� �������
      {
        printf(MIDDLE);

        current = list->getn_revers();  // �������� ���������� ������� ������

        printf(STR, current.name, current.price, current.quantity,
               current.age_min, current.age_max,
               current.type == '0' ? " �� " : " ��� ");
               (current.type == '0') ?  printf(Det, current.avaible.details) : printf(Matr,current.avaible.material);

       if (list->start_check())  // �������� �� ������ ������
          break;
      }
      puts(BOTTOM);
      puts("<--1   0-�����   2-->");

      do
      {
        printf("����: ");
        while (!scanf("%*c%c", &choice))
        {
          printf("������ �����!\n����: ");
        }

        if (choice != '1' && choice != '0' && choice != '2') printf("����������� �������!\n");
      } while (choice != '1' && choice != '0' && choice != '2');

      if (choice == '1')  // ���� ��������� �������
      {
        list->changeDirection();  // ������ ����������� ������ ������

        for (j = 0; j < TOY_PAGE + i + 1; j++)  // ������������ �� �������� �����
        {
          list->getn_revers();

          if (list->start_check())  // �������� �� ������ ������
          {
            list->getn_revers();
            break;
          }
        }

        list->changeDirection();
      }
      else if (choice == '0')
      {
        list->resetCur();  // ������ ��������� � ��������� ���������
        return;
      }
    }
    else
    {
      puts("� ������ ����������� ������");
      getchar();
      break;
    }
  }
}




void AddData()
{
  int choice, _type ;
  struct toy newt;


  printf("������� �������� �������: ");
  scanf("%s", &newt.name);
  printf("������� ����: ");
  scanf("%lf", &newt.price);
  printf("������� ����������: ");
  scanf("%d", &newt.quantity);
  printf("������� ����������� �������: ");
  scanf("%d", &newt.age_min);
  printf("������� ������������ �������: ");
  scanf("%d", &newt.age_max);
  printf("������� ������� �������� �� ������������� (0-�� 1-���) ");
  getchar();
  newt.type = getchar() ;
  if (newt.type == '0')
    {
        printf("������� ���������� ������� � ������������: ");
        scanf("%d", &newt.avaible.details);
    }
  else
    {
        printf("������� �������� �������: ");
        scanf("%s", &newt.avaible.material);
    };

  list->add(newt);
    list->resetCur();
  printf("\n������ ���������!\n");
}



void CreateFilef()
{
  FILE *f;
  if (Open(&f, filename, "w"))
  {
    printf("���� ������!\n");
    Close(&f);
  }
}



void ToySearch()
{

  int age;
  double price;
  toy current;

  do
  {
    printf("������� ������� � ���� (��): ");
    while (scanf("%d%lf", &age, &price) != 2)
    {
      printf("������ �����!\n������� ������� � ����: ");
    }
    if (age < 0 || price < 0) printf("������� ������������� ��������!\n");
  } while (age < 0 || price < 0);


  puts(UP);
    for (int i = 0; i < list->Schet; i++)
    {
        current = list->getn();
        if (current.age_min <= age && current.age_max >= age && current.price <= price)
        {
        printf(MIDDLE);
        printf(STR, current.name, current.price, current.quantity,
               current.age_min, current.age_max,
               current.type == '0' ? " �� " : " ��� ");
               (current.type == '0') ?  printf(Det, current.avaible.details) : printf(Matr,current.avaible.material);
        }
    }
    puts(BOTTOM);

  list->resetCur();
  printf("��� ����������� ������� ����� �������...\n");
  getchar();
}

void MaxConstructor()
{

  double max_price = 0;
  toy current, current_get;

  for (int i = 0; i < list->Schet; i++)
  {
    current = list->getn();
    for (int j = 0; j < N; j++)
      if (current.type == '0' && max_price < current.price)
       {
        max_price = current.price;
        current_get = current;
       }
  }
  list->resetCur();

    if (max_price != 0)
    {

                puts(UP);
                printf(MIDDLE);
                printf(STR, current_get.name, current_get.price, current_get.quantity,
               current_get.age_min, current_get.age_max,
              current.type == '0' ? " �� " : " ��� ");
               current_get.type == '0' ?  printf(Det, current_get.avaible.details) : printf(Matr,current_get.avaible.material);
                puts(BOTTOM);

                printf("��� ����������� ������� ����� �������...\n");
                getchar();


    list->resetCur();
    }
    else {
            printf("� ������ ��� ������������. \n");
            printf("��� ����������� ������� ����� �������...\n");
                getchar();
         };
}

void ToyDelete()
{

  FILE *f, *t;
  char del[N], choice;
  struct toy current;

  printf("������� �������� �������: ");
  scanf("%s", del);
  for (int i = 0; i < list->Schet ; i++)
  {
    current = list->getn();
    if (!strcmp(current.name, del))
    {
      puts(UP);
      printf(MIDDLE);
      printf(STR, current.name, current.price, current.quantity,
               current.age_min, current.age_max,
               current.type == '0' ? " �� " : " ��� ");
               (current.type == '0') ?  printf(Det, current.avaible.details) : printf(Matr,current.avaible.material);
      puts(BOTTOM);

      do
      {
        printf("\n�� ������ ������� ������ �����?\n1 - �� 0 - ���\n"); getchar();
        scanf("%c", &choice);
        if (choice != '1' && choice != '0') printf("������ �����!\n");
      } while (choice != '1' && choice != '0');

      if (choice == '1')
      {
        list->del(i);
        break;
      }
    }
  }
  list->resetCur();
}

