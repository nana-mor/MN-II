#include <iostream>
#include <vector>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matriz;

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

class Funciones{
  public:
    int sistema;

    Matriz J(Vector X){
        Matriz Jac;
        if(sistema==1){

        }else if(sistema == 2){

        }else if(sistema == 3){

        }else{
            
        }
        return Jac;
    }

    Vector F(Vector X){
        Vector Fx;
        if(sistema==1){

        }else if(sistema == 2){

        }else if(sistema == 3){

        }else{
            
        }
        return Fx;
    }

    double f(int fun, double x){
        double resultado;
        if(sistema==1){

        }else if(sistema == 2){

        }else if(sistema == 3){

        }else{
            
        }
        return resultado;

    }
    

};


int main() {
    Funciones f;
    Portada();
    while(true){
        f.sistema = ElegirSistema();
        cout<<f.sistema<<endl;


        break;
    }

  
}