#include"FUNKCJE.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<iomanip>

using namespace std;

double **vec1; //first matrix
double **vec2; // second matrix
double **vec3; // result matrix

Matrices::Matrices(void)
{
row1=0, col1=0;
row2=0, col2=0;
}
void Matrices::Choice()
{
    cout <<"Lista wyboru:" <<"\n" <<"Nacisnij D zeby dodac.\n" << "Nacisnij O zeby odjac.\n" << "Nacisnij P zeby pomnozyc.\n";
    cout << "Nacisnij M zeby znalezc macierz odwrotna."<< endl;
    cin >> choice;
    if ((choice == 'D') || (choice == 'd'))
        {
            input();
            addition();
        }
        else if ((choice == 'O') || (choice == 'o'))
        {
            input();
            subtraction();
        }
        else if ((choice == 'P') || (choice == 'p'))
        {
            input();
            multiplication();
        }


    else if ((choice == 'M') || (choice == 'm'))
    {


        int i=0, j=0,n=0;
        float determinant=0;
        //get matrix dimensions

        cout<<"Wprowadz rozmiar macierzy:\n";
        cin>>n;

        float **matrix = new float*[n];
        float **adjoint = new float*[n];
        float **inverse = new float*[n];

        for (i = 0; i <n; ++i)
            matrix[i] = new float[n];
        for (i = 0; i <n; ++i)
            adjoint[i] = new float[n];
        for (i = 0; i <n; ++i)
            inverse[i] = new float[n];

        string nazwa;

        cout<<"Z jakiego pliku dane?\n";
        cin>>nazwa;
        nazwa = nazwa + ".txt";

        ifstream plik;
        plik.open(nazwa.c_str());
        if (!plik.is_open())
        {
            cout << "Blad otwarcia pliku." << endl;
            exit(0);
        }
        int counter=0;
        while(!plik.eof() && counter!=n*n)
        {
            for(i=0;i<n;i++){

                for(j=0;j<n;j++)
                {
                    plik>>matrix[i][j];
                     counter++;
                }
            }

        }
        plik.close();
        cout<<"\nWprowadzona macierz:";
        for(i = 0; i < n; i++){
            cout<<"\n";
            for(j = 0; j < n; j++)
                cout<<matrix[i][j]<<"\t";
        }

        determinant = calcDeterminant(matrix,n); //finding determinant
        cout<<"\n\nWyznacznik: "<<determinant;


        adjugate(matrix,adjoint,n);             //get adjoint of matrix

        cout<<"\n\nMacierz dolaczona:";
        for(i = 0; i < n; i++){
            cout<<"\n";
            for(j = 0; j < n; j++)
                cout<<adjoint[i][j]<<"\t";
        }

        if(inverseMatrix(matrix,inverse,n)){  //check for singular matrix, print result inverse if not
            cout<<"\n\nMacierz odwrotna:";
            for(i = 0; i < n; i++){
                cout<<"\n";
                for(j = 0; j < n; j++)
                {
                   cout<<setprecision(2)<<fixed<<inverse[i][j]<<"\t";
                }
            }
            ofstream plik_wy;
            plik_wy.open("wynik.txt");
            plik_wy<<"\n\nMacierz odwrotna:";
            for(i = 0; i < n; i++){
                plik_wy<<"\n";
                for(j = 0; j < n; j++)
                {
                   plik_wy<<setprecision(2)<<fixed<<inverse[i][j]<<"\t";
                }
            }
            plik_wy.close();


        }else{
            cout<<"\nMacierzy pojedynczej nie mozna odworcic.";
        }

       for (i = 0; i <n; ++i){
            delete [] matrix[i];
       }
       for (i = 0; i <n; ++i){
            delete [] inverse[i];
       }
       for (i = 0; i <n; ++i){
            delete [] adjoint[i];
       }

       delete [] matrix;
       delete [] adjoint;
       delete [] inverse;
        matrix = NULL;
       adjoint = NULL;
       inverse = NULL;
        }

        else
        {
            cout << "Nie ma takiej opcji. " << endl;
        }
    }
void Matrices::input()
{
    cout <<"Wprowadz rozmiar pierwszej macierzy (wiersz,kolumna) : " << endl;
    cin >> row1 >> col1;
    vec1 = new double*[row1];
    for(int i=0;i<row1;i++)
        vec1[i]= new double [col1];

   string nazwa;


    cout<<"Z jakiego pliku dane?\n";
    cin>>nazwa;
    nazwa = nazwa + ".txt";
    ifstream plik;
    plik.open(nazwa.c_str());
    if (!plik.is_open())
    {
        cout << "Blad otwarcia pliku." << endl;
        exit(0);
    }
    int counter=0;
    while(!plik.eof() && counter!=row1*col1)
    {
        for(int i=0;i<row1;i++){

            for(int j=0;j<col1;j++)
            {
                plik>>vec1[i][j];
                 counter++;
            }
        }

    }
    plik.close();

    /*cout << "Wprowadz wartosci do pierwszej macierzy. " << endl;
    for (int i=0;i<row1;i++)
    {
        for(int j = 0; j<col1; j++)
        {
            cin>>vec1[i][j];
        }
    }
    */
    cout << endl;

    cout << "Pierwsza macierz: " << row1 << "x" << col1 << endl;
    for (int i=0;i<row1;i++)
    {
        for(int j = 0; j<col1; j++)
        {
            cout << vec1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    if (choice == 'd' || choice == 'D' || choice == 'o' || choice == 'O' || choice == 'p' || choice == 'P')
       {

           cout << " Wprowadz rozmiar drugiej macierzy (wiersz,kolumna) : " << endl;
           cin >> row2 >> col2;

           vec2 = new double*[row2];
           for(int i=0;i<row2;i++)
               vec2[i]= new double [col2];
            string nazwa2;
           cout<<"Z jakiego pliku wprowadzic dane?\n";
           cin>>nazwa2;
           nazwa2 = nazwa2 + ".txt";

           ifstream plik2;
           plik2.open(nazwa2.c_str());
           if (!plik2.is_open())
           {
               cout << "Blad otwarcia pliku." << endl;
               exit(0);
           }
           int counter=0;
           while(!plik2.eof() && counter!=row2*col2)
           {
               for(int i=0;i<row2;i++){

                   for(int j=0;j<col2;j++)
                   {
                       plik2>>vec2[i][j];
                        counter++;
                   }
               }

           }
           plik2.close();
         /*
           for (int i=0;i<row2;i++)
           {
               for(int j = 0; j<col2; j++)
               {
                   cin>>vec2[i][j];
               }
           }
           */
           cout << endl;

             cout << "Druga macierz: " << row2 << "x" << col2 << endl;
           for (int i=0;i<row1;i++)
           {
               for(int j = 0; j<col2; j++)
               {
                   cout << vec2[i][j] << " ";
               }
               cout << endl;
           }
           cout << endl;

}

}

void Matrices::multiplication(){
    if(row1 != col2)
    {
        cout << "Nie mozna pomnozyc macierzy,\n wiersze pierwszej macierzy nie rownaja sie kolumnom drugiej macierzy" << endl;
        exit(0);
    }
    else
    {
        vec3 = new double *[row1];
        {
            for (int i=0;i<row1;i++)
            {
               vec3[i]= new double [col2];
            }
        }

        for (int i=0; i<row1;i++)
        {
            for(int j=0;j<col2;j++)
            {
                for(int k=0; k<col1; k++)
                {
                    vec3[i][j] += vec1[i][k]*vec2[k][j];
                }
            }
        }

        cout << "Wynikowa macierz: " << row1<<"x"<<col2 <<endl;
        for(int i=0; i<row1; i++)
        {
            for(int j=0; j<col2; j++)
            {
                cout << vec3[i][j] << " ";
            }
            cout << endl;
        }
    }

    ofstream plik_wy;
    plik_wy.open("wynik.txt");
    plik_wy << "Wynikowa macierz: " << row1<<"x"<<col2 <<endl;
    for(int i=0; i<row1; i++)
    {
        for(int j=0; j<col2; j++)
        {
           plik_wy << vec3[i][j] << " ";
        }
        plik_wy << endl;
    }

    plik_wy.close();

    for(int i=0; i<row1;i++)
    delete []vec1[i];
    delete []vec1;

    for(int i=0; i<row2;i++)
    delete []vec2[i];
    delete []vec2;

    for(int i=0; i<row1;i++)
    delete []vec3[i];
    delete []vec3;

    system("PAUSE");
}

void Matrices::addition()
{
    cout << "Macierz1 + Macierz2 = " << endl;
    vec3 = new double *[row1];
    {
        for (int i=0;i<row1;i++)
        {
           vec3[i]= new double [col2];
        }
    }
    for (int i = 0; i<row1; i++)
    {
        for(int j = 0; j<col1;j++)
        {
            vec3[i][j] = vec1[i][j]+vec2[i][j];
        }
    }
    for(int i=0;i<row1; i++)
    {
        for (int j=0; j<col1; j++)
        {
            cout << vec3[i][j] <<" ";
        }
        cout << endl;
    }


    ofstream plik_wy;
    plik_wy.open("wynik.txt");
    plik_wy << "Wynikowa macierz: " <<endl;
    for(int i=0; i<row1; i++)
    {
        for(int j=0; j<col1; j++)
        {
           plik_wy << vec3[i][j] << " ";
        }
        plik_wy << endl;
    }

    plik_wy.close();

    for(int i=0; i<row1;i++)
    delete []vec1[i];
    delete []vec1;

    for(int i=0; i<row2;i++)
    delete []vec2[i];
    delete []vec2;

    for(int i=0; i<row1;i++)
    delete []vec3[i];
    delete []vec3;

    system("PAUSE");
}

void Matrices :: subtraction()
{
    cout << "Macierz1 - Macierz2 = " << endl;
    vec3 = new double *[row1];
    {
        for (int i=0;i<row1;i++)
        {
           vec3[i]= new double [col2];
        }
    }
    for (int i = 0; i<row1; i++)
    {
        for(int j = 0; j<col1;j++)
        {
            vec3[i][j] = vec1[i][j]-vec2[i][j];
        }
    }
    for(int i=0;i<row1; i++)
    {
        for (int j=0; j<col1; j++)
        {
            cout << vec3[i][j] <<" ";
        }
        cout << endl;
    }

    ofstream plik_wy;
    plik_wy.open("wynik.txt");
    plik_wy << "Wynikowa macierz: " << endl;
    for(int i=0; i<row1; i++)
    {
        for(int j=0; j<col1; j++)
        {
           plik_wy << vec3[i][j] << " ";
        }
        plik_wy << endl;
    }

    plik_wy.close();

    for(int i=0; i<row1;i++)
    delete []vec1[i];
    delete []vec1;

    for(int i=0; i<row2;i++)
    delete []vec2[i];
    delete []vec2;

    for(int i=0; i<row1;i++)
    delete []vec3[i];
    delete []vec3;

    system("PAUSE");
}

float Matrices :: calcDeterminant(float **matrix,int n){

    int i=0,j=0,sign=1;
    float det=0;
    float **holder = new float*[n]; //for storing cofactors

    for (i = 0; i <n; ++i)
    {
        holder[i] = new float[n];   //allocate memory for each row of 2d array
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
           holder[i][j] = matrix[i][j];
        }
    }

    if (n==1)
    {                        //matrix contains single element
        return matrix[0][0];
    }
    for (int x =0; x<n;x++)
    {
        cofactor(matrix,holder,0,x,n);
        det += (sign* matrix[0][x] * calcDeterminant(holder,n-1));
        sign =(-sign);                //alternate sign for next term
    }


    for (int i = 0; i <n; i++)
    {
            delete[] holder[i];
       }
    delete [] holder;
    holder = NULL;

    return det;
}

void Matrices:: cofactor (float **matrix, float **holder,int r, int c, int n) //function gets the cofactor matrix
    {
    int i=0,j=0;

    for(int row =0; row<n; row++)
    {                                                 //loop through each index of matrix
        for (int col=0; col<n; col++)
        {
           if(row !=r && col!=c)
            {                                        //copy into holder, elements that are not in given row/co
                holder[i][j++] = matrix[row][col];
                    if (j== n-1)
                    {
                    j=0;
                    i++;
                    }
            }
        }
    }
   }


void Matrices:: adjugate(float **matrix,float **adju,int n)
 {                                                               //function gets the adjoint matrix
   int x=0, i=0, sign = 1;

    if (n==1)
    {
        adju[0][0] = 1;
    }
                                                                //array used to store cofactors of matrix
    float **holder = new float*[n];
     for (i = 0; i <n; ++i)
     {
        holder[i] = new float[n];
      }
     for (i=0; i<n; i++)
     {
         for (x=0; x<n; x++)
         {
           cofactor(matrix, holder, i, x, n);                    //get cofactor
              if ((i+x)%2==0)
                    sign=1;
                else                                             // sign is positive if sum of row and column index equals even.
                    sign=-1;
                    adju[x][i] = sign*calcDeterminant(holder, n-1); //transposition of cofactor matrix
          }
      }

    for (int i = 0; i <n; i++)
        {
            delete[] holder[i];
       }
    delete [] holder;
    holder = NULL;
}

bool Matrices::inverseMatrix(float **matrix, float **inverse, int n)
{
    int i=0,j=0;
    float det=0;
    float **adjoint = new float*[n];

    for (int i = 0; i <n; ++i)
    {
        adjoint[i] = new float[n];
    }
                                             //get determinant of matrix
    det = calcDeterminant (matrix,n);
    if (det==0){                             //singular matrix, has no inverse
        return false;
    }

     adjugate(matrix,adjoint,n);             //get adjoint of matrix

    for (i =0; i<n; i++)
    {                                        //get the inverse by dividing the matrix's adjoint and determinant
        for(j=0; j<n; j++)
        {
     inverse[i][j] = adjoint[i][j]/(det);    //cast det to float because invert matrix is float
        }
    }

    for (int i = 0; i <n; i++){
            delete[] adjoint[i];
       }
    delete [] adjoint;
    adjoint = NULL;

    return true;
}
