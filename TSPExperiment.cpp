#include <fstream>
#include <iostream>

#include "randomdata.h"

using namespace std;

using ArcType = int;

const int MaxNodeNum = 100;

/// <summary>
/// 邻接矩阵结构
/// </summary>
struct AMGraph {
  ArcType arcs[MaxNodeNum][MaxNodeNum];
  int node_num, arc_num;
};

struct Edge {
  int start;
  int end;
  int weight;
};

void CreateUDN(AMGraph& graph);
void QuickSort(Edge* edges, int left, int right);
void GetMST(const AMGraph& graph);

int main() {
  AMGraph graph;
  CreateUDN(graph);

  /*for (int i = 0; i < graph.node_num; i++) {
    for (int j = 0; j < graph.node_num; j++) {
      cout << graph.arcs[i][j] << " ";
    }
    cout << endl;
  }*/

  Edge edges[MaxNodeNum];
  int k = 0;

  for (int i = 0; i < graph.node_num; i++) {
    for (int j = 0; j < graph.node_num; j++) {
      if (i < j) {
        edges[k++] = Edge{i, j, graph.arcs[i][j]};
      }
    }
  }

  QuickSort(edges, 0, graph.arc_num);

  for (int i = 0; i < k; i++) {
    printf("%d %d %d\n", edges[i].start, edges[i].end, edges[i].weight);
  }
}

/// <summary>
/// 输入数据并生成相应的邻接矩阵
/// </summary>
/// <param name="graph">生成的邻接矩阵表</param>
void CreateUDN(AMGraph& graph) {
  // 输入数据
  ifstream fin;
  fin.open("data.tsp", ios::in);
  if (!fin.is_open()) {
    cout << "open file failed" << endl;
  }

  fin >> graph.node_num;
  graph.arc_num = graph.node_num * (graph.node_num - 1) / 2;

  for (int i = 0; i < graph.node_num; i++) {
    for (int j = 0; j < graph.node_num; j++) {
      graph.arcs[i][j] = INT_MAX;
    }
  }

  int a, b, w;
  for (int i = 0; i < graph.arc_num; i++) {
    fin >> a >> b >> w;
    graph.arcs[a - 1][b - 1] = graph.arcs[b - 1][a - 1] = w;
  }
}

/// <summary>
/// 将图中的边按权值非降序排序
/// </summary>
/// <param name="edges">边的集合</param>
/// <param name="left">左侧边界</param>
/// <param name="right">右侧边界</param>
void QuickSort(Edge* edges, int left, int right) {
  int l = left, r = right;
  Edge temp = {};
  if (l <= r) {
    temp = edges[left];
    while (l != r) {
      while (r > l && edges[r].weight > temp.weight) {
        r--;
      }
      swap(edges[l], edges[r]);
      while (r > l && edges[l].weight < temp.weight) {
        l++;
      }
      swap(edges[l], edges[r]);
    }
    edges[r] = temp;

    QuickSort(edges, left, l - 1);
    QuickSort(edges, r + 1, right);
  }
}

/// <summary>
/// 使用Kruskal算法获取最小生成树
/// </summary>
/// <param name="graph"></param>
void GetMST(const AMGraph& graph) {}
