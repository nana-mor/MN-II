#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matriz;

void Newton();
void Portada();
int ElegirSistema();
Matriz Producto(Matriz matriza, Matriz matrizb);
Matriz Resta(Matriz a, Matriz b);
Matriz Inversa(Matriz matriz);



class Funciones{

  public:

    int sistema;

    Vector F(Vector X);
    double f(int fun, Vector X);
    Matriz J(Vector X);

};


int main() {
    Newton();
    return 0;
}


//Funciones del método

void Newton(){
    Funciones f;
    Portada();
    bool continua = true;
    char resp;
    while(true){ //Elegir sistema de ecuaciones
        f.sistema = ElegirSistema();
        while(true){ //Elegir datos iniciales


            cout<<"Desea cambiar los datos de entrada para buscar otra raiz? (S/N): "<<endl;
            cin>>resp;
            if(resp=='n'||resp=='N'){
                break;
            }
        }
        cout<<"Desea resolver otro sistema de ecuaciones? (S/N): "<<endl;
        cin>>resp;
        if(resp=='n'||resp=='N'){
            break;
        }
    }
    cout<<"**Finalizo el metodo"<<endl;
}

void Portada(){ //Se imprime información de la escuela y nombres de los integrantes del equipo
  
  cout<<"\n\nUNIVERSIDAD NACIONAL AUTONOMA DE MEXICO"<<endl;
  cout<<"Facultad de Estudios Superiores Acatlan"<<endl;
  cout<<"  Matematicas Aplicadas y Computacion"<<endl;
  cout<<"         Metodos Numericos II"<<endl;
  cout<<"               Grupo 2403\n\n"<<endl;
  cout<<"     Alonso Lopez Carlos Arnulfo"<<endl;
  cout<<"    Amador Navarro Dana Alejandra"<<endl;
  cout<<"      Rioja Romero Kevin Alexis"<<endl;
  cout<<"      Vargas Gonzalez Jose Luis\n\n"<<endl;
  
}

int ElegirSistema(){ //Función que imprime los sistemas de ecuaciones e ingresa la elección por consola
    int opcion;
    cout<<"SISTEMAS DE ECUACIONES:"<<endl;
  
    cout<<"\n\tSistema 1:"<<endl;
    cout<<"f1(x,y)=x^2+xy-10=0"<<endl;
    cout<<"f2(x,y)=y+3xy^2-50=0"<<endl;
    
    cout<<"\n\tSistema 2:"<<endl;
    cout<<"f1(x,y)=x^2+y^2-9=0"<<endl;
    cout<<"f2(x,y)=-e^x-2y-3=0"<<endl;
    
    cout<<"\n\tSistema 3:"<<endl;
    cout<<"f1(x,y,z)=2x^2-4x+y^2+3z^2+6z+z=0"<<endl;
    cout<<"f2(x,y,z)=x^2+y^2-2y+2z^2-5=0"<<endl;
    cout<<"f3(x,y,z)=3x^2-12x+y^2-3z^2+8=0"<<endl;
    
    cout<<"\n\tSistema 4:"<<endl;
    cout<<"f1(x,y,z)=x^2-4x+y^2=0"<<endl;
    cout<<"f2(x,y,z)=x^2-x-12-12y+1=0"<<endl;
    cout<<"f3(x,y,z)=3x^2-12x+y^2-3z^2+8=0"<<endl;

    // Se ingresa el sistema y se verifica que sea una entrada válida
    while(true){ //try-catch continúa hasta que se reciba una entrada válida
        try{
            cout<<"\nIngresa el sistema que deseas resolver: ";
            cin>>opcion; //Se ingresa la opción por consola
            if(0 < opcion && opcion <5) break; //Se verifica que sea un entero en un intervalo [1,4]
            else{
                cout<<"\n----> No es una opcion valida. Vuelve a intentarlo.\n\n";
                throw opcion;
            }
        }catch(...){ //En caso de error o si la entrada no se encuentra en el intervalo [1,4]
            //Se descarta la entrada
            cin.clear();
            cin.ignore(100, '\n');
        }
    }

    return opcion;
}

//Operaciones con matrices:

Matriz Producto(Matriz matriza, Matriz matrizb){ //Producto de 2 matrices
    int m= matriza.size();
    int p1= matriza[0].size();
    int p2=matrizb.size();
    int n=matrizb[0].size();
    Vector vec;
    double aux;
    Matriz producto;
    if(p1==p2){
        for(int i = 0 ; i < m ; i++){
            for(int j = 0 ; j < n ; j++){
                aux=0;
                for(int k = 0 ; k < p1 ; k++){
                    aux+=matriza[i][k]*matrizb[k][j];
                }
                vec.push_back(aux);
            }
            producto.push_back(vec);
            vec.clear();
        }
        return producto;
    }
}

Matriz Resta(Matriz a, Matriz b){
    Matriz resultado;
    Vector vecaux;
    int m = a.size();
    int n = a[0].size();
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j < n ; j++){
            vecaux.push_back(a[i][j]-b[i][j]);
        }
        resultado.push_back(vecaux);
        vecaux.clear();
    }
    return resultado;
}

Matriz Inversa(Matriz matriz){ //Inversa por Gauss-Jordan
    int n = matriz[0].size();
    double pivote;
    Vector vecaux;
    Matriz inversa;
    for(int i = 0 ; i < n ; i++){ //se crea la matriz identidad y se almacena en la matriz inversa
        for(int j = 0 ; j < n ; j++){
            if(i==j){
                vecaux.push_back(1);
            }else{
                vecaux.push_back(0);
            }
        }
        inversa.push_back(vecaux);
        vecaux.clear();
    }

    for(int i = 0 ; i < n ; i++){ //pivotes, cada columna
        double pivote=matriz[i][i];
        for(int j = 0 ; j < n ; j++){
            matriz[i][j]=matriz[i][j]/pivote;
            inversa[i][j]=inversa[i][j]/pivote;
        }
        for(int j = 0 ; j < n ; j++){//cada renglón
            if(i!=j){
                pivote=matriz[j][i];
                for(int k = 0 ; k < n ; k++){//actualizacion de renglón
                    matriz[j][k]=matriz[j][k]-(pivote*matriz[i][k]);
                    inversa[j][k]=inversa[j][k]-(pivote*inversa[i][k]);
                }
            }
        }
    }

    return inversa;
}

//Métodos de la clase Funciones

Vector Funciones::F(Vector X){
        Vector Fx=X;
        if(sistema==1||sistema==2){
            Fx[0]=f(1, X);
            Fx[1]=f(2, X);
        }else{
            Fx[0]=f(1, X);
            Fx[1]=f(2, X);
            Fx[2]=f(3, X);
        }
        return Fx;
    }

double Funciones::f(int fun, Vector X){

        if(sistema==1){         //se eligió el 1er sistema de ecuaciones

            if(fun == 1) return pow(X[0],2)+X[0]*X[1]-10;       //se desea calcular f1
            else return X[1]+3*X[0]*pow(X[1],2)-50;             //se desea calcular f2

        }else if(sistema == 2){ //se eligió el 2do sistema de ecuaciones
            
            if(fun == 1) return pow(X[0],2)+pow(X[1],2)-9;      //se desea calcular f1
            else return -exp(X[0])-2*X[1]-3;                    //se desea calcular f2
                
        }else if(sistema == 3){ //se eligió el 3er sistema de ecuaciones

            if(fun == 1) return 2*pow(X[0],2)-4*X[0]+pow(X[1],2)+3*pow(X[2],2)+6*X[2]+2;    //se desea calcular f1
            else if (fun == 2) return pow(X[0],2)+pow(X[1],2)-2*X[1]+2*pow(X[2],2)-5;       //se desea calcular f2
            else return 3*pow(X[0],2)-12*X[0]+pow(X[1],2)-3*pow(X[2],2)+8;                         //se desea calcular f3

            
        }else{                  //se eligió el 4to sistema de ecuaciones

            if(fun == 1) return pow(X[0],2)-4*X[0]+pow(X[1],2);                 //se desea calcular f1
            else if (fun == 2) return pow(X[0],2)-X[0]-12*X[1]+1;               //se desea calcular f2
            else return 3*pow(X[0],2)-12*X[0]+pow(X[1],2)-3*pow(X[2],2)+8;      //se desea calcular f3

        }
    }

Matriz Funciones::J(Vector X){
    Matriz Jac;
    int n = X.size();
    if(sistema==1){

        Jac.assign(2,{0,0});
        Jac[0][0]=2*X[0]+X[1];
        Jac[0][1]=X[0];
        Jac[1][0]=3*pow(X[1],2);
        Jac[1][1]=6*X[0]*X[1]+1;

    }else if(sistema == 2){

        Jac.assign(2,{0,0});
        Jac[0][0]=2*X[0];
        Jac[0][1]=2*X[1];
        Jac[1][0]=-exp(X[0]);
        Jac[1][1]=-2;

    }else if(sistema == 3){

        Jac.assign(3,{0,0,0});
        Jac[0][0]=4*X[0]-4;
        Jac[0][1]=2*X[1];
        Jac[0][2]=6*X[2]+6;
        Jac[1][0]=2*X[0];
        Jac[1][1]=2*X[1]-2;
        Jac[1][2]=4*X[2];
        Jac[2][0]=6*X[0]-12;
        Jac[2][1]=2*X[1];
        Jac[2][2]=-6*X[2];


    }else{

        Jac.assign(3,{0,0,0});
        Jac[0][0]=2*X[0]-4;
        Jac[0][1]=2*X[1];
        Jac[0][2]=0;
        Jac[1][0]=2*X[0]-1;
        Jac[1][1]=-12;
        Jac[1][2]=0;
        Jac[2][0]=6*X[0]-12;
        Jac[2][1]=2*X[1];
        Jac[2][2]=-6*X[2];


    }
    return Jac;
}






