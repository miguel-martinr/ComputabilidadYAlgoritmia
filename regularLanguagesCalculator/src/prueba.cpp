#include <iostream>
#include <set>
#include <string>



using namespace std;
class compare {
public:
  bool operator() (const string& str1, const string& str2) const {
  if (str1.size() < str2.size())
    return true;
  if (str1.size() > str2.size())
    return false;
  if (str1.compare(str2) < 0)
    return true;
  return false;
  }
};
int main(void) {
    
    set<string, compare> mi_set;
    for (int i=0; i<5;i++) {
        string str;
        cin>>str;
        mi_set.insert(str);
    }
    
    set<string, compare>::iterator itr = mi_set.begin();
    for (;itr!=mi_set.end();++itr)
      cout<<*itr<<endl;
    
    return 0;
}