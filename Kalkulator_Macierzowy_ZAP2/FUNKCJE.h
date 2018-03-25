#ifndef FUNKCJE_H
#define FUNKCJE_H

using namespace std;
class Matrices
{
public:
    Matrices(void);
    void Choice();
    void input();
    void multiplication();
    void addition();
    void subtraction();
    void Transpose();
    float calcDeterminant (float **matrix,int n);
    void cofactor (float **matrix,float **holder,int r, int c, int n);
    void adjugate(float **matrix,float **adju,int n);
    bool inverseMatrix(float **matrix, float **inverse,int n);

private:
    int row1, col1;
    int row2, col2;
    char choice;


};

#endif // FUNKCJE_H
