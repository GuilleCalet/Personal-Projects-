/** @file Cjt_productos.hh
    @brief Especificació de la classe Cjt_productos.hh 
*/
#ifndef CJT_PRODUCTOS_HH
#define CJT_PRODUCTOS_HH
#ifndef NO_DIAGRAM
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<list>
#endif
using namespace std; 
/** @class Cjt_productos
    @brief Classe Cjt_productos: Representa un conjunt de productes que conté la informació del identificador el pes i el volum de cada 
    producte. 
*/
class Cjt_productos
{
private:
/** @brief Cada producte,en te dos atributs principals, que es el seu pes i el veu volum. 
 */
struct producto
{
   int peso; 
   int volumen; 
};

    /** @brief Els productes de la nostre conca, es guarden en un vector de productes, on produtes es un strcut que te com a atributs dos ints
     * que ens indiquen un pes i un volum. La propia posició dins d'aquest vector serveix per identificar els productes. */
    vector<producto>estanteria; 
public:
    //CONSTRUCTORES

    /**
        @brief Constructora per defecte.    
        \pre Cert.
        \post Crea un conjunt de productes buit.
    */
    Cjt_productos();
    //DESTRUCTORES

    /**
        @brief Destructora per defecte.    
        \pre Cert.
        \post Destrueix un conjunt de productes buit.
    */
    ~Cjt_productos();

    //MODIFICADORES 
    /**
        @brief Modificadora de Cjt_productos: Afegeix un producte a la estanteria.    
        \pre Cert.
        \post Afegeix un numero determinat que llegirem pel canal estàndard d'entrada de productes al vector estanteria. També s'escriu pel canal estandard de sortida el numero de productes nous. 
    */
    void anadir_prod (); 

    //CONSULTORES
    /**
        @brief Consultora de Cjt_productos : Retorna la mida del paràmetre implícit.    
        \pre Cert.
        \post Retorna el número de productes amb id diferent de la nostre conca. 
    */ 
    int num_prod() const; 
    /**
     @brief Consultora de Cjt_productos : Em diu si existeix o no el porducte p en la meva estanteria 
     \pre Cert. 
     \post Si el producte amb identificador p esta al vector, retornem true. False en cas contrari.  
    */
    bool existe_producto(int p) const; 

    //LECTURA Y ESCRIPTURA
    /**
        @brief Operació de lectura per terminal : LLegim productes i els fiquem dins de la nostre estanteria . 
        \pre El paràmetre implícit està buit.
        \post El paràmetre implícit està format per "n" productes, on cada producte te un pes i un volum, i un id que es veu reperesentat pr la 
        seva posicio al vector.
    */
    void leer_cjto_productos();

    /**
        @brief Operació d'escriptura per terminal : S'escriu per pantalla els atributs del producte p de la estanteria.    
        \pre Cert.
        \post Si el prodcucte p existeix, es mostra pel canal estandard de sortida l'identificador del producte, el pes i el volum . Altrament, es mostra pel canal estàndard de sortida un missatge d'error.
    */
    void escribir_producto(int p) const; 
    /**
        @brief Consultora de Cjt_productos : Retorna el pes del producte p .    
        \pre El producte existeix.
        \post Retorna el pes del prodcute p.
    */
    int consultar_peso(int p) const; 
    /**
        @brief Consultora de Cjt_productos : Retorna el volum del producte p .    
        \pre El producte existeix.
        \post Retorna el volum del producte p. 
    */
    int consultar_volumen(int p) const; 
};
#endif
