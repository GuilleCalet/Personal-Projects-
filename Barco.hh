/** @file Barco.hh
    @brief Especificació de la classe Barco.hh 
*/
#ifndef _BARCO_HH_
#define _BARCO_HH_
#include "Cjt_productos.hh"
#ifndef NO_DIAGRAM 
#include"BinTree.hh"
#endif
/** @class Barco
    @brief Classe Barco: Representa un barco amb un id de compra i un numero de compras per fer, un id de venta i un numero de ventas per fer, i un recorregut, 
    que ens diu quines han esta tles ultimes ciutats en visitar per parte del barco. 

*/
class Barco
{
private:
    /**
        @brief Atribut barco: Identificador del producte que vol comprar el Barco.    
    */
    int id_compra; 
    /**
        @brief Atribut barco: Identificador del producte que vol vendre el Barco.    
    */
    int id_venta; 
    /**
        @brief Atribut barco: Numero de ventes que vol fer el barco.    
    */
    int cant_compra; 
    /**
        @brief Atribut barco: Numero de compres que vol fer el barco.    
    */
    int cant_venta;
    /**
        @brief Atribut barco: Ens diu quines han estat les ultimes ciutats en visitar del barco cada vegada que fa un viatge.    
    */
    vector<string> ciudad_ruta; 
public:
/**
        @brief Constructora per defecte.    
        \pre Cert.
        \post Crea un barco buit.
    */
    Barco();
    /**
        @brief Modificadora de barco: Modifica els atributs del barco.    
        \pre El barco existeix.
        \post Si el porducte de compra existeix en el cjt_productes i el id de compra es diferent al id de venta, actualitza els atributs de compra del barco(id i quantitat),i ho fa de la mateixa 
        manera per les ventes. Altrament si el producte no existeix, o be el id de venta es igual al de compra, es mostra pel canal estàndard de sortida un missatge d'error.
    */
    void modificar_barco(int compra,int venta,int cantidad_compra,int cantidad_venta, const Cjt_productos&cp);
    /**
        @brief Lectura del barco: Llegim els atributs de un barco.    
        \pre El barco existeix. 
        \post Llegim pel canal estandard d'entrada els atributs del barco, com ara els dos id i les dues quantitats, la de compra i la de venta i 
        els modifiquem en el barco.  
    */
    void leer_barco();
     /**
        @brief Consultora del barco: Em diu el numero de vendes que vol fer el barco.    
        \pre El barco existeix. 
        \post Retorna la quantitat de ventas que vol ver aquest barco.
    */
    int num_ventas_barco() const; 
    /**
        @brief Consultora del barco: Em diu el numero de compres qu evol fer el barco .    
        \pre El barco existeix. 
        \post Retorna la quantitat de compras que vol ver aquest barco.
    */
    int num_compras_barco() const; 
    /**
        @brief Consultora del barco: Em diu el producte que vol vendre el barco.    
        \pre El barco existeix. 
        \post Retorna l'identificador del producte de venta del barco.
    */
    int consultar_prod_venta() const; 
    /**
        @brief Consultora del barco: Em diu el producte que vol comprar el barco.    
        \pre El barco existeix. 
        \post Retorna l'identificador del producte de compra del barco.
    */
    int consultar_prod_compra() const; 
    /**
        @brief Escriptura del barco: Escriu pel canal estandard de sortida els atributs principals de barco, així com les seves ulitmes ciutats visitades despres de fer un viatje.    
        \pre El barco existeix.
        \post Escric pel canal estàndard de sortida els atributs del barco,com ara els seus id de compra i de venta amb els seus respectius objectius.
        També escribim pel canal estàndard de sortida les ultimes ciutat que ha visitat el barco en tots els seus viatges. 
    */
    void escribir_barco () const;
    /**
        @brief Modificadora del barco: Modifica l'atribut ciudad_ruta de barco.    
        \pre El barco existeix. 
        \post Afegim la nostra ruta, la ultima ciutat visitada despres de fer un viatge.
    */
    void modificar_ciudad_barco (string final_ruta);
    /**
        @brief Modificació del barco: Modifica l'atribut de la clase barco ciudad_ruta, per un nou, buit.    
        \pre El barco existeix.
        \post Modifiquem la nostra ruta del barco, per un a buida, es a dir la inicialitzem buida.
    */ 
    void borrar_viajes();  
};
#endif
