/** 
    @file cjt_productos.cc
    @brief Implementació de la classe Cjt_productos.hh
*/
#include"Cjt_productos.hh"
Cjt_productos::Cjt_productos(){
    vector<producto>estanteria; 
}
Cjt_productos::    ~Cjt_productos(){}
//MODIFICADORES
void Cjt_productos::anadir_prod(){
    int num_prod_nuevos; 
    cin>>num_prod_nuevos;  
    cout<<num_prod_nuevos<<endl; 
    int p,v; 
    for (int i = 1; i <= num_prod_nuevos; ++i){
        cin>>p>>v;  
        producto prod; 
        prod.peso=p; 
        prod.volumen = v; 
        estanteria.push_back(prod); 
    }
}
//CONSULTORES
int Cjt_productos::num_prod() const{
    return estanteria.size()-1; 
}

bool Cjt_productos::existe_producto(int p) const{
    return (p > 0 and p <= estanteria.size()-1);
}
//LECTURA Y ESCRIPTURA

void  Cjt_productos::leer_cjto_productos(){
    int num_prod_nuevos; 
    cin>>num_prod_nuevos; 
    int p,v; 
    estanteria = vector<producto>(num_prod_nuevos+1);
    for (int i = 1; i <= num_prod_nuevos; ++i){
        cin>>p>>v;  
        producto prod; 
        prod.peso=p; 
        prod.volumen = v; 
        estanteria[i]=prod; 
    }
}
void Cjt_productos::escribir_producto(int p) const{
    if ( existe_producto(p)){
        cout<<p<<' '; 
        cout<<estanteria[p].peso<<' '<<estanteria[p].volumen << endl; 
    }
    else cout<<"error: no existe el producto"<<endl; 
}
int Cjt_productos::consultar_peso(int p) const{
    return estanteria[p].peso; 

}
int Cjt_productos::consultar_volumen(int p) const {
    return estanteria[p].volumen; 
}