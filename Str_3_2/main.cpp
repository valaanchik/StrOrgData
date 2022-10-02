#include <iostream>
#include <fstream>
#include <ctime>
#define CNT " Бор \t\t\t\t\t\t\t\t АВЛ-дерево "
#define SR     cout<< endl<< endl<< " CРЕДНЕЕ КОЛИЧЕСТВО СРАВНЕНИЙ|     Бор: "<<_k_cr_bor/100<< "\t\t\t АВЛ: "<< _k_cr_avl/100<<endl; cout<< " ЗАНИМАЕМАЯ ПАМЯТЬ\t     |\t   Бор: "<<memory_bor<<  " \t\t АВЛ: "<< memory_avl<<endl;


#define N 10
using namespace std;

int memory_avl = 0,
    memory_bor = 0;
int _k_avl=0,
    _k_bor=0,
    _k_cr_avl = 0,
    _k_cr_bor = 0;

struct node // структура для представления узлов дерева АВЛ
{
    int key;
    unsigned char height;
    struct node *left, *right;

};
typedef struct node node;
typedef struct node * tree;




    int bfactor (tree p) //вычисление баланса
    {
        return ( p->left ? p->left->height : 0 ) - (p->right ? p->right->height : 0 );
    }

    node * make_node (int k)
    {
        memory_avl+=sizeof (node);
        node * n = new node();
        if ( n==NULL )
           return NULL;
        n->key = k;
        n->left = n->right = NULL;
        n->height = 1;
        return n;
    }

    void fixheight (node* p) //корректировка высоты после добавления/удаления узлов
    {
        unsigned char hl = p->left ? p->left->height : 0;
        unsigned char hr = p->right ? p->right->height : 0;
        p->height = ( hl>hr ? hl : hr ) + 1;
    }

    node* rotateright(node* p) // правый поворот вокруг p
    {
        node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    node* rotateleft (node* q) // левый поворот вокруг q
    {
        node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    node* balance (node* p) // балансировка узла p
    {
        fixheight(p);
        if( bfactor(p)==-2 )
        {
            if( bfactor(p->right) > 0 )
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if( bfactor(p)==2 )
        {
            if( bfactor(p->left) < 0  )
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }

    tree avl_insert (tree p, int k) // вставка ключа k в дерево с корнем p
    {

        if( !p ) return make_node(k);
        if( k==p->key ) return p;
        if( k<p->key )
            p->left = avl_insert(p->left,k);
        else
            p->right = avl_insert(p->right,k);
        return balance(p);
    }


    int find_key (node* p, int k) // поиск узла
    {
        if (p != nullptr)
        {
            if (++_k_avl && p->key == k){
                return 1;
            };
            if (++_k_avl&&p->key > k) return find_key(p->left,k);
                    else return find_key(p->right, k);
        };

 return 0;
    };


    void del_tree (tree t)
    {


         if (t->left) del_tree (t->left);
         if (t->right) del_tree (t->right);
         free (t);
    }

    struct trie_node_bor
    {
        char eok;
        struct trie_node_bor * p[10];
    };

    typedef struct trie_node_bor trie_node_bor;

    trie_node_bor * make_trie_node ()
    {

        memory_bor+=sizeof (trie_node_bor);
        int i;
        trie_node_bor * nd = (trie_node_bor*) malloc (sizeof(trie_node_bor));
        nd->eok = 0;
        for (i=0; i<N; i++)
           nd->p[i] = NULL;
        return nd;
    }


    trie_node_bor* insert_key (trie_node_bor* trie, char* key)
    {
        if (trie == NULL)
            trie = make_trie_node();
        if ( *key>='0' && *key<='9' )									/*текущую цифру*/
            trie->p[*key-'0'] = insert_key (trie->p[*key-'0'], key+1);	/*добавляем в дерево и продолжаем строить*/
        else
            trie->eok = 1; 		/*ключ кончился - устанавливаем признак конца ключа*/
        return trie;
    }

    int find_key_bor (trie_node_bor* trie, char* key)
    {
        if ( trie == NULL )		/*если узел не обнаружен, то ключ не найден*/
            return 0;
        if ( ++_k_bor&&*key>='0' && *key<='9' )
            return find_key_bor (trie->p[*key-'0'], key+1);		/*пока не конец ключа продолжаем поиск*/
        if ( ++_k_bor&&trie->eok )		/* если кончился ключ и в узле установлен признак конца ключа, то значение найдено */
            return 1;
        return 0;
    }


    trie_node_bor* delete_trie (trie_node_bor* trie)
    {
        int i;
        for (i=0; i<N; i++)
           if (trie->p[i] != NULL)
              trie->p[i] = delete_trie (trie->p[i]);
        free (trie);
        return NULL;
    }


int main()
{system ("chcp 65001");

    ifstream fin,fin_key;
    clock_t t;

    fin.open("C:\\Univirsity\\Str_3_1\\test_numbers.txt");
    fin_key.open("C:\\Univirsity\\Str_3_2\\key.txt");
    tree t_avl = nullptr;
    trie_node_bor* trie = make_trie_node();

    for (int i; fin >> i;)
    {
        t_avl =avl_insert(t_avl,i);
    };
    fin.close();
    fin.open("C:\\Univirsity\\Str_3_1\\test_numbers.txt");

    for (char i[12]; fin >> i;)
    {
        trie = insert_key(trie, i);

    };


    cout << CNT <<endl;
    for (char i[12]; fin_key >> i;)
    {

        _k_avl=0;
        _k_bor=0;
        t = clock();
         cout<< "Ключ: "<< i<< (find_key_bor(trie, i)? "  Найден. ":"  Не найден. ") << "Время поиска: " << clock() - t<< " мс " ;
          t = clock();
         cout    <<    "\t\t Ключ: "<< i <<  ((find_key(t_avl,atof(i)))?"  Найден. ":"  Не найден. ")<< "Время поиска: " << clock() - t<< " мс " << endl;
         cout<< " КОЛИЧЕСТВО СРАВНЕНИЙ|     \t   Бор: "<< _k_bor<< "\t\t\t АВЛ: "<< _k_avl<<endl;
         _k_cr_bor+=_k_bor;
         _k_cr_avl+=_k_avl;
    };
    SR;


  delete_trie(trie);
  del_tree(t_avl);
  fin.close();
  fin_key.close();
  return 0;
};
