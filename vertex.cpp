#include "seaice.h"

//Object constructor
vertex::vertex(){
    mean = 0.0;
    degree = 0;
    sum = 0.0;
}

//Used for filling the 832 week array in this particular vertex
void vertex::setArray(float val, int index){
    arr[index] = val;
}

//Returns the entire 832 array of floating points
float* vertex::getArray(){
    return arr;
}

//Gets a particular index from the 832 array of floating points
float vertex::getIndex(int index){
    return arr[index];
}

//Calculates the mean for this particular vertex
void vertex::calculateMean(){
    float count = 0;
    float value = 0;
    if(isLand() == false)
    {
        for(int i = 0; i < 832; i++){
            if(arr[i] != 157){
                count++;
                value = value + arr[i];
            }
        }
        mean = value/count;
    }
    
}

//Calculates SUM((Vi - Vbar)^2)
void vertex::sumCor(){
    float val = 0.0;
    if(isLand() == false){
        for(int i = 0; i < 832; i++){
            if(arr[i] != 157){
                float subProb = arr[i] - mean;
                val = val + pow((subProb), 2.0f);
            }
        }
        sum = val;
    }
}

//Increases the degree count for this particular index
void vertex::increaseDegree(){
    degree++;
}

//Checks if this particular vertex is land
bool vertex::isLand(){
    bool flag = false;
    if(arr[0] == 168){
        flag = true;
    }
    return flag;
}

//Gets the mean
float vertex::getMean(){
    return mean;
}

//Gets the sum
float vertex::getSum(){
    return sum;
}

//Gets the degree
int vertex::getDegree(){
    return degree;
}