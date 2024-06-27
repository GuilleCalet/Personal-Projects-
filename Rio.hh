/** @file Rio.hh
    @brief Especificació de la classe Rio.hh
*/
#ifndef _RIO_HH_
#define _RIO_HH_
#ifndef NO_DIAGRAM 
#include"BinTree.hh"
#endif
#include"Ciudad.hh"
#include"Cjt_productos.hh"
#include"Barco.hh"

/** @class Rio
    @brief Classe Rio : Respresenta la conca del riu, amb les seves difurcacions i les ciutats d'aquestes. 
*/
class Rio
{
private:
    BinTree<string>fluvial;
    map<string,Ciudad>comunidad; 
    /**
        @brief Operació auxiliar de hacer_viaje: Calcula ruta més eficient, i el numero de comrpes i vendes totals   
        \pre Cert.
        \post Retornem un int de la quantitat de compres + ventes que ha pogut fer el barco en un viatje, a més, també triem la millor 
        ruta teneint en compte els seguents cirteris : una ruta sempre sera millor que una altre si aquesta pot comprar i vendre més productes, en cas d'empat, 
        sera millor la ruta que passi per menys ciutats, i finalment, si això també es empat, sera millor la ruta de l'esquerra.        
    */
    int calcular_ruta(const BinTree<string>&fluvial, list<pair<string,pair<int,int>>> &ruta, Barco& b, pair<int,int> anterior_cv) const; 
    /**
        @brief Operació auxiliar de redistribuir : Aplica recursivament comerciar en el nostre arbre 
        \pre Cert.
        \post Hem comerciat de manera recursiva amb totes les ciutats del riu fluvial, es a dir, comerciem amb la part esquerra, i amb la part dreta per cada node.      
    */
    void redistribuir2(const BinTree<string>&fluvial, const Cjt_productos &cp);
    /**
        @brief Operació auxiliar de hacer_viaje: Modifica les ciutats segun la ruta que hem fet, canviant els valors que les compres i vendes del barco en aquella ciutat
        \pre Cert.
        \post Hem acualitzat cada ciutat de la ruta amb els valors que ha venut al barco, i que aquest li ha comprat. També he recalculat el pes i volum total 
        d'aquestes.  
    */
    void modificar_segun_ruta(list<pair<string,pair<int,int>>> &ruta, map<string,Ciudad>& comunidad, Barco &b, const Cjt_productos &cp);
    /**
        @brief Operació auxiliar de leer_rio  
        \pre Cert.
        \post LLegim un arbre binari en forma de preordre, i cada node que llegim, l'afegim aquest string a la nostre comunitat.
        Els atributs de cada ciutat, encara son buits.    
    */
    void leer_rio_segunda(BinTree<string>&fluvial,map<string,Ciudad>&comunidad);
    
public:
    //CONSTRUCTORAS
    /**
        @brief Constructora per defecte.    
        \pre cert.
        \post Crea un conjunt de ciutats buit.
    */
    Rio();
    //DESTRUCTORAS
    /**
        @brief Destructora per defecte.    
        \pre cert.
        \post Destrueix un conjunt de ciutats buit.
    */
    ~Rio();

    //MODIFICADORAS
    /**
        @brief Treu el producte p de la ciutat s .    
        \pre cert.
        \post Treu el producte p de la ciutat s, i modifica els seus volum i pes total que despres seran escrits pel canal estàndard de sortida. Si no existeix el porducte, o no existeix la ciutat, o la ciutat 
        no tenia aquest producte, es mostrara pel canal estàndard de sortida un missatge d'error. 
    */
    void quitar_prod_de_ciudad(string s,int p, const Cjt_productos &cp);  
    /** 
        @brief Ens diu quants productes té la ciutat 
        \pre Cert.
        \post Retornem la quantitat que te i que necessita la ciutat 's' del el determinat producte p. Si no existeix el producte, o no existeix la ciutat, o el 
        proucte no hi es en la ciutat determinada, es mostrara pel canal estàndard de sortida un misstage d'error.       
    */
    void consulta_prod_de_ciudad ( string s, int p, const Cjt_productos &cp) const;
    /**
        @brief Operació modificadora de Rio:: redistribueix els productes de totes les ciutats del riu, comerciant. 
        \pre Cert.
        \post Hem comerciat per totes les ciutats de el fluvial, desde la desembocadura fins al neixament.        
    */
    void redistribuir(const Cjt_productos &cp);
    /**
        @brief Canvia els atributs de una ciutat, li dona un nou numero de productes que te i un nou numero que necesita de un producte concret anomenat p .  
        \pre Cert.
        \post Hem modificat la quantitat que té i que necessita la ciutat 'ciudad', de un determinat producte 'p' pels valors de nuevo_tiene i nuevo_necesita .
        També recalculem el nos pes i volum total de la ciutat i els escribim pel canal estàndard de sortida.  
        Si no existeix el producte, o no existeix la ciutat, o el 
        proucte no hi es en la ciutat determinada, es mostrara un misstage d'error pel canal estàndard de sortida.             
    */
    void modificar_ciudad(string ciudad, int p, int nuevo_tiene,int nuevo_necesita, const Cjt_productos&cp);
    /**
        @brief Operació modificadora de Rio: Dues ciutats intercanvien productes del mateix tipus en funció dels seus interessos.  
        \pre Cert.
        \post Dues ciutats han comerciat donant-se l'una a l'altre, dels productes que coincideixen del seu inventari, una quantitat determinada, que permetria a aquestes 
        arribar o aproximar-se cada vegada més, al número que necessitaven d'aquest producte.  En cas de que una de les dues ciutat sno existeixi, es mostrara pel canal estàndard de sortida un misstage d'error.  
    */
    void comerciar(string c1, string c2, const Cjt_productos&cp); 

    //CONSULTORAS 
   /**
        @brief Operació consultora de Rio: EM diu si existeix o no una ciutat.    
        \pre cert.
        \post Retorna true existeix la ciutat c en la nostre comunidad, false en cas contrari. 
    */
    bool existe_ciudad(string c) const;
    /**
        @brief Modificadora de Rio: Afegeix un producte a una ciutat c .    
        \pre Cert.
        \post Escric pel canal estàndard de sortida els atributs del barco,com ara els seus id de compra i de venta amb els seus respectius objectius.
        En cas de que la ciutat 'c' no existeixi, o el pdoructe p ja fos a la ciutat, o simplement el producte p no hi es en el nostre conjunt de prodcutes, es 
        mostrara pel canal estàndard de sortida un missatge d'error. 
    */
    void anadir_producto(string c, int p, const Cjt_productos cp);
    /**
        @brief Operació consultora de Rio: Em diu si la ciutat 'c' existeix en el meu riu .    
        \pre Cert.
        \post Retornem true, si la ciutat c conte en el seu inventari el porducte p, flase en cas contari. 
    */
    bool tiene_producto_inventario(string c, int p) const;

    /**
        @brief Modificadora de Rio: El meu barco fa un viatje pel riu, amb l'objectiu de per el seu numero de ventes, i el seu numero de compres.    
        \pre Cert.
        \post El meu barco, fa un viatje, una vegada fet aquest viatje, em retorna pel canal estàndard de sortida la quantitat de productes comprats i ventus que ha pogut fer 
        en la millor ruta que ha trobat en el meu fluvial.
    */
    void hacerviaje(Barco& b, const Cjt_productos&cp);
    /**
        @brief Consultora de ciutat: Busquem una ciutat en el nostre riu i retornem els seus atributs.    
        \pre El string c es l'identificador de una ciutat que existeix en el map.
        \post Retorna la ciutat entera amb el nom de l'string 'c'. Amb els seu inventari, pes total i  volum total. 
    */
    Ciudad buscar_ciudad(string c) const; 

    //LECTURA Y ESCRITURA
    /**
        @brief Operació de lectura per terminal: Llegim els atributs de la ciutat.    
        \pre Pel canal estandard d'entrada llegim el nom de una ciutat.
        \post L'inventari de la ciutat 'ciudad' ha estat modificat, aixi com els seu pes total i el seu volum total.En cas de que la ciutat no existeixi, 
        es mostrara pel canal estàndard de sortida un missatge d'error. 
    */
    
    void leer_ciudad(string ciudad, const Cjt_productos&cp); 
    /**
        @brief Operació de lectura per terminal: LLegim els atributs de varies ciutats .    
        \pre Pel canal estandard d'entrada llegim noms de ciutats, i per cada ciutat un nombre n de productes. Anirem llegint ciutats fins a trobar un '#'.
        \post L'inventari de les ciutats llegides ha estat modificat amb els seus respetius productes. Si no existeix la ciutat, es mostrara un missatge d'error. 
    */
    void leer_inventario(const Cjt_productos&cp); 
    /**
        @brief Operació d'escriptura: Escribim pel canal estandard de sortida els atributs de la ciutat.    
        \pre cert.
        \post Si la ciutat existeix, es mostra perl canal de sortida estàndard l'inventari de la ciutat, també el seu pes total y volum total, que s'escriuen per terminal. 
        Altrament, s'escriu pel canal estàndard de sprtida un missatge d'error. 
        
    */
    void escribir_ciudad(string ciudad) const; 
    /**
        @brief Operació de lectura per terminal: LLegim un riu.    
        \pre Pel canal estandard d'entrada llegim un arbre binari d'string en forma de preordre.
        \post Buidem l'anterior comunitat, i omplim la nostre nova comunitat amb les noves ciutats del arbre binari previament llegit.
    */
    void leer_rio();
};
#endif
