#include "seaice.h"

int main(int argc, char *argv[])
{
    //Instantiating graphs
    graph obj1;
    graph obj2;
    graph obj3;

    //Calculations for Graph One
    std::cout << "GRAPH 1 HISTOGRAM (.95):" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    obj1.setGPH();                      //Reading files and filling graph
    obj1.setThresh(0.95);               //Setting threshold for graph
    obj1.initMeanSum();                 //Calculating Means and Sums for all vertices
    obj1.createEdges();                 //Calculating correlation between vertices
    obj1.printHistogramTWO();              //Printing histogram
    std::cout << std::endl;

    std::cout << "GRAPH 2 HISTOGRAM (.925):" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    obj2.setGPH();                      //Reading files and filling graph
    obj2.setThresh(0.925);              //Setting threshold for graph
    obj2.initMeanSum();                 //Calculating Means and Sums for all vertices
    obj2.createEdges();                 //Calculating correlation between vertices
    obj2.printHistogramTWO();              //Printing histogram
    std::cout << std::endl;

    std::cout << "GRAPH 3 HISTOGRAM (.9):" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    obj3.setGPH();                      //Reading files and filling graph
    obj3.setThresh(0.9);                //Setting threshold for graph
    obj3.initMeanSum();                 //Calculating Means and Sums for all vertices
    obj3.createEdges();                 //Calculating correlation between vertices
    obj3.printHistogramTWO();              //Printing histogram
    std::cout << std::endl;

    
    std::cout << "GRAPH 1 COMPONENTS (.95):" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    obj1.DFS();
    std::cout << std::endl;
    obj1.printComponents();
    std::cout << std::endl;
    
    std::cout << "GRAPH 2 COMPONENTS (.925):" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    obj2.DFS();
    std::cout << std::endl;
    obj2.printComponents();
    std::cout << std::endl;

    std::cout << "GRAPH 3 COMPONENTS (.9):" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    obj3.DFS();
    std::cout << std::endl;
    obj3.printComponents();
    std::cout << std::endl;

    return 0;  
} 