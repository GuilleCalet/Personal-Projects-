/** 
    @file ciudad.cc
    @brief Implementació de la classe Ciudad.hh
*/
#include"Ciudad.hh"
#ifndef NO_DIAGRAM
#include<cmath>
#endif

Ciudad::Ciudad(){
    p_total = 0 ; 
    v_total = 0 ; 
}
Ciudad::~Ciudad(){}

void Ciudad:: escribir_ciudad() const{
    map<int,compra_venda>::const_iterator it = inventario.begin(); 
    while ( it != inventario.end()){
        cout<<it->first<<' '<<it->second.tiene<<' ' <<it->second.necesita<<endl; 
        ++it;
    } 
}
void Ciudad::leer_ciudad( const Cjt_productos&cp){
    int n;
    cin >> n;
    inventario.clear();
    p_total = 0;
    v_total = 0;
    int id;
    for (int i = 0; i < n; ++i) {
        cin >> id; 
        compra_venda v; 
        cin >> v.tiene >> v.necesita;
        inventario[id] = v;
        
        int p = v.tiene*cp.consultar_peso(id) ; 
        p_total+= p; 
        int vol = v.tiene*cp.consultar_volumen(id); 
        v_total+=vol; 
    } 
}
void Ciudad:: anadir_producto(int p, int peso, int volumen){
    compra_venda v; 
    cin>>v.tiene>>v.necesita; 
    inventario[p]=v;
    p_total += peso * v.tiene; 
    v_total += volumen * v.tiene; 
}
void Ciudad:: modificar_prod_inventario(int p, int peso, int volumen, int nuevo_tiene, int nuevo_necesita) {
    map<int,compra_venda>::iterator it = inventario.find(p);
    p_total -= peso * it->second.tiene; 
    v_total -= volumen * it->second.tiene;
    p_total += peso * nuevo_tiene; 
    v_total += volumen * nuevo_tiene;
    it->second.necesita=nuevo_necesita; 
    it->second.tiene = nuevo_tiene; 
}
void Ciudad::quitar_producto(int p, int peso, int volumen){
    map<int,compra_venda>::iterator it = inventario.find(p);
    p_total -= peso * it->second.tiene; 
    v_total -= volumen * it->second.tiene;
    inventario.erase(it); 
}
void Ciudad::consulta_producto_de_ciudad (int p) const{
    map<int,compra_venda>::const_iterator it = inventario.find(p);
   cout<<it->second.tiene<<' '<<it->second.necesita<<endl;  
}
bool Ciudad::existe_producto(int p) const{
        map<int,compra_venda>::const_iterator it = inventario.find(p);
        return it != inventario.end(); 
}
int Ciudad:: pes_total() const{
    return p_total; 
}
int Ciudad:: vol_total() const{
    return v_total; 
}

void Ciudad::calcula_min(int& d1, int d2) {
    if (abs(d2) < d1) d1 = d2;
}

void Ciudad:: comerciar2 (Ciudad &ciudad2, const Cjt_productos&cp){
    int diferencia1, diferencia2; 
    map<int,compra_venda>::iterator it1 = inventario.begin();
    map<int,compra_venda>::iterator it2 = ciudad2.inventario.begin();
    while ( it1 != inventario.end() and it2 !=  ciudad2.inventario.end()){
        if ( it1->first > it2->first) ++it2; 
        else if (it1->first < it2->first ) ++it1; 
        else{
            diferencia1 = it1->second.tiene - it1->second.necesita; //-7
            //resta del tiene menos necesita de la ciudad 1 
            diferencia2 = it2->second.tiene - it2->second.necesita; //4
            // resta del tiene menos necesita de la ciudad 2 


            
            if ( diferencia1 > 0 and diferencia2 < 0 ){ // 1 positiva y 2 negativa
                calcula_min(diferencia1, diferencia2);
                it2->second.tiene += abs(diferencia1); 
                ciudad2.p_total += abs(diferencia1)*cp.consultar_peso(it1->first); 
                ciudad2.v_total += abs(diferencia1)*cp.consultar_volumen(it1->first); 
                it1->second.tiene -= abs(diferencia1);
                p_total -= abs(diferencia1)*cp.consultar_peso(it1->first); 
                v_total -= abs(diferencia1)*cp.consultar_volumen(it1->first);  
            }
            else if ( diferencia1 < 0 and diferencia2 > 0){ // 1 negativa y 2 positiva 
                calcula_min(diferencia2, diferencia1);
                it1->second.tiene += abs(diferencia2); 
                p_total += abs(diferencia2)*cp.consultar_peso(it2->first);
                v_total += abs(diferencia2)*cp.consultar_volumen(it2->first);
                it2->second.tiene -= abs(diferencia2);
                ciudad2.p_total -= abs(diferencia2)*cp.consultar_peso(it2->first); 
                ciudad2.v_total -= abs(diferencia2)*cp.consultar_volumen(it2->first); 
            }
            ++it1; 
            ++it2; 
        }
    }
}
int Ciudad:: consultar_diferencia_prod_compra(int p, pair<int,int>& anterior_cv, Barco &b) const{
    map<int,compra_venda>::const_iterator it = inventario.find(p);
    if(it == inventario.end()) return 0 ; 
    else{
        int resta = it->second.tiene - it->second.necesita;
        if ( resta > 0){
            if(resta <= b.num_compras_barco()- anterior_cv.first) return resta; 
            else return b.num_compras_barco()- anterior_cv.first;  
        } 
    }
    return 0 ; 

}
int Ciudad:: consultar_diferencia_prod_venta(int p, pair<int,int>& anterior_cv, Barco &b) const{
    map<int,compra_venda>::const_iterator it = inventario.find(p);
      if(it == inventario.end()) return 0 ; 
      else{
        int resta = it->second.necesita - it->second.tiene;
        if ( resta > 0 ){
            if ( resta <= b.num_ventas_barco()- anterior_cv.second) return resta; 
            else return b.num_ventas_barco()- anterior_cv.second;  
        }
      }
      return 0 ; 
}
void Ciudad:: modifica_prod_ruta(int producto_suma, int nueva_cantidad_suma, int producto_venta, int nueva_cantidad_venta, const Cjt_productos & cp){
    map<int,compra_venda>::iterator it1 = inventario.find(producto_suma);
    map<int,compra_venda>::iterator it2 = inventario.find(producto_venta);

    if (it1 != inventario.end()) it1->second.tiene -= nueva_cantidad_suma; 
    if (it2 != inventario.end()) it2->second.tiene += nueva_cantidad_venta; 

    p_total -= nueva_cantidad_suma * cp.consultar_peso(producto_suma); 
    v_total -= nueva_cantidad_suma * cp.consultar_volumen(producto_suma); 

    p_total += nueva_cantidad_venta * cp.consultar_peso(producto_venta); 
    v_total += nueva_cantidad_venta * cp.consultar_volumen(producto_venta);  
}