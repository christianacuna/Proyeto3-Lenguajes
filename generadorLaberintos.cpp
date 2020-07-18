#include <bits/stdc++.h>
using namespace std;
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define INF 0x3f3f3f3f 
#define SET(a,b)  ((a) | (1<<(b)))

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

struct Ar{int a,b,w;};
bool operator<(const Ar& a, const Ar &b){return a.w<b.w;}

vector<ii> prim(vector<pair<int,int> > G[], int fc){ 
    priority_queue< ii, vector <ii> , greater<ii> > pq; 
    int src = 0;
    vector<int> key(fc, INF); 
    vector<int> parent(fc, -1); 
    vector<bool> inMST(fc, false); 
    pq.push(make_pair(0, src)); 
    key[src] = 0; 
    while (!pq.empty()) { 
        int u = pq.top().second; 
        pq.pop(); 
        inMST[u] = true;
        for (auto x : G[u]){ 
            int v = x.second; 
            int weight = x.first; 
            if (inMST[v] == false && key[v] > weight){ 
                key[v] = weight; 
                pq.push(make_pair(key[v], v)); 
                parent[v] = u; 
            } 
        } 
    }
    vector<ii> r;
    for (int i = 1; i < fc; ++i)
        r.push_back(make_pair(parent[i], i));
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

    vector<ii> p = prim(G, f*c);
    imprimirLaberinto(p,f,c);
}

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