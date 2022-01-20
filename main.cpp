#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <iostream>

using namespace std;

typedef struct node
{
    int id = 0;
    int color = 0; // 0 -> white 1 -> gray 2 -> black
    int number_of_parents;
    vector<int> adj;

} node;

int v1, v2;
int vertices, edges;
node *array_v;
set<int> ordered_ancestors;

int read_input()
{
    int first, second;
    if (scanf("%d %d", &v1, &v2) != 2)
        return -1;
    if (scanf("%d %d", &vertices, &edges) != 2)
        return -1;
    array_v = (node *)malloc(sizeof(node) * (vertices + 1));
    for (int i = 0; i != edges; i++)
    {
        if (scanf("%d %d", &first, &second) != 2)
            return -1;
        if (array_v[second].number_of_parents == 2)
        {
            return -1;
        }
        array_v[second].number_of_parents++;
        array_v[first].id = first;
        array_v[second].id = second;
        array_v[second].adj.push_back(first);
    }
    return 0;
}

int dfs_visit(int position)
{
    array_v[position].color = 1;
    int size = array_v[position].adj.size();
    for (int i = 0; i != size; i++)
    {
        if (array_v[array_v[position].adj[i]].color == 0)
        {
            if (dfs_visit(array_v[position].adj[i])==-1)
                return -1;
        }
        else if (array_v[array_v[position].adj[i]].color == 1)
        {
            printf("0\n");
            return -1;
        }
    }
    array_v[position].color = 2;
    return 0;
}

int DFS()
{
    for (int i = 1; i <= vertices; i++)
    {
        if (array_v[i].color == 0)
        {
            if(dfs_visit(i)==-1){
                return -1;
            }
        }
    }
    return 0;
}

void dfs_visit_v1(int position)
{
    array_v[position].color = 3;
    int size = array_v[position].adj.size();
    for (int i = 0; i != size; i++)
    {
        if (array_v[array_v[position].adj[i]].color == 2)
        {
            dfs_visit_v1(array_v[position].adj[i]);
        }
    }
}

void dfs_visit_v3(int position){
    int size = array_v[position].adj.size();
    for (int i = 0; i != size; i++)
    {
        if (array_v[array_v[position].adj[i]].color == 4)
        {
            set<int>::iterator iter= ordered_ancestors.find(array_v[array_v[position].adj[i]].id);
            if (iter!=ordered_ancestors.end()){
                ordered_ancestors.erase(iter);
            }
        }
        dfs_visit_v3(array_v[position].adj[i]);
    }
}

void DFS_3(){
    for (int i=1; i<=vertices; i++){
        if (array_v[i].color==4){
            dfs_visit_v3(i);
        }
    }
}

void dfs_visit_v2(int position)
{
    int size = array_v[position].adj.size();
    if (array_v[position].color == 3)
    {
        array_v[position].color =4;
        ordered_ancestors.insert(position);
    }
    for (int i = 0; i != size; i++)
    {
        dfs_visit_v2(array_v[position].adj[i]);
    }
}

void print_result()
{
    if (ordered_ancestors.empty())
    {
        printf("-\n");
        return;
    }
    else
    {
        set<int>::iterator itr;
        for (itr = ordered_ancestors.begin(); itr != ordered_ancestors.end(); itr++)
        {
            cout << *itr << " ";
        }
        cout << endl;
    }
}

int main()
{
    if (read_input() == -1)
    {
        printf("0\n");
        return 0;
    }
    if(DFS()==-1){
        return 0;
    }
    dfs_visit_v1(v1);
    dfs_visit_v2(v2);
    DFS_3();
    print_result();
    return 0;
}