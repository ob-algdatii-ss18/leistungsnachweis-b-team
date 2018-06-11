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

/// Template Klasse für alle Collections die verglichen werden sollen.
/** Diese Klasse enthält die Methodenvorgaben und Mechanismen für die Vergleichsmessung.
 * Dazu kann beim Einfügen, Suchen und Entfernen die Anzahl der Vergleiche und Dateizugriff erfasst werden. */
template<class T>
class Collection {

protected:
    const std::function<int(T)> valueToKeyConverter;
public:
    Collection(std::function<int(T)> keyConverter):valueToKeyConverter(keyConverter){}
  virtual bool insert(const T* t)= 0;
  virtual bool insert(const T* t, ProfilingResults* p)= 0;
  virtual const T* search(int key)= 0;
  virtual const T* search(int key, ProfilingResults* p)= 0;
  virtual bool remove(int key)= 0;
  virtual bool remove(int key, ProfilingResults* p)= 0;
};

#endif //LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
