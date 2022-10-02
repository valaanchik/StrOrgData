
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int Alg_Deik(struct Graph* graph);
void addEdge(struct Graph* graph, int src, int dest, int weight);
struct AdjListNode* newAdjListNode(int dest, int weight);
struct Graph* createGraph(int V);
void printGraph(struct Graph* graph);
int Init_File(Graph *graph);
struct MinHeapNode* newMinHeapNode(int v, int dist);
struct MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isEmpty(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
bool isInMinHeap(struct MinHeap *minHeap, int v);
void printArr(int dist[], int n);

struct AdjListNode

{

    int dest;
    int weight;

    struct AdjListNode* next;

};


// Структура для представления списка смежности

struct AdjList

{

    struct AdjListNode *head;

};

struct Graph

{

    int V;

    struct AdjList* array;

};


// Служебная функция для создания нового узла списка смежности




struct MinHeapNode

{

    int  v;

    int dist;

};


struct MinHeap

{

    int size;      // Количество узлов кучи, присутствующих в данный момент

    int capacity;  // Емкость мин кучи

    int *pos;     // Это необходимо для lowerKey ()

    struct MinHeapNode **array;

};




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main()

{
  system ("chcp 65001");
     int a;

     struct Graph* graph;

     a = Init_File(graph);

     cout<< endl<< "\t\tРеализация списком смежности " << endl;

     cout<< endl<< "Фельдшерский пункт нужно расположить в " << a+1 << " деревне. "<< endl;

     delete graph;

    return 0;

}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct AdjListNode* newAdjListNode(int dest, int weight)

{

    struct AdjListNode* newNode = new AdjListNode;


    newNode->dest = dest;

    newNode->weight = weight;

    newNode->next = nullptr;

    return newNode;

}


// Вспомогательная функция, которая создает граф из V вершин

struct Graph* createGraph(int V)

{

    struct Graph* graph = new Graph;

    graph->V = V;



    // Создать массив списков смежности. Размер

    // массив будет V

    graph->array = new AdjList[V];




    // Инициализируем каждый список смежности как пустой

    // сделать голову как NULL



    for (int i = 0; i < V; ++i)

        graph->array[i].head = nullptr;



    return graph;

}


// Добавляем ребро в неориентированный граф

void addEdge(struct Graph* graph, int src, int dest, int weight)

{

    // Добавить ребро из src в dest. Новый узел

    struct AdjListNode* newNode = newAdjListNode(dest, weight);

    newNode->next = graph->array[src].head;

    graph->array[src].head = newNode;



    newNode = newAdjListNode(src, weight);

     newNode->next = graph->array[dest].head;

     graph->array[dest].head = newNode;

}


int Init_File(Graph *graph)
{
    int n;
    int rez_Vil;
    char F_reliz;
    char buf;
    int _v = 0, _weight = 0;
    ifstream fin;


fin.open("C:\\Univirsity\\Pr_2_3-DOS\\G_List_5_2.txt");
if (fin){
  fin >> n;
  fin >> F_reliz;

     struct Graph* graph = createGraph(n);


     if  (F_reliz != 'M')
    {

         for (int i = 0; i < n; ++i)
             {
                 while ( (buf = fin.get()) != '\n' && buf != '\0' )
               {
                     if (buf == ' ') buf = fin.get();

                  _v = buf -'0';

                  fin >> _weight;

                  addEdge(graph, i-1, _v, _weight);
               }

           };

         //  printGraph(graph);


    cout << endl;





    }
else
    {
      for(int i = 0; i < n ; ++i)
          for(int j = 0; j < n;++j )
          {
              fin >> _weight;
              if (_weight && _weight != -1)
              {
                  addEdge(graph, i, j, _weight);
              }


          }
    };


    fin.close();

    rez_Vil = Alg_Deik(graph);


}
else cout <<"Ошибка открытия файла";
return rez_Vil;
};

// Вспомогательная функция для создания нового узла Min Heap

struct MinHeapNode* newMinHeapNode(int v, int dist)

{

    struct MinHeapNode* minHeapNode = new MinHeapNode;

    minHeapNode->v = v;

    minHeapNode->dist = dist;

    return minHeapNode;

}


// созданиe Min Heap

struct MinHeap* createMinHeap(int capacity)

{

    struct MinHeap* minHeap = new MinHeap;


    minHeap->pos = (int *)malloc(capacity * sizeof(int));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array =

         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));

    return minHeap;

}


// Вспомогательная функция для замены двух узлов минимальной кучи.
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;

    *a = *b;

    *b = t;

}


//функция обновляет положение узлов, когда они меняются местами.

void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest, left, right;

    smallest = idx;

    left = 2 * idx + 1;

    right = 2 * idx + 2;



    if (left < minHeap->size &&

        minHeap->array[left]->dist < minHeap->array[smallest]->dist )

      smallest = left;



    if (right < minHeap->size &&

        minHeap->array[right]->dist < minHeap->array[smallest]->dist )

      smallest = right;



    if (smallest != idx)

    {

        // Узлы, которые нужно поменять местами в минимальной куче

        MinHeapNode *smallestNode = minHeap->array[smallest];

        MinHeapNode *idxNode = minHeap->array[idx];



        // Меняем местами

        minHeap->pos[smallestNode->v] = idx;

        minHeap->pos[idxNode->v] = smallest;



        // Переставляем узлы

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);



        minHeapify(minHeap, smallest);

    }

}


// является ли данный minHeap пустым или нет

int isEmpty(struct MinHeap* minHeap)

{

    return minHeap->size == 0;

}


// функция для извлечения минимального узла из кучи

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    if (isEmpty(minHeap))

        return NULL;



    // Сохраняем корневой узел

    struct MinHeapNode* root = minHeap->array[0];



    // Заменить корневой узел последним узлом

    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;



    // Обновляем позицию последнего узла

    minHeap->pos[root->v] = minHeap->size-1;

    minHeap->pos[lastNode->v] = 0;



    // Уменьшаем размер кучи

    --minHeap->size;

    minHeapify(minHeap, 0);



    return root;

}


// Функция для уменьшения значения dist данной вершины v. Эта функция
// использует pos [] из min heap, чтобы получить текущий индекс узла в min heap

void decreaseKey(struct MinHeap* minHeap, int v, int dist)

{

    // Получить индекс v в массиве кучи

    int i = minHeap->pos[v];



    // Получить узел и обновить его значение dist

    minHeap->array[i]->dist = dist;



    // Подниматься вверх

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)

    {

        // Поменяем местами этот узел

        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;

        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;

        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);



        // перейти к родительскому индексу

        i = (i - 1) / 2;

    }

}


// Полезная функция, чтобы проверить, является ли данная вершина
// 'v' в минимальной куче или нет

bool isInMinHeap(struct MinHeap *minHeap, int v)

{

   if (minHeap->pos[v] < minHeap->size)

     return true;

   return false;

}


void printArr(int dist[], int n)

{

    printf("Vertex   Distance from Source\n");

    for (int i = 0; i < n; ++i)

        printf("%d \t\t %d\n", i, dist[i]);

}



int Alg_Deik(struct Graph* graph)

{
    int vil = INT_MAX;
    int _der;
    int src = 0;
    int V = graph->V;// Получить количество вершин в графе

    int dist[V];      // значения dist, используемые для выбора минимального края веса в разрезе
    int min_vil[V];

    for (int i = 0; i < V; i++)   min_vil[i] = 0;
    for (src = 0; src < V; src++)
    {

    struct MinHeap* minHeap = createMinHeap(V);



    // Инициализируем минимальную кучу со всеми вершинами. значение dist всех вершин

    for (int v = 0; v < V; ++v)

    {

        dist[v] = INT_MAX;

        minHeap->array[v] = newMinHeapNode(v, dist[v]);

        minHeap->pos[v] = v;

    }



    // Сделать значение dist вершины src равным 0, чтобы оно извлекалось первым

    minHeap->array[src] = newMinHeapNode(src, dist[src]);

    minHeap->pos[src] = src;

    dist[src] = 0;

    decreaseKey(minHeap, src, dist[src]);



    // изначально размер min heap равен V

    minHeap->size = V;



    // В цикле followin min heap содержит все узлы

    // кратчайшее расстояние которого еще не определено.

    while (!isEmpty(minHeap))

    {

        // Извлекаем вершину с минимальным значением расстояния

        struct MinHeapNode* minHeapNode = extractMin(minHeap);

        int u = minHeapNode->v; // Сохраняем извлеченный номер вершины



        // Обход всех смежных вершин и обновить их значения расстояния

        struct AdjListNode* pCrawl = graph->array[u].head;

        while (pCrawl != NULL)

        {

            int v = pCrawl->dest;



            // Если кратчайшее расстояние до v еще не определено, а расстояние до v

            // через u меньше предварительно рассчитанного расстояния

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&

                                          pCrawl->weight + dist[u] < dist[v])

            {

                dist[v] = dist[u] + pCrawl->weight;



                // обновить значение расстояния в мин куче

                decreaseKey(minHeap, v, dist[v]);

            }

            pCrawl = pCrawl->next;

        }

    }


    for (int i = 0; i < V; i++)   min_vil[src] += dist[i];

    if (vil > min_vil[src]) {vil = min_vil[src]; _der = src; }

};

return _der;
}
