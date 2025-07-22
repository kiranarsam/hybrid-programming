#include "singleton.h"


int main(int argc, char **argv)
{
  auto& db = SingletonDatabase::get();
  auto& db2 = SingletonDatabase::get();

  std::cout << &db << " = " << &db2 << "\n";

  SingletonRecordFinder rf;
  std::vector<std::string> names{ "Seoul", "Mexico City" };
  int tp = rf.totalPopulation(names);
  std::cout << "tp = " << tp << "\n";

  DummyDatabase dummydb{};
  ConfigurableRecordFinder crf{ dummydb };
  auto pp = crf.totalPopulation(std::vector<std::string>{"alpha", "gamma"});

  std::cout << "pp = " << pp << "\n";

  std::cout << "Singleton Instances = " << SingletonDatabase::instance_count << "\n";

  return 0;
}
