#include"Barco.hh"
/** 
    @file barco.cc
    @brief Implementació de la classe Barco.hh
*/
Barco:: Barco(){
}
void Barco:: leer_barco(){
    int compra,venta,c_compra,c_venta;
    cin>>compra>>c_compra>>venta>>c_venta; 
    cant_compra= c_compra; 
    cant_venta=c_venta; 
    id_compra=compra; 
    id_venta=venta;
}
void  Barco:: escribir_barco () const{
    cout<<id_compra<<' '<<cant_compra<<' '<<id_venta<<' '<<cant_venta << endl;

    for (int i = 0; i < ciudad_ruta.size(); ++i) {
        cout<<ciudad_ruta[i]<<endl; 
    }
}
void Barco::modificar_barco(int compra,int venta,int cantidad_compra,int cantidad_venta, const Cjt_productos &cp){
    if ( not cp.existe_producto(compra) or not cp.existe_producto(venta)){
                cout<<"error: no existe el producto"<<endl;
    }
    else if (venta == compra ){
        cout<<"error: no se puede comprar y vender el mismo producto"<<endl;
    }
    else{
        id_compra = compra; 
        id_venta = venta; 
        cant_compra = cantidad_compra; 
        cant_venta = cantidad_venta; 
    }
}
int Barco::consultar_prod_venta() const{
    return id_venta;
}
int Barco::consultar_prod_compra() const{
    return id_compra;
}
int Barco::num_ventas_barco() const{
    return cant_venta; 
} 
int Barco::num_compras_barco() const{
    return cant_compra; 
}
void Barco::modificar_ciudad_barco (string final_ruta){
    ciudad_ruta.push_back(final_ruta); 
}

void Barco::borrar_viajes() {
    ciudad_ruta = vector<string>();
}