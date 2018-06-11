//
// Created by Wolfgang on 26.03.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
#define LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
#include <functional>

struct ProfilingResults {
  int searchComparisons = 0;
  int searchFileAccess = 0;
  int insertComparisons = 0;
  int insertFileAccess = 0;
  int removeComparisons = 0;
  int removeFileAccess = 0;

  void add(ProfilingResults* other) {
      this->searchComparisons += other->searchComparisons;
      this->searchFileAccess += other->searchFileAccess;
      this->insertComparisons += other->insertComparisons;
      this->insertFileAccess += other->insertFileAccess;
      this->removeComparisons += other->removeComparisons;
      this->removeFileAccess += other->removeFileAccess;
  }
};

/// Template Klasse für alle Listen die verglichen werden sollen.
/** Diese Klasse enthält die Methodenvorgaben und Mechanismen für die Vergleichsmessung.
 * Dazu kann beim Einfügen, Suchen und Entfernen die Anzahl der Vergleichsoperationen und Dateizugriff erfasst werden. */
template<class T>
class Collection {

protected:
    /**
     * Lambdaausdruck der aus dem Objekt einen int-Key generiert.
     */
    const std::function<int(T)> valueToKeyConverter;
public:
    /**
     * C.
     * @param keyConverter = Funktion die aus der Value den Key berechnet.
     */
    Collection(std::function<int(T)> keyConverter):valueToKeyConverter(keyConverter){}
    /**
     * Einfügen ohne Messung.
     * @param t Pointer auf das Objekt das eingefügt werden soll.
     * @return true.
     */
  virtual bool insert(const T* t)= 0;
  /**
   * Einfügen mit Messung.
   * @param t Pointer auf das Objekt das eingefügt werden soll.
   * @param p Profile in das die Messergebnisse geschrieben werden
   * @return true.
   */
  virtual bool insert(const T* t, ProfilingResults* p)= 0;
  virtual const T* search(int key)= 0;
  virtual const T* search(int key, ProfilingResults* p)= 0;
  virtual bool remove(int key)= 0;
  virtual bool remove(int key, ProfilingResults* p)= 0;
};

#endif //LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
