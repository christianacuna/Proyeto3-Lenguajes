#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforsn(i,a,b) for(int i=(b)-1; i>=a; i--)
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))

/////////////////////////////////
// BORRAR LOS QUE NO SE OCUPEN //
/////////////////////////////////

//#define TEST(a,b) ((a) & (1<<(b)))
#define SET(a,b)  ((a) | (1<<(b)))
//#define CLEAR(a,b) ((a) & ~(1<<(b)))
//#define FLIP(a,b) ((a) ^ (1<<(b)))

typedef pair<int,int> ii;
const int MAXN=100000;

struct UnionFind{
    vector<int> f;//the array contains the parent of each node
    void init(int n){f.clear(); f.insert(f.begin(), n, -1);}
    int comp(int x){return (f[x]==-1?x:f[x]=comp(f[x]));}//O(1)
    bool unir(int i, int j) {
        bool con=comp(i)==comp(j);
        if(!con) f[comp(i)] = comp(j);
        return con;
    }};

bool taken[MAXN];
priority_queue<ii, vector<ii>, greater<ii> > pq;//min heap
struct Ar{int a,b,w;};
bool operator<(const Ar& a, const Ar &b){return a.w<b.w;}

void process(vector<ii> G[], int v){
    taken[v]=true;
    forall(e, G[v]){
        if(!taken[e->second]) pq.push(*e);
    }
}

vector<ii> prim(vector<ii> G[]){ //HACER QUE DEVUELVA <NODO1, NODO2>
    zero(taken);
    process(G, 0);
    vector<ii> r;
    while(sz(pq)){
        ii e=pq.top(); pq.pop();
        if(!taken[e.second])r.push_back(make_pair(e.first, e.second)), process(G, e.second);
    }
    return r;
}

vector<ii> kruskal(vector<Ar> E, int fc){
    vector<ii> r;
    UnionFind uf;
    sort(E.begin(), E.end());//ordenar aristas de menor a mayor
    uf.init(fc);
    forall(it, E){
        if(uf.comp(it->a)!=uf.comp(it->b)){//si no estan conectados
            uf.unir(it->a, it->b);//conectar
            r.push_back(make_pair(it->a, it->b));
        }
    }
    return r;
}

void imprimirLaberinto(vector<ii> aristas, int f, int c){
    
    ii a;
    int v;
    printf("(%d,%d)\n", f,c);
    for (int i = 0; i < f*c; i++)
    {
        int msk = 0;
        if (i>c) //tiene Norte
        {
            v = i-c;
            a.first = i;
            a.second = v;

            if (find(aristas.begin(), aristas.end(), a) != aristas.end())
            {
                msk |= SET(msk,1);
            }
        }

        if (i%c!=0) //tiene Oeste
        {
            v = i-1;
            a.first = i;
            a.second = v;

            if (find(aristas.begin(), aristas.end(), a) != aristas.end())
            {
                msk |= SET(msk,0);
            }
        }

        printf("%d", msk);

        if (i%c==c-1)
        {
            printf("\n");
        }
    }
}

///////////////////
// ARREGLAR PRIM //
///////////////////

void caminoPrim(int f, int c){

    int v, r; //vecino, random
    srand(time(NULL));
    vector<ii> G[f*c]; //representacion del grafo prim

    for (int i = 0; i < f*c; i++)
    {
        if (i>c) //tiene Norte
        {
            r = rand() % 100 + 1;
            v = i-c;
            if (i<v)
            {
                G[i].push_back(make_pair(r,v));
                G[v].push_back(make_pair(r,i));
            }
        }

        if (i/c<f-1) //tiene Sur
        {
            r = rand() % 100 + 1;
            v = i+c;
            if (i<v)
            {
                G[i].push_back(make_pair(r,v));
                G[v].push_back(make_pair(r,i));
            }
        }

        if (i%c!=c-1) //tiene Este
        {
            r = rand() % 100 + 1;
            v = i+1;
            if (i<v)
            {
                G[i].push_back(make_pair(r,v));
                G[v].push_back(make_pair(r,i));
            }
        }

        if (i%c!=0) //tiene Oeste
        {
            r = rand() % 100 + 1;
            v = i-1;
            if (i<v)
            {
                G[i].push_back(make_pair(r,v));
                G[v].push_back(make_pair(r,i));
            }
        }
    }

    /*for(size_t idx = 0; idx < 20; ++idx)
{
   cout << "Nodo: " << idx << endl;
   for (vector <pair<int,int> >::const_iterator iter = G[idx].begin();
        iter != G[idx].end();
        ++iter)
   {
      cout << "Peso: "    << iter->first
           << ", Hacia: " << iter->second << endl;
   }
}

    vector<ii> p = prim(G);
    printf("Prim\n");
    for (vector <pair<int,int> >::const_iterator iter = p.begin();
        iter != p.end();
        ++iter)
   {
      cout << "Peso: "    << iter->first
           << ", Hacia: " << iter->second << endl;
   }*/

    //imprimirLaberinto(p,f,c);
}

////////////////////
// REVISAR SALIDA //
////////////////////

void caminoKruskal(int f, int c){

    int v, r; //vecino, random
    srand(time(NULL));
    vector<Ar> E; //vector de aristas kruskal
    Ar Ar;

    for (int i = 0; i < f*c; i++)
    {
        if (i>c) //tiene Norte
        {
            r = rand() % 100 + 1;
            v = i-c;
            if (i<v)
            {
                Ar.a=i;
                Ar.b=v;
                Ar.w=r;
                E.push_back(Ar);

                Ar.a=v;
                Ar.b=i;
                Ar.w=r;
                E.push_back(Ar);
            }
        }

        if (i/c<f-1) //tiene Sur
        {
            r = rand() % 100 + 1;
            v = i+c;
            if (i<v)
            {
                Ar.a=i;
                Ar.b=v;
                Ar.w=r;
                E.push_back(Ar);

                Ar.a=v;
                Ar.b=i;
                Ar.w=r;
                E.push_back(Ar);
            }
        }

        if (i%c!=c-1) //tiene Este
        {
            r = rand() % 100 + 1;
            v = i+1;
            if (i<v)
            {
                Ar.a=i;
                Ar.b=v;
                Ar.w=r;
                E.push_back(Ar);

                Ar.a=v;
                Ar.b=i;
                Ar.w=r;
                E.push_back(Ar);
            }
        }

        if (i%c!=0) //tiene Oeste
        {
            r = rand() % 100 + 1;
            v = i-1;
            if (i<v)
            {
                Ar.a=i;
                Ar.b=v;
                Ar.w=r;
                E.push_back(Ar);

                Ar.a=v;
                Ar.b=i;
                Ar.w=r;
                E.push_back(Ar);
            }
        }
    }

   vector<ii> k = kruskal(E, f*c);
   printf("Kruskal\n");
   for (vector <pair<int,int> >::const_iterator iter = k.begin();
        iter != k.end();
        ++iter)
   {
      cout << "Desde: "    << iter->first
           << ", Hacia: " << iter->second << endl;
   }

    imprimirLaberinto(k,f,c);

}

int main(){

    int f, c; //filas, columnas
    char a; //algoritmo
    scanf("%d %d %c", &f, &c, &a);

    if (a == 'K')
    {
        caminoKruskal(f,c);
    } else {
        caminoPrim(f,c);
    }

    return 0;
}