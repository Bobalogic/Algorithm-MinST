#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

/*variavel global*/
int res;


typedef struct{
    int v1;
    int v2;
    int w;
} edge;

vector<edge> e_vec;
vector<int> vv_rank;
vector<int> vv_parent;


void initVertexVector (int v) {
    int i;
    vv_parent.resize(v);
    for(i=0; i<v; i++)
        vv_parent[i]=i+1;
}

void getEdges(int e) {
    int v1, v2, w, i;
    for(i=0; i<e; i++) {
        edge ed;
        scanf("%d %d %d", &v1, &v2, &w);
        ed.v1 = v1;
        ed.v2 = v2;
        ed.w = w;
        e_vec[i] = ed;
    }
}
/*
treeForest funcs
*/
int findSet(int v) {
    if (vv_parent[v-1] != v)
        vv_parent[v-1] = findSet(vv_parent[v-1]);
    return vv_parent[v-1];
}
void linkSet(int v1, int v2) {
    if (vv_rank[v1-1] > vv_rank[v2-1])
        vv_parent[v2-1] = v1;
    else {
        vv_parent[v1-1] = v2;
        if(vv_rank[v1-1] == vv_rank[v2-1])
            vv_rank[v2-1] += 1;
    }
}
void unionSet(int v1, int v2) {
    linkSet(findSet(v1), findSet(v2));
}

/*
kruskal
*/
void kruskal(int e) {
    int i;
    for(i=0; i<e; i++) {
        if (findSet(e_vec[i].v1) != findSet(e_vec[i].v2)) {
            res += e_vec[i].w;
            unionSet(e_vec[i].v1, e_vec[i].v2);
        }
    }
}

bool comparator(edge e1, edge e2) {
    return e1.w > e2.w;
}


int main() {
    int e, v;
    scanf("%d\n%d", &v, &e);    /*get #vertexes and #edges*/

    initVertexVector(v); /*O(V) percorre v elementos para criar os vertices todos*/
    e_vec.resize(e);
    vv_rank.resize(v, 0);

    getEdges(e); /*O(Elog(E)) vai criar lista e depois dar sort*/
    sort(e_vec.begin(), e_vec.end(), comparator);

    kruskal(e);/*O(elog(v))*/
    
    printf("%d\n", res);
    return 0;
}