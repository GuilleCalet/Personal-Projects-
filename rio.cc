#include"Rio.hh"

/** 
    @file rio.cc
    @brief Implementació de la classe Rio.hh
*/

Rio::Rio(){
    BinTree<string>fluvial;
    map<string,Ciudad>comunidad;
}
Rio::~Rio(){}
void Rio:: leer_rio(){
    fluvial = BinTree<string>();
    comunidad.clear();
    leer_rio_segunda(fluvial,comunidad);
}
void Rio::leer_rio_segunda(BinTree<string>&fluvial, map<string,Ciudad>&comunidad){
    string nombre; 
    cin>>nombre; 
    if ( nombre != "#"){
        BinTree<string>izq; 
        BinTree<string>dcha; 
        leer_rio_segunda(izq,comunidad); 
        leer_rio_segunda(dcha,comunidad); 
        fluvial = BinTree<string>(nombre,izq,dcha); 
        Ciudad c; 
        comunidad.insert(make_pair(nombre,c)); 
    }
}
void Rio::leer_inventario(const Cjt_productos&cp){
    string c;
    while (cin>>c and c != "#") {
        map<string,Ciudad>::iterator it = comunidad.find(c); 
        it->second.leer_ciudad(cp);
    }
}
void Rio:: leer_ciudad(string c, const Cjt_productos&cp){ 
    if ( not existe_ciudad(c)){
        cout<<"error: no existe la ciudad"<<endl;
    }
    else{
        map<string,Ciudad>::iterator it = comunidad.find(c);
        it->second.leer_ciudad(cp);
    }
}
void Rio::escribir_ciudad(string c) const{
    if ( not existe_ciudad(c) ) {
        cout<<"error: no existe la ciudad"<<endl; 
    }
    else{
        map<string,Ciudad>::const_iterator it =  comunidad.find(c); 
        it->second.escribir_ciudad(); 
        cout<<it->second.pes_total()<<' '<<it->second.vol_total() << endl;
    }
}
bool Rio::existe_ciudad(string c)const {
    map<string,Ciudad>::const_iterator it = comunidad.find(c); 
    return it != comunidad.end(); 
}
bool Rio ::tiene_producto_inventario(string c, int p) const{
    map<string,Ciudad>::const_iterator it = comunidad.find(c);
     return it->second.existe_producto(p);
}
void Rio ::anadir_producto(string c, int p, Cjt_productos cp){

    if ( not cp.existe_producto(p)){
                cout<<"error: no existe el producto"<<endl; 
            }
    else if ( not existe_ciudad(c)){
                cout<<"error: no existe la ciudad"<<endl;
    }
    else if ( tiene_producto_inventario(c,p)){
                cout<<"error: la ciudad ya tiene el producto"<<endl;
    }
    else{
        map<string,Ciudad>::iterator it = comunidad.find(c);
        int peso = cp.consultar_peso(p);
        int volumen = cp.consultar_volumen(p);
        it->second.anadir_producto(p, peso,volumen); 
        cout<<it->second.pes_total()<<' '<<it->second.vol_total()<<endl; 
    }
}
void Rio :: modificar_ciudad(string c, int p,int nuevo_tiene,int nuevo_necesita,const Cjt_productos&cp){
    if ( not cp.existe_producto(p)) cout<<"error: no existe el producto"<<endl; 
    else if ( not existe_ciudad(c))cout<<"error: no existe la ciudad"<<endl;
    else if ( not tiene_producto_inventario(c,p))cout<<"error: la ciudad no tiene el producto"<<endl;
    else{
        int peso = cp.consultar_peso(p);
        int volumen = cp.consultar_volumen(p);
        map<string,Ciudad>::iterator it = comunidad.find(c);
        it->second.modificar_prod_inventario(p,peso,volumen,nuevo_tiene,nuevo_necesita);
        cout<<it->second.pes_total()<<' '<<it->second.vol_total()<<endl; 
    }
}
void Rio::quitar_prod_de_ciudad(string c, int p,const Cjt_productos&cp){ 
    if ( not cp.existe_producto(p)) cout<<"error: no existe el producto"<<endl; 
    else{
        if (not  existe_ciudad(c)){
            cout<<"error: no existe la ciudad"<<endl;    
        }
        else if (not tiene_producto_inventario(c,p)){
            cout<<"error: la ciudad no tiene el producto"<<endl; 
        }
        else{
            int peso = cp.consultar_peso(p);
            int volumen = cp.consultar_volumen(p);

            map<string,Ciudad>::iterator it = comunidad.find(c);
            it->second.quitar_producto(p,peso,volumen);  
            cout<<it->second.pes_total()<<' '<<it->second.vol_total()<<endl; 
        }
    }
}
void Rio ::consulta_prod_de_ciudad ( string c, int p, const Cjt_productos&cp) const{
    if ( not cp.existe_producto(p)) cout<<"error: no existe el producto"<<endl;
    else{
        if ( not existe_ciudad(c)){
            cout<<"error: no existe la ciudad"<<endl;
        }
        else if ( not tiene_producto_inventario(c,p)){
             cout<<"error: la ciudad no tiene el producto"<<endl;
        }
        else{
            map<string,Ciudad>::const_iterator it = comunidad.find(c);
            it->second.consulta_producto_de_ciudad(p); 
        }
    }
}
void  Rio:: comerciar(string c1, string c2, const Cjt_productos &cp){
    if ( not existe_ciudad(c1) or not existe_ciudad(c2)){
        cout<<"error: no existe la ciudad"<<endl;  
    }
    else if ( c1 == c2 ) cout<<"error: ciudad repetida"<<endl; 
    else{
        map<string,Ciudad>::iterator ciudad1 = comunidad.find(c1);
        map<string,Ciudad>::iterator ciudad2 = comunidad.find(c2);
        ciudad1->second.comerciar2(ciudad2->second, cp); 
    }

}
void Rio::redistribuir(const Cjt_productos &cp){
    redistribuir2(fluvial,cp);
}
void Rio::redistribuir2(const BinTree<string>&fluvial, const Cjt_productos &cp){
    if ( not fluvial.empty()){
        if ( not fluvial.left().empty()){
            BinTree<string>hijo_derecho = fluvial.right(); 
            BinTree<string>hijo_izquierdo = fluvial.left(); 

            comerciar(fluvial.value(), hijo_izquierdo.value(), cp); 
            comerciar(fluvial.value(), hijo_derecho.value(), cp); 

            redistribuir2(hijo_izquierdo,cp); 
            redistribuir2(hijo_derecho,cp); 
        }
        
    }
}
void Rio::hacerviaje(Barco& b,const  Cjt_productos &cp){
    list<pair<string,pair<int,int>>>ruta; 
    pair<int,int>anterior_cv = make_pair(0,0); 

    int num = calcular_ruta(fluvial,ruta, b, anterior_cv);

    cout<<num<<endl; 
    if (num > 0) {
        modificar_segun_ruta(ruta,comunidad,b,cp); 

        b.modificar_ciudad_barco(ruta.front().first); 
    }   
} 
int Rio::calcular_ruta(const BinTree<string>& fluvial, list<pair<string,pair<int,int>>> &ruta, Barco& b, pair<int,int> anterior_cv ) const{
    //retorno lo que yo y mis hijos hemos comprado + vendido
    if ( fluvial.empty()) return 0;
    else{
        map<string,Ciudad>::const_iterator it = comunidad.find(fluvial.value());
        int uni_comp, uni_vend; //COMPRA VENTA EN LA CIUDAD PERO OJO CON NO PASARME DE LOS LIMITES (b.num_comprar - anterior_cv.first)
        // uni_comp = quantitat de porductes que es poden comprar en la meva ciutat
        uni_comp = it->second.consultar_diferencia_prod_compra(b.consultar_prod_compra(),anterior_cv, b); 
        // uni_vend = quantitat de porductes que es poden vendre en la meva ciutat
        uni_vend =  it->second.consultar_diferencia_prod_venta(b.consultar_prod_venta(),anterior_cv, b); 
        // actualitzo el anteriors_comprats_ventus
        anterior_cv = make_pair(anterior_cv.first+uni_comp,anterior_cv.second+uni_vend);
        int suma_subarbol; 
        // si ja he comprat tot lo cenessari i he ventu tot lo necessari, finalitzo
        if(anterior_cv.first == b.num_compras_barco() and anterior_cv.second == b.num_ventas_barco()) {
            suma_subarbol = uni_comp + uni_vend;
            ruta.insert(ruta.end(), make_pair(fluvial.value(),make_pair(uni_comp, uni_vend)));
        }
        //sino::
        else {
            list<pair<string,pair<int,int>>> ruta_izq, ruta_dcha;
            // izq = num compres ventes subarbre esquerra
            int izq= calcular_ruta(fluvial.left(), ruta_izq, b, anterior_cv); 
             // dcha= num compres ventes subarbre dreta
            int dcha= calcular_ruta(fluvial.right(), ruta_dcha, b, anterior_cv);
            //condiciones per escollir quina es la millor ruta
            if ( izq > dcha){
                ruta = ruta_izq; 
                suma_subarbol = izq + uni_comp + uni_vend; 
            }
            else if ( dcha > izq ){
                ruta = ruta_dcha;   
                suma_subarbol = dcha + uni_comp + uni_vend; 
            }
            else {
                if( ruta_izq.size() > ruta_dcha.size()){
                    ruta = ruta_dcha; 
                    suma_subarbol = dcha + uni_comp + uni_vend; 
                }
                else{
                    ruta = ruta_izq; 
                    suma_subarbol = izq + uni_comp + uni_vend; 
                }
            }
            // evitem possar al map ciutats en les que no es faci res ni en elles ni sota seu
            if (suma_subarbol != 0) ruta.insert( ruta.end(), make_pair(fluvial.value(),make_pair(uni_comp, uni_vend)));
        }
        return suma_subarbol; 
    }
}
void Rio:: modificar_segun_ruta(list<pair<string,pair<int,int>>> &ruta, map<string,Ciudad>& comunidad,Barco &b, const Cjt_productos&cp){
    list<pair<string,pair<int,int>>>::iterator it = ruta.begin(); 
    while (it != ruta.end())
    {
        map<string,Ciudad>:: iterator it2 = comunidad.find(it->first); 
        it2->second.modifica_prod_ruta(b.consultar_prod_compra(),it->second.first, b.consultar_prod_venta(), it->second.second, cp) ;
        ++it;  
    }
} 
Ciudad Rio ::buscar_ciudad(string c) const{
     map<string,Ciudad>::const_iterator it = comunidad.find(c);
    return it->second; 
}
