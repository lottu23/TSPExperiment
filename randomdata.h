#pragma once

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

const int MaxVexNum = 100;

unsigned int edges[MaxVexNum][MaxVexNum];

int num;

void recur(int node_a, int node_b, int weight);

/// <summary>
/// 生成随机城市数据
/// </summary>
void GenerateRandomData(int n) {
  srand((unsigned int)time(nullptr));
  num = 10;
  // 初始化
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      edges[i][j] = INT_MAX;
    }
  }
  // 设置权重
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      if (i < j) {
        edges[i][j] = edges[j][i] = rand() % 1000 + 1;
      }
    }
  }

  // 检查是否满足三角不等式
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      if (i < j) {
        for (int k = 0; k < num; k++) {
          if (k != i && k != j && edges[i][j] > edges[i][k] + edges[k][j]) {
            edges[i][j] = edges[j][i] = edges[i][k] + edges[k][j] - 1;
          }
        }
      }
    }
  }

  // 打印查看
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      cout << edges[i][j] << " ";
    }
    cout << endl;
  }

  // 输出到文件
  ofstream fout;
  fout.open("data.tsp");
  if (!fout.is_open()) {
    cout << "open file failed" << endl; 
  }
  fout << num << endl;
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      if (i < j) {
        fout << i + 1 << " " << j + 1 << " " << edges[i][j] << endl;
      }
    }
  }
}
