#include <fstream>
#include <iostream>

#include"randomdata.h"

using namespace std;

using ArcType = float;

const int MaxNodeNum = 100;

/// <summary>
/// 邻接矩阵结构
/// </summary>
typedef struct {
  ArcType arcs[MaxNodeNum][MaxNodeNum];
  int node_num, arc_num;
} AMGraph;

void CreateUDN(AMGraph& graph);
void GetMST(const AMGraph& graph);

int main() { GenerateRandomData(50); }

/// <summary>
/// 输入数据并生成相应的邻接矩阵
/// </summary>
/// <param name="graph">生成的邻接矩阵表</param>
void CreateUDN(AMGraph& graph) {
  // 输入数据
  ifstream fin;
  fin.open("att8.tsp", ios::in);
  if (!fin.is_open()) {
    cout << "open file failed" << endl;
  }

  fin >> graph.node_num;
  graph.arc_num = graph.node_num * (graph.node_num - 1) / 2;

  int a, b, w;
  for (int i = 0; i < graph.arc_num; i++) {
    fin >> a >> b >> w;
    graph.arcs[a][b] = graph.arcs[b][a] = w;
  }

}

/// <summary>
/// 使用Prim算法获取最小生成树
/// </summary>
/// <param name="graph"></param>
void GetMST(const AMGraph& graph) {

}
