/* Squelette pour classe générique Tableau<T>.
 * Lab3 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab3/
 */

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>

template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    bool           vide();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void           enlever(int index=0);
    void           enlever_dernier();
    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element);
    bool           contient(const T& elements);
    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

    void           trier();
    Tableau<T>&    operator += (const Tableau<T>& autre);
    Tableau<T>     operator + (const Tableau<T>& autre) const;

  private:
    void redimensionner(int a);
    T*             elements;
    int            nbElements;
    int            capacite;
};


// ---------- Définitions -------------


template <class T>
Tableau<T>::Tableau(int capacite_){

    elements = new T[capacite_];
    nbElements = 0;
    capacite = capacite_;
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre){

    nbElements = autre.nbElements;
    capacite = autre.capacite;
    elements = new T[capacite];
    for(int i=0;i<nbElements;i++)
    elements[i] = autre.elements[i];
}

template <class T>
Tableau<T>::~Tableau(){

    delete[] elements;
    elements = nullptr;
}

template <class T>
int Tableau<T>::taille() const{

    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item){

   assert ( nbElements <= capacite);
   if(nbElements == capacite)
       redimensionner(capacite*2);
       elements[nbElements++] = item;
}
template <class T> void Tableau<T>::redimensionner(int nouvCapacite){

    capacite = nouvCapacite;
    T*temp = new T[capacite];
    for(int i=0;i<nbElements;i++)
    temp[i] = elements[i];
    delete [] elements;
    elements = temp;
}

template <class T>
void Tableau<T>::inserer ( const T& element, int index ) {

    if ( index < nbElements ) {
        //decaler
        T temp;
        for ( int i = nbElements - 1; i >= index; i-- ) {
            temp = elements[i];
            elements[i+1] = temp;
        }
    } else {
        if ( index >=  capacite ){
           //grandir
          int i = index / capacite;
          if( i == 1 )
              i = 2;
             redimensionner( capacite * i );
        }
    }
        elements[index] = element;
        nbElements ++;
}

template <class T>
void Tableau<T>::enlever(int index){

T temp;

    if ( index < capacite ){
       if ( index < nbElements ){
          for ( int i = index + 1; i < nbElements; i++){
              temp = elements[i];
              elements[i-1] = temp;
          }
       }
       nbElements--;
    }
}

template <class T>
void Tableau<T>::enlever_dernier(){
nbElements--;
}

template <class T>
int Tableau<T>::chercher(const T& element){

     for(int i = 0; i < nbElements; i++)
          if( elements[i] == element)
             return i;
    return -1;
}

template <class T>
bool Tableau<T>::contient(const T& element){

     for(int i = 0; i < nbElements; i++)
          if( elements[i] == element)
             return true;
    return false;
}

template <class T>
void Tableau<T>::vider(){

   nbElements = 0;
   capacite = 4;
}

template <class T>
bool Tableau<T>::vide(){
return nbElements==0;
}

template <class T>
const T& Tableau<T>::operator[] (int index) const{

    assert(index<nbElements);
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index){

    assert(index<nbElements);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre){

    if(this==&autre) return *this;
    nbElements = autre.nbElements;
    if(capacite<autre.nbElements){
    delete[] elements;
    capacite = autre.nbElements;
    elements = new T[capacite];
}
    for(int i=0;i<nbElements;i++)
       elements[i] = autre.elements[i];
       return *this;
}

template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const{

    if ( this == &autre ) return true;
    if ( nbElements != autre.nbElements ) return false;
    for ( int i=0; i < nbElements; i++ )
        if ( elements[i] != autre.elements[i] )
            return false;
    return true;
}

template <class T>
void Tableau<T>::trier(){

   bool inversion = false ;
   T t;
   do{
     inversion = false;
     for(int i=0;i<nbElements-1;i++){
        if (elements[i]>elements[i+1]){
           t = elements[i];
           elements[i] = elements[i+1];
           elements[i+1] = t;
           inversion = true;
        }
     }
     }while(inversion);
}

template <class T>
Tableau<T>& Tableau<T>::operator += (const Tableau<T>& autre){

   int tmp = autre.nbElements;

   redimensionner(autre.nbElements + nbElements);
   for(int i = 0; i < tmp; i++)
     elements[nbElements++] = autre.elements[i];

   return *this;
}

template <class T>
Tableau<T> Tableau<T>::operator + (const Tableau<T>& autre) const{

    Tableau<T> temp (nbElements + autre.nbElements);
    for(int i=0;i<nbElements;i++)
       temp.elements[temp.nbElements++] = elements[i];
    for(int i=0;i<autre.nbElements;i++)
       temp.elements[temp.nbElements++] = autre.elements[i];

return temp;
}

#endif //define _TABLEAU___H_
