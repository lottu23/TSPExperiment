#include <fstream>
#include <iostream>

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

int main() {
  AMGraph graph;
  CreateUDN(graph);
  for (int i = 0; i < graph.node_num; i++) {
    for (int j = 0; j < graph.node_num; j++) {
      cout << graph.arcs[i][j] << " ";
    }
    cout << endl;
  }
}

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
  pair<int, int> pos[MaxNodeNum];
  int a;
  for (int i = 0; i < graph.node_num; i++) {
    fin >> a >> pos[i].first >> pos[i].second;
  }

  // 初始化结点距离为无限大值
  for (int i = 0; i < graph.node_num; i++) {
    for (int j = 0; j < graph.node_num; j++) {
      graph.arcs[i][j] = (ArcType)std::numeric_limits<float>().infinity();
    }
  }

  // 将权值设置为结点间的距离
  for (int i = 0; i < graph.node_num; i++) {
    for (int j = 0; j < graph.node_num; j++) {
      if (i < j)
        graph.arcs[i][j] = graph.arcs[j][i] =
            sqrt(pow(pos[j].first - pos[i].first, 2) +
                 pow(pos[j].second - pos[i].second, 2));
    }
  }
}

/// <summary>
/// 使用Prim算法获取最小生成树
/// </summary>
/// <param name="graph"></param>
void GetMST(const AMGraph& graph) {

}
