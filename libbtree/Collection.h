//
// Created by Wolfgang on 26.03.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
#define LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
#include <functional>

struct ProfilingResults {
  int comparisons;
  int fileAccess;

  ProfilingResults* copy() {
    auto* res = new ProfilingResults();
    res->comparisons = this->comparisons;
    res->fileAccess = this->fileAccess;
    return res;
  }
};

template<class T>
class Collection {

private:
    ProfilingResults* profile = nullptr;
protected:
    const std::function<int(T)> valueToKeyConverter;
public:
    Collection(std::function<int(T)> keyConverter):valueToKeyConverter(keyConverter){}
  virtual bool insert(const T* t)= 0;
  virtual const T* search(int key)= 0;
  virtual T* remove(int key)= 0;

  int startProfiling() {
    return 0;
  }

  int stopProfiling() {
    return 0;
  }

  void profileInsertCompare() {

  }

  ProfilingResults* profileResults() const {
    return profile->copy();
  }
};

#endif //LEISTUNGSNACHWEIS_B_TEAM_COLLECTION_H
