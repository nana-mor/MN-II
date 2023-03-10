#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matriz;

int sistema;

void Newton();
void Portada();
int ElegirSistema();
Matriz Producto(Matriz matriza, Matriz matrizb);
Matriz Resta(Matriz a, Matriz b);
Matriz Inversa(Matriz matriz);
Vector F(Vector X);
double f(int fun, Vector X);
Matriz J(Vector X);
Vector PuntoInicial();
void Imprimir(int k, Vector X, Matriz J, Vector F, Matriz JF, double NF);
Vector ProductoEscalar(double d, Vector a);


int main() {
    time_t t_i, t_f;
    time(&t_i); //Se calcula la hora de inicio

    Newton();

    time(&t_f); //Se calcula la hora de fin
    cout<<"\nTiempo de ejecucion: "<<difftime(t_f,t_i)<< " segundos"; //Se imprime el tiempo que estuvo el usuario en el código

    return 0;
}


//Funciones del método

void Newton(){
    
    Vector X_k, X_k1, FX_k, FX_k1;
    Matriz Jacobiana;
    int iter_max, contador=0;
    double tol;
    Portada();
    bool continua = true;
    char resp;
    while(true){ //Elegir sistema de ecuaciones
        sistema = ElegirSistema();
        while(true){ //Elegir datos iniciales
            
            //Se ingresa el punto inicial
            X_k = PuntoInicial();

            //Se ingresan las iteraciones mínimas
            while(true){ //try-catch continúa hasta que se reciba una entrada válida
                try{
                    cout<<"\nIngresa la cantidad de iteraciones maximas: ";
                    cin>>iter_max; //Se ingresa la opción por consola
                    if(0 < iter_max ) break; 
                    else{
                        cout<<"\n----> No es una entrada valida. Vuelve a intentarlo.\n\n";
                        throw iter_max;
                    }
                }catch(...){ //En caso de error 
                    //Se descarta la entrada
                    cin.clear();
                    cin.ignore(100, '\n');
                }
            }

            //Se ingresa la tolerancia
            while(true){ //try-catch continúa hasta que se reciba una entrada válida
                try{
                    cout<<"\nIngresa la tolerancia: ";
                    cin>>tol; //Se ingresa la opción por consola
                    if(0 < tol && tol < 1) break; 
                    else{
                        cout<<"\n----> No es una entrada valida. Vuelve a intentarlo.\n\n";
                        throw tol;
                    }
                }catch(...){ //En caso de error 
                    //Se descarta la entrada
                    cin.clear();
                    cin.ignore(100, '\n');
                }
            }

            //Se lleva a cabo el método
            /*contador=0;

            cout<<"k"<<" | "<<"Xk"<<"\t\t"<<"J(Xk)"<<"\t\t"<<"F(Xk)"<<"\t\t"<<"-(J-1)*F"<<"\t\t";

            cout<< "\t|\t||F||\t|\tEa"<<endl;

            while(contador <= iter_max){
                FX_k=F(X_k);
                Jacobiana = J(X_k);
                if(contador = 0){
                    Imprimir(contador, X_k, Jacobiana, FX_k, ProductoEscalar(-1,Producto(Inversa(Jacobiana),FX_k)),max(FX_k));
                }else{

                }
                X_k1 = Resta(X_k,Producto(Inversa(Jacobiana),FX_k));
                contador++;
                break;
            }*/

            

            cout<<"\nDesea cambiar los datos de entrada para buscar otra raiz? (S/N): ";
            cin>>resp;
            if(resp=='n'||resp=='N'){ //si se ingresa que no, se termina el while y ejecuta la siguiente línea
                break;
            }
        }
        cout<<"\nDesea resolver otro sistema de ecuaciones? (S/N): ";
        cin>>resp;
        if(resp=='n'||resp=='N'){ //si se ingresa que no, se termina el while y termina el programa
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

Vector Producto(Matriz matriza, Vector veca){ //Producto de matriz y vector
    int m=matriza.size();
    int p1=matriza[0].size();
    int p2=veca.size();
    double aux;
    Vector producto;
    if(p1==p2){
        for(int i = 0 ; i < m ; i++){
            aux=0;
            for(int k = 0 ; k < p1 ; k++){
                aux+=matriza[i][k]*veca[k];
            }
            producto.push_back(aux);
        }
    }else{
        cout<<"No es posible realizar el producto con las dimensiones ingresadas. "<<endl;
    }
    return producto;
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

Vector Resta(Vector a, Vector b){
    Vector resultado;
    int m = a.size();
    int n = a.size();
    for(int i = 0 ; i < m ; i++){
        resultado.push_back(a[i]-b[i]);
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

Vector ProductoEscalar(double d, Vector a){
    Vector vecaux;
    int n = a.size();
  for(int j = 0 ; j < n ; j++){
        vecaux.push_back(a[j]*d);
    }
    return vecaux;
}

double max(Vector X){
    double aux;
    aux=X[0];
    for(int i = 0 ; i < X.size() ; i++){
        if(X[i]>aux){
            aux=X[i];
        }
    }
    return aux;
}

//Funciones para el método

Vector F(Vector X){
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

double f(int fun, Vector X){

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

Matriz J(Vector X){
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

Vector PuntoInicial(){
    Vector X;
    double aux;

    cout<<"\nIngresa los valores de tu punto inicial"<<endl;
    cout<<"Ingresa x: ";
    cin>>aux;
    X.push_back(aux);

    cout<<"Ingresa y: ";
    cin>>aux;
    X.push_back(aux);

    if(sistema==3||sistema==4){
        cout<<"Ingresa z: ";
        cin>>aux;
        X.push_back(aux);
    }

    return X;
}

void Imprimir(int k, Vector X, Matriz J, Vector F, Vector JF, double NF){
    int n = X.size();
    for(int i = 0 ; i < n ; i++){
        if(i==0){
            cout<<k<<" | "<<X[i]<<"\t|\t";
            for(int j ; j < n ; j++){
                cout<<J[i][j]<<"\t";
            }
            cout<< "\t|\t"<<JF[i]<<"\t|\t"<<NF<<endl;
        }else{
            cout<<"  | "<<X[i]<<"\t|\t";
            for(int j ; j < n ; j++){
                cout<<J[i][j]<<"\t";
            }
            cout<< "\t|\t"<<JF[i]<<"\t|\t"<<endl;

        }
    }
}




