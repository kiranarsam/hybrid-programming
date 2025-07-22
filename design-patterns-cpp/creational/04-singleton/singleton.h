#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class Database
{
public:
  virtual int getPopulation(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
  SingletonDatabase()
  {
    std::cout << "Initializing database" << std::endl;

    std::ifstream ifs("capitals.txt");

    if(ifs.is_open()) {
      std::string s, s2;
      while (getline(ifs, s)) {
        getline(ifs, s2);
        int pop = 0;
        try {
          pop = std::stoi(s2);
        }
        catch(...) {
          pop = -1;
        }

        capitals[s] = pop;
      }

      ifs.close();
    }
    else {
      std::cout << "File not found\n";
    }


    instance_count++;
  }

  std::map<std::string, int> capitals;

public:
  static int instance_count;

  // delete copy const and assign operator func
  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  // get instance only once
  static SingletonDatabase& get()
  {
    static SingletonDatabase db;
    return db;
  }

  int getPopulation(const std::string& name) override
  {
    return capitals[name];
  }

  /*
  static SingletonDatabase* get_instance()
  {
    if (!instance)
      instance = new SingletonDatabase;
    return instance; // atexit
  }
  */
};

int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database
{
  std::map<std::string, int> capitals;
public:
  DummyDatabase() {
    capitals["alpha"] = 1;
    capitals["beta"] = 2;
    capitals["gamma"] = 3;
  }

  int getPopulation(const std::string& name) override {
    return capitals[name];
  }
};

class SingletonRecordFinder
{
public:
  int totalPopulation(std::vector<std::string> names)
  {
    int result = 0;
    for (auto& name : names)
      result += SingletonDatabase::get().getPopulation(name);
    return result;
  }
};

class ConfigurableRecordFinder
{
public:
  explicit ConfigurableRecordFinder(Database& db)
    : db{db}
  {
  }

  int totalPopulation(std::vector<std::string> names) const
  {
    int result = 0;
    for (auto& name : names)
      result += db.getPopulation(name);
    return result;
  }

  Database& db;
};