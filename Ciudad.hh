/** @file Ciudad.hh
    @brief Especificació de la classe Ciudad.hh 
*/
#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_
#include"Cjt_productos.hh"
#include"Barco.hh"

/** @class Ciudad
    @brief Classe Ciudad: Representa ciutat amb identificador, un inventari de productes, un pes total i un volum total. 

*/
class Ciudad
{
private:
/** @brief En l'inventari d'una ciutat, cada producte té dos atributs principals, per una banda, tenim la disponibilitat d'aquest producte,
* que seria la quantitat de la qual despon, i per un altre la quantitat que necessita o desitja.
 */
    struct compra_venda{
        int tiene; 
        int necesita; 
    };
    /**
        @brief Atribut ciutat: Inventari un es guarden els porductes i la quantitat que tenim i necessitam d'aquests.     
    */
     map<int,compra_venda> inventario;
     /**
        @brief Atribut ciutat: Pes total de la ciutat, tenint en compte el pes del producte i la quantitat de productes que tenim.     
    */ 
    int p_total; 
    /**
        @brief Atribut ciutat: Volum total de la ciutat, tenint en compte el volum del producte i la quantitat de productes que tenim.     
    */ 
    int v_total; 
    /**
        @brief Consultora.    
        \pre Cert.
        \post Si la primera diferencia es estrictament mes gran que la segona, modifiquem la primera possant el valor de la segona, 
        es a dir, sempre que comerciem, donem a l'altre ciutat el minim que necessita, per arribar al seu objectiu.
    */
    static void calcula_min(int& d1, int d2);
public:
//CONSTRUCTORES

    /**
        @brief Constructora per defecte.    
        \pre Cert.
        \post Crea una ciutat amb el seu pes i volum total de valor 0.
    */
    Ciudad();
//DESTRUCTORES
    /**
        @brief Destructora per defecte.    
        \pre Cert.
        \post Destrueix una ciutat buida.
    */
~Ciudad();
//MODIFICADORAS
    /**
        @brief Modificadora de Ciutat: Afegeix al paràmetre implícit un nou producte.    
        \pre Existeix la ciutat, el producte, i aquest producte no esta en la ciutat del pi.
        \post S'ha afegit al inventari de la ciudat el nou producte, amb el seu pes i el seu volum, i s'ha modificat tant el pes com el volum
        total de la ciutat. 
    */
    void anadir_producto(int p, int peso, int volumen); 
    /**
        @brief  Modificadora de Ciutat: Modifica al paràmetre implícit un nou producte.    
        \pre Existeix el porducte, existeis la ciutat del Pi, i el producte esta a la ciutat del Pi.
        \post Modifica els parametres del prducte p, canviant les quantitats que tens i/o que necesites, i modifica també el pes i el volum. 
        totals de la ciutat.
    */
    void modificar_prod_inventario(int p, int peso, int volumen, int nuevo_tiene, int nuevo_necesita);
     /**
        @brief  Modificadora de Ciutat: Esborra al paràmetre implícit un nou producte.    
        \pre La ciutat existeix.
        \post Esborra del parametre implicit un cert producte, canviant pes i volumen de la ciutat.  
    */
    void quitar_producto(int p, int peso, int volumen);
    /**
        @brief Modificadora ciutat: Comercia entre dues ciutants, repartint-se els productes segons els seus interessos.    
        \pre Les dues ciutats existeixen.
        \post Dugues ciutats han comerciat entre elles, repartint els produtes que a una li sobren i a la altre li falten, aconseguint així
         apropar-se al màxim al seu objectiu.   
    */
    void comerciar2 (Ciudad &ciudad2, const Cjt_productos &cp); 
//CONSULTORAS
    /**
        @brief Consultora d'un producte: Em diu els atributs del producte p en la ciutat del PI.    
        \pre El producte existeix, la ciutat també, i el porducte esta present en la ciutat del PI
        \post Escriu pel canal estàndard de sortida cuantes unitats tenim d'aquest producte, i cuantes en necessitem a la ciutat del paràmetre implícit.  
    */
    void consulta_producto_de_ciudad (int p) const;
    /**
        @brief  Consultora de Ciutat:Retorna el pes total de la ciutat.    
        \pre Cert.
        \post Retorna el pes total de la ciutat indicada en el parametre implicit.  
    */
    int pes_total () const;
    /**
        @brief Consultora de Ciutat:Retorna el volum total de la ciutat.    
        \pre Cert.
        \post Retorna el volum total de la ciutat indicada en el parametre implicit.  
    */
    int vol_total() const; 

    /**
        @brief Consultora de Ciutat:Bool sobre si existeix o no un producte.    
        \pre Cert.
        \post Retorna cert si el producte existeix en l'inventari de la ciutat, fals en cas contrari.  
    */
    bool existe_producto(int p) const; 
    /**
        @brief Consultora de Ciutat:Em diu la diferecnia entre les quantitats que tinc i les que necesito del producte que vull comprar.    
        \pre Cert.
        \post En cas de que no superem la quantitat requerida pel barco, retorna la resta entre les que tinc i les que necessito, 
        en canvi, si superem la quantitat requerida pel barco, el numero retornat es lo que ens falta per arribar a lo requerit pel barco.  
    */
    int consultar_diferencia_prod_compra(int p, pair<int,int>& anterior_cv, Barco &b) const;
    /**
        @brief Consultora de Ciutat:Em diu la diferecnia entre les quantitats que tinc i les que necesito del producte que vull vendre.    
        \pre Cert.
        \post En cas de que no superem la quantitat requerida pel barco, retorna la resta entre les que tinc i les que necessito, 
        en canvi, si superem la quantitat requerida pel barco, el numero retornat es lo que ens falta per arribar a lo requerit pel barco.  
    */
    int consultar_diferencia_prod_venta(int p, pair<int,int>& anterior_cv, Barco &b) const;  


/**
    @brief  Modificadora de Ciutat:Modifico les quantitats que tinc d'un cert producte.    
    \pre Cert.
    \post Modifiquem les quantitats que tenim del producte que ens ha comprat el barco, y modifiquem les quantitats que tenim del 
    producte que hem venut. També modifiquem el pes total y el volum total de la ciutat. 
    */
    void modifica_prod_ruta(int producto_suma, int nueva_cantidad_suma, int producto_venta, int nueva_cantidad_venta, const Cjt_productos &cp); 

//LECTURA Y ESCRITURA
    /**
     @brief Operació de escriptura per terminal:Escriu l'inventari d'una ciutat
     \pre La ciutat existeix. 
     \post Pel canal estàndard de sortida s'escriu el numero de productes que tenim i necesitem de cada element 
     de l'inventari de la ciutat del parametre implícit. 
    */
    void escribir_ciudad() const; 

    /**
     @brief Operació de lectura per terminal:Modifica la ciutat, possant els vlors que entren per terminal en els seus atributs. 
     \pre La ciutat existeix. 
     \post Hem llegit el nou inventari de la ciutat, i hem actualitzat el pes i el volum d'aquesta. 
    */
    void leer_ciudad( const Cjt_productos&cp);   
};
#endif
