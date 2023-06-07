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
/// ���������������
/// </summary>
void GenerateRandomData(int n) {
  srand((unsigned int)time(nullptr));
  num = 10;
  // ��ʼ��
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      edges[i][j] = INT_MAX;
    }
  }
  // ����Ȩ��
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      if (i < j) {
        edges[i][j] = edges[j][i] = rand() % 1000 + 1;
      }
    }
  }

  // ����Ƿ��������ǲ���ʽ
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

  // ��ӡ�鿴
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      cout << edges[i][j] << " ";
    }
    cout << endl;
  }

  // ������ļ�
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
