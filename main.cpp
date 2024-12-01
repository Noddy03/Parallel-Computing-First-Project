
#include <iostream>
#include<stdio.h>
#include<random>
#include<cmath> 
#include<cstdlib>
#ifdef _OPENMP
    #include <omp.h>
#endif
#include <vector>
#include <chrono>
using namespace std;


float randon_float();
void initializ(float *matrix,int n);
void stampa(float *matrix,int n);
void matTranspose(float *matrix,float *trans,int n);
void  matTransposeImp(float *matrix,float *trans,int n);
void matTransposeOMP(float *matrix,float *trans,int n);
bool checkSymOMP(float *matrix,int n);
bool checkSymImp(float *matrix,int n);
bool checkSym(float *matrix,int n);


int main(int argc, const char * argv[]) {
    bool symm;
    int n=0;
    // runnare con il compiler vs 
     //   cin>>argc;
     //  n=pow(2,argc);
     cout<<argv[1]<<endl;
        n=pow(2,atoi(argv[1]));
    float *matrix= new float[n * n];
float *transpose= new float[n * n];
cout<<"Matrix dimension: "<<n<<endl;
    initializ(matrix, n);
 auto start_cron = chrono::high_resolution_clock::now();
    matTranspose(matrix,transpose ,n);
  auto end_cron = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_cron - start_cron;
    cout << "Time taken by the Transposition code serial:" << elapsed.count() << " seconds" <<endl;   
     start_cron = chrono::high_resolution_clock::now();
    symm=checkSym(matrix, n);
     end_cron = chrono::high_resolution_clock::now();
    if(symm==true) cout<<"is symmetric"<<endl;
    else cout<<"is not symmetric"<<endl;
     elapsed = end_cron - start_cron;
     cout << "Time taken by the serial code symmetric check: " << elapsed.count() << " seconds" <<endl;   
    
cout<<endl;

   start_cron = chrono::high_resolution_clock::now();
    matTransposeImp(matrix,transpose ,n);
    end_cron = chrono::high_resolution_clock::now();
  elapsed = end_cron - start_cron;
     cout << "Time taken by the Transposition code IMP: " << elapsed.count() << " seconds" <<endl;   
  
    start_cron = chrono::high_resolution_clock::now();
   symm=checkSymImp(matrix, n);
    end_cron = chrono::high_resolution_clock::now();
   if(symm==true) cout<<"is symmetricImp"<<endl;
   else cout<<"is not symmetric"<<endl;
   elapsed = end_cron - start_cron;
     cout << "Time taken by the SymmetricIMP code: " << elapsed.count() << " seconds" <<endl;   
cout<<endl;

    start_cron = chrono::high_resolution_clock::now();
     matTransposeOMP(matrix,transpose ,n);
    end_cron = chrono::high_resolution_clock::now();
    elapsed = end_cron - start_cron;
     
     cout << "Time taken by the Transposition code OMP: " << elapsed.count() << " seconds" <<endl;   
     
 start_cron = chrono::high_resolution_clock::now();
   symm=checkSymOMP(matrix, n);
    end_cron = chrono::high_resolution_clock::now();
   if(symm==true) cout<<"is symmetric"<<endl;
   else cout<<"is not symmetric"<<endl;
elapsed = end_cron - start_cron;
   
     cout << "Time taken by the SymmetricOMP code: " << elapsed.count() << " seconds" <<endl;   
   
   cout<<endl;
delete[] matrix;
delete [] transpose;
cout<<"matrix deallocated dinamically"<<endl;
    return 0;
}


float randon_float(){
    return ((float)rand() / RAND_MAX) * (10 - 1) + 1;
}
void initializ(float *matrix,int n){
    cerr<<"matrix initialization"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            matrix[i * n + j]=randon_float();
        }
    }
   
    
}

void stampa(float *matrix,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<matrix[i * n + j]<<" ";
        }
        cout<<endl;
    }
}


void matTranspose(float *matrix,float *trans,int n){ 
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            trans[j * n + i]=matrix[i * n + j];
        }
    }
}


bool checkSym(float *matrix,int n){
    bool check=true;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(matrix[j * n + i]!=matrix[i * n + j]) {
                check=false;
            }
        }
      
    }
    return check;
}

void  matTransposeImp(float *matrix,float *trans,int n){
     
    //divide the matrix in 2 submatrixes
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n;j++){
         trans[j * n + i]=matrix[i * n + j];
        }
    }
    
    for(int i=n/2;i<n;i++){
        for(int j=0;j<n;j++){
            trans[j * n + i]=matrix[i * n + j];
        }
    }
}


bool checkSymImp(float *matrix,int n){
    bool check=true;
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n;j++){
            if(matrix[j * n + i]!=matrix[i * n + j]) {
                check=false;
            }
        }
    }
    for(int i=n/2;i<n;i++){
        for(int j=0;j<n;j++){   
           if(matrix[j * n + i]!=matrix[i * n + j]) {
                check=false;
            }
        }
    }
 
    return check;
}


void matTransposeOMP(float *matrix,float *trans,int n){
    //divide the matrix in 2 submatrixes and parallalize  
#pragma omp parallel num_threads(128) 
{       
 #pragma omp unroll(4) 8
    for(int i=0;i<n/2;i+=4){
        for(int j=0;j<n;j+=4){
         trans[j * n + i]=matrix[i * n + j];
        trans[j * n + i+1]=matrix[i * n + j+1];
         trans[j * n + i+2]=matrix[i * n + j+2];
     trans[j * n + i+3]=matrix[i * n + j+3];
        }
    }  
    #pragma omp unroll(4)  
    for(int i=n/2;i<n;i+=4){
        for(int j=0;j<n;j+=4){
             trans[j * n + i]=matrix[i * n + j];
        trans[j * n + i+1]=matrix[i * n + j+1];
         trans[j * n + i+2]=matrix[i * n + j+2];
         trans[j * n + i+3]=matrix[i * n + j+3];
        }
    }  

}  

}


bool checkSymOMP(float *matrix,int n){
  bool check=true;
#pragma omp parallel num_threads(128) 
{
     bool check=true;
   #pragma omp unroll(4) 
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n;j++){
            if(matrix[j * n + i]!=matrix[i * n + j]) {
                check=false;
            }
        }
    }
     #pragma omp unroll(4) 
    for(int i=n/2;i<n;i++){
        for(int j=0;j<n;j++){   
           if(matrix[j * n + i]!=matrix[i * n + j]) {
                check=false;
            }
        }
    }
}
    return check;
}