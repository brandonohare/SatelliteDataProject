#ifndef VERTEX_H
#define VERTEX_H
class vertex{
    private:
    float arr[832];
    float mean;
    int degree;
    float sum;

    public:
    vertex();
    void setArray(float val, int index);
    float* getArray();
    float getIndex(int index);
    void calculateMean();
    void sumCor();
    void increaseDegree();
    bool isLand();
    float getMean();
    float getSum();
    int getDegree();
};
#endif