#include "seaice.h"

vertex graph::GPH[63][63];

//Fills the graph with all data from files
void graph::setGPH(){

    int year = 1990;
    std::string fileName;
    std::stringstream ss;
    std::stringstream tt;
    std::string yearStr;
    std::string weekStr;
    int temp = 0;
    int yearAdded;
    float data;
    
    for(int i = 0; i < 16; i++)
    {
        yearAdded = year + i;
        ss << yearAdded;
        ss >> yearStr;
        for(int j = 1; j < 53; j++)
        {
            tt << j;
            tt >> weekStr;
            if(j < 10)
            { 
                fileName = "CS310_project_subregion/" + yearStr + "/Beaufort_Sea_diffw0" + weekStr + "y" + yearStr + "+landmask"; 
            }
            else
            {
                fileName = "CS310_project_subregion/" + yearStr + "/Beaufort_Sea_diffw" + weekStr + "y" + yearStr + "+landmask";
            }
            std::ifstream myFile(fileName, std::ios::in|std::ios::binary);
            for(int k = 0; k < 63; k++)
            {
                for(int l = 0; l < 63; l++)
                {
                    myFile.read((char*)&data, 4 );
                    GPH[k][l].setArray(data, temp); 
                }
            }
           tt.clear();
           temp++;
        }
        ss.clear();
    }
    initEdges();
}

//Initializes all edges to NULL
void graph::initEdges(){
    for(int i = 0; i < 3969; i++){
        EDGES[i] = NULL;
        
    }
}

//Sets the threshold for this particular graph
void graph::setThresh(float val){
    threshold = val;
}

//Initializes all means ands sums for all vertices within this graph (SHOULD BE CALLED BEFORE ANY OTHER OPERATIONS)
void graph::initMeanSum(){
    for(int i = 0; i < 63; i++){
        for(int j = 0; j < 63; j++){
            if(GPH[i][j].isLand() == false){
                GPH[i][j].calculateMean();
                GPH[i][j].sumCor();
            }
        }
    }
}

//Turns a one dimensional index into a two dimensional one
void graph::oneDTwoD(int i, int arr[]){
    arr[0] = i/63;
    arr[1] = i%63;
}

//Iterates through the entire array and creates every edge
void graph::createEdges(){
    
    int arr1[2];
    for(int i =  0; i < 3969;i++){
    oneDTwoD(i,arr1);

        int x1 = arr1[0];
        int x2 = arr1[1];

        for(int j = i + 1;j < 3969;j++){
        
            int arr2[2];
            oneDTwoD(j,arr2);
            int y1 = arr2[0];
            int y2 = arr2[1];
            if(j > i){
                calculateCorrelation(x1, x2, y1, y2);
            }
        }
    }
}

//Calculates a correlation betweeen to vertices
void graph::calculateCorrelation(int x1, int x2, int y1, int y2){

    float meanX;
    float meanY;
    float sumX;
    float sumY;
    float val = 0.0;
    float correlation;
    float xVal;
    float yVal;
    float denom;
    
    if((GPH[x1][x2].isLand() != true) && (GPH[y1][y2].isLand() != true)){
        sumX = GPH[x1][x2].getSum();
        sumY = GPH[y1][y2].getSum();
        meanX = GPH[x1][x2].getMean();
        meanY = GPH[y1][y2].getMean();
        for(int i = 0; i < 832; i++){
            float xi = GPH[x1][x2].getIndex(i);
            float yi = GPH[y1][y2].getIndex(i);
            if((xi != 157) && (yi != 157)){
                xVal = xi - meanX;
                yVal = yi - meanY;
                val = val + ((xVal)*(yVal));
            }
        }
        denom = sqrtf(sumX*sumY);
        correlation = val/(denom);
        if(correlation < 0){
            correlation = correlation * -1;
        }
        if(correlation >= threshold){
            addToGraph(x1, x2, y1, y2);
        }
    }
    else{}
}

//Adds an edge to the graph
void graph::addToGraph(int x1, int x2, int y1, int y2){
    if(EDGES[x1*63+x2] == NULL){
        edge* temp = new edge;
        temp->index = (y1*63+y2);
        temp->next = NULL;
        EDGES[x1*63+x2] = temp;
    }
    else{
        edge* temp = new edge;
        temp = EDGES[x1*63+x2];
        edge* temp2 = new edge;
        temp2->index = y1*63+y2;
        temp2->next = temp;
        EDGES[x1*63+x2] = temp2;
    }
    if(EDGES[y1*63+y2] == NULL){
        edge* temp = new edge;
        temp->index = (x1*63+x2);
        temp->next = NULL;
        EDGES[y1*63+y2] = temp;
    }
    else{
        edge* temp = new edge;
        temp = EDGES[y1*63+y2];
        edge* temp2 = new edge;
        temp2->index = x1*63+x2;
        temp2->next = temp;
        EDGES[y1*63+y2] = temp2;
    }
    
    GPH[x1][x2].increaseDegree();
    GPH[y1][y2].increaseDegree();
}

//Prints the histogram for this particular graph
void graph::printHistogram(){
    int max = 0;
    for(int i = 0; i < 63; i++){
        for(int j = 0; j < 63; j++){
            int val = GPH[i][j].getDegree();
            if(val > max){
                max = val;
            }
        }
    }
    int* degArr = new int[max];
    for(int i = 0; i < max + 1; i++){
        degArr[i] = 0;
    }
    for(int i = 0; i < 63; i++){
        for(int j = 0; j < 63; j++){
            int val = GPH[i][j].getDegree();
            if(GPH[i][j].isLand() == false){
                degArr[val] = degArr[val] + 1;
            }
            
        }
    }
    for(int i = 0; i < max + 1; i++){
        std::cout << "# VERTICES W/DEGREE " << i << ": (" << degArr[i] << ") ";
        for(int j = 0; j < degArr[i]; j++){
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    
}

void graph::printHistogramTWO(){
    int max = 0;
    int value = 0;
    for(int i = 0; i < 3969; i++){
        value = 0;
        if(EDGES[i] != NULL){
            value++;
            edge* temp = EDGES[i];
            while(temp->next != NULL){
                value++;
                temp = temp->next;
            }
            if(value > max){
                max = value;
            }
        }
    }

    int* degArr = new int[max];
    for(int i = 0; i < max + 1; i++){
        degArr[i] = 0;
    }

    for(int i = 0; i < 3969; i++){
        value = 0;
        if(EDGES[i] != NULL){
            value++;
            edge* temp = EDGES[i];
            while(temp->next != NULL){
                value++;
                temp = temp->next;
            }
            degArr[value] = degArr[value] + 1;
        }
        else{
            degArr[value] = degArr[value] + 1;
        }
    }

    for(int i = 0; i < max + 1; i++){
        std::cout << "# VERTICES W/DEGREE " << i << ": (" << degArr[i] << ") ";
        for(int j = 0; j < degArr[i]; j++){
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}
//Prints every aspect of the graph. Used for debugging
void graph::printGraph(){
    for(int i = 0; i < 63; i++){
        for(int j = 0; j < 63; j++){
            float val1 = GPH[i][j].getMean();
            float val2 = GPH[i][j].getSum();
            int degree = GPH[i][j].getDegree();
            std::cout << "GPH[" << i << "][" << j << "]: ";
            std::cout << "Mean: " << val1 << " Sum: " << val2 << " \nDegree: " << degree << std::endl;
            
            float* arr;
            arr = GPH[i][j].getArray();
            
            for(int k = 0; k < 832; k++)
            {
                std::cout << arr[k] << " ";
            }
            std::cout << std::endl;
        }
    }
}

//Prints all the edges that were created as a result of Pearson's correlation. Used for debugging
void graph::printEdges(){
    int count = 0;
    for(int i = 0; i < 3969; i++){
        count = 0;
        if(EDGES[i] == NULL){
            count = 0;
            std::cout << i << ": " << count << std::endl;
        }
        else{
            edge* temp = new edge;
            temp = EDGES[i];
            std::cout << i << ": ";
            while(temp->next != NULL){
                std::cout << "Index: [" << temp->index << "] --> ";
                temp = temp->next;
                count++;
            }
            std::cout << "Count: " << count << std::endl;
        }
        
    }
}


void graph::DFS(){
    //int tracking = 1;
    initComponents();
    for(int i = 0; i < 3969; i++){
        count = 0;
        if(visited[i] == false){
            
            DFS_Visit(i);
            count++;
            if(count != 0){
                //std::cout << "COMPONENT " << tracking << " IS SIZE: " << count << std::endl;
                //tracking++;
            }
            COMP[count] = COMP[count] + 1;
            
        }
    }
}

void graph::DFS_Visit(int u){
   
    visited[u] = true;
    edge* temp = EDGES[u];
    while(temp != NULL){
        //std::cout << " H1 ";
        int v = temp->index;
        if(visited[v] == false){
            //std::cout << " IND: " << v << " ";
            DFS_Visit(v);
            count++;
        }
        temp = temp->next;
        
    }
}

void graph::printComponents(){
    for(int i = 0; i < 3969; i++){
        if(COMP[i] != 0){
            std::cout << "# OF COMPONENTS W/SIZE " << i << ": " << COMP[i] << std::endl;
        }
    }
}

void graph::initComponents(){
    for(int i = 0; i < 3969; i++){
        COMP[i] = 0;
    }
}