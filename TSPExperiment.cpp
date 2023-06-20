#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

#include "randomdata.h"

using namespace std;

using ArcType = int;

const int MaxNodeNum = 105;

/// <summary>
/// 邻接矩阵结构
/// </summary>
struct AMGraph {
  ArcType arcs[MaxNodeNum][MaxNodeNum];
  int node_num, arc_num;
};

struct Edge {
  int begin;
  int end;
  int weight;
};

AMGraph *CreateUDN();

void PrintInputGraph(AMGraph *graph);

void QuickSort(vector<Edge> edges, int left, int right);

int FindEnd(int *ends, int f);

vector<Edge> GetMST(AMGraph *graph);

void PrintMST(vector<Edge> mst);

AMGraph *GetEulerGraph(vector<Edge> mst, int n);

void PrintEulerGraph(AMGraph *graph);

vector<int> GetEulerPath(AMGraph *graph);

void PrintEulerPath(vector<int> &euler_path);

vector<int> GetTSPPath(AMGraph *graph, vector<int> &euler_path);

void PrintTSPPath(vector<int> TSP_path);

int main() {
  AMGraph *graph = CreateUDN();

  vector<Edge> mst = GetMST(graph);

  AMGraph *euler_graph = GetEulerGraph(mst, graph->node_num);
  
  vector<int> euler_path = GetEulerPath(euler_graph);

  vector<int> TSP_path = GetTSPPath(euler_graph, euler_path);

  PrintTSPPath(TSP_path);
}

void PrintInputGraph(AMGraph *graph) {
  for (int i = 0; i < graph->node_num; i++) {
    for (int j = 0; j < graph->node_num; j++) {
      cout << graph->arcs[i][j] << " ";
    }
    cout << endl;
  }
}

void PrintMST(vector<Edge> mst) {
  for (int i = 0; i < mst.size(); i++) {
    printf("(%d %d) %d\n", mst[i].begin, mst[i].end, mst[i].weight);
  }
}

void PrintEulerGraph(AMGraph *graph) {
  for (int i = 0; i < graph->node_num; i++) {
    for (int j = 0; j < graph->node_num; j++) {
      cout << graph->arcs[i][j] << " ";
    }
    cout << endl;
  }
}

/// <summary>
/// 输入数据并生成相应的邻接矩阵
/// </summary>
/// <param name="graph">生成的邻接矩阵表</param>
AMGraph *CreateUDN() {
  // 输入数据
  ifstream fin;
  fin.open("data.tsp", ios::in);
  if (!fin.is_open()) {
    cout << "open file failed" << endl;
  }

  AMGraph *graph = new AMGraph;

  fin >> graph->node_num;
  graph->arc_num = graph->node_num * (graph->node_num - 1) / 2;

  for (int i = 0; i < graph->node_num; i++) {
    for (int j = 0; j < graph->node_num; j++) {
      graph->arcs[i][j] = -1;
    }
  }

  int a, b, w;
  for (int i = 0; i < graph->arc_num; i++) {
    fin >> a >> b >> w;
    graph->arcs[a - 1][b - 1] = graph->arcs[b - 1][a - 1] = w;
  }

  return graph;
}

/// <summary>
/// 将图中的边按权值非降序排序
/// </summary>
/// <param name="edges">边的集合</param>
/// <param name="left">左侧边界</param>
/// <param name="right">右侧边界</param>
void QuickSort(vector<Edge> edges, int left, int right) {
  if (left > right)
    return;
  int i = left, j = right;
  Edge temp = edges[left];

  while (i != j) {
    while (i < j && edges[j].weight >= temp.weight) {
      j--;
    }
    swap(edges[i], edges[j]);
    while (i < j && edges[i].weight < temp.weight) {
      i++;
    }
    swap(edges[i], edges[j]);
  }

  QuickSort(edges, i + 1, right);
  QuickSort(edges, left, i - 1);
}

/// <summary>
/// 查找结点对应的终点
/// </summary>
/// <param name="ends">结点对应的终点数组</param>
/// <param name="f">待查找终点的结点</param>
/// <returns>终点</returns>
int FindEnd(int *ends, int f) {
  while (ends[f] > 0) {
    f = ends[f];
  }

  return f;
}

/// <summary>
/// 使用Kruskal算法获取最小生成树
/// </summary>
/// <param name="graph"></param>
vector<Edge> GetMST(AMGraph *graph) {
  // 定义边的集合
  vector<Edge> edges;
  int k = 0;

  for (int i = 0; i < graph->node_num; i++) {
    for (int j = 0; j < graph->node_num; j++) {
      if (i < j) {
        edges.push_back({i, j, graph->arcs[i][j]});
      }
    }
  }

  // 将边的集合按照权重排序
  QuickSort(edges, 0, graph->arc_num - 1);

  // 定义各结点的终点
  int ends[MaxNodeNum];
  for (int i = 0; i < graph->node_num; i++) {
    ends[i] = 0;
  }

  vector<Edge> mst;

  // 按顺序将边加入并检查是否有回路
  int count = 0;
  for (int i = 0; i < graph->arc_num; i++) {
    int n = FindEnd(ends, edges[i].begin);
    int m = FindEnd(ends, edges[i].end);

    if (n != m) {
      ends[n] = m;
      mst.push_back({edges[i].begin, edges[i].end, edges[i].weight});
      ++count;
      if (count == graph->node_num - 1) {
        break;
      }
    }
  }

  return mst;
}

AMGraph *GetEulerGraph(vector<Edge> mst, int n) {
  AMGraph *graph = new AMGraph;
  graph->node_num = n;
  graph->arc_num = graph->node_num * (graph->node_num - 1);

  for (int i = 0; i < graph->node_num; i++) {
    for (int j = 0; j < graph->node_num; j++) {
      graph->arcs[i][j] = -1;
    }
  }

  for (int i = 0; i < mst.size(); i++) {
    int begin = mst[i].begin;
    int end = mst[i].end;
    graph->arcs[begin][end] = graph->arcs[end][begin] = mst[i].weight;
  }

  return graph;
}

vector<int> GetEulerPath(AMGraph *graph) {
  vector<int> euler_path;
  stack<int> stk;
  bool vis[MaxNodeNum];
  for (int i = 0; i < graph->node_num; i++) {
    vis[i] = false;
  }

  stk.push(0);
  euler_path.push_back(0);
  vis[0] = true;
  int t = 0;
  while (!stk.empty()) {
    bool flag = true;
    t = stk.top();
    for (int j = 0; j < graph->node_num; j++) {
      if (graph->arcs[t][j] > -1 && !vis[j]) {
        stk.push(j);
        euler_path.push_back(j);
        vis[j] = true;
        flag = false;
      }
    }
    if (flag) {
      stk.pop();
      if (!stk.empty()) {
        euler_path.push_back(stk.top());
      }
    }
  }

  return euler_path;
}

void PrintEulerPath(vector<int> &euler_path) {
  for (int i = 0; i < euler_path.size(); i++) {
    cout << euler_path[i] << " ";
  }
  cout << endl;
}

vector<int> GetTSPPath(AMGraph *graph, vector<int> &euler_path) {
  int vis[MaxNodeNum];
  vector<int> TSP_path;
  for (int i = 0; i < graph->node_num; i++) {
    vis[i] = false;
  }
  for (int i = 0; i < euler_path.size(); i++) {
    if (!vis[i]) {
      TSP_path.push_back(i);
      vis[i] = true;
    }
  }
  TSP_path.push_back(0);

  return TSP_path;
}

void PrintTSPPath(vector<int> TSP_path) {
  for (int i = 0; i < TSP_path.size(); i++) {
    if (i > 0)
      cout << "->";
    cout << TSP_path[i] + 1;
  }
  cout << endl;
}