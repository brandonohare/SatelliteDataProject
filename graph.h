#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"

struct edge{
    int index;
    edge* next;
    //int color;
};

class graph{
    public:
    static vertex GPH[63][63];
    private:
    edge* EDGES[3969];
    float threshold;
    int COMP[3969];
    int count;
    bool visited[3969];

    public:
    void setGPH();
    void initEdges();
    void setThresh(float val);
    void initMeanSum();
    void oneDTwoD(int i, int arr[]);
    void createEdges();
    void calculateCorrelation(int x1, int x2, int y1, int y2);
    void addToGraph(int x1, int x2, int y1, int y2);
    void printHistogram();
    void printGraph();
    void printEdges();
    void DFS();
    void DFS_Visit(int u);
    void printComponents();
    void initComponents();
    void printHistogramTWO();
    
};
#endif