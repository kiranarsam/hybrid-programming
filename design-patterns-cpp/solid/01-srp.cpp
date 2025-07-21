/**
 * Single Responsibility Principle:
 * 	--> A class should only have one reason to change.
 * 	--> Separation of concerns - different classes handling different, independent tasks/problems
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct JournalBooks
{
  std::string title;
  std::vector<std::string> entries;

  explicit JournalBooks(const std::string& title)
    : title{title}
  {
  }

  void add(const std::string& entry);

  // persistence is a separate concern
  void save(const std::string& filename);
};

void JournalBooks::add(const std::string& entry)
{
  static int count = 1;
  entries.push_back(std::to_string(count++) + ": " + entry);
}

void JournalBooks::save(const std::string& filename)
{
  std::ofstream ofs(filename);
  for (auto& entry : entries) {
    ofs << entry << std::endl;
  }
}

// Single Reponsibility Principle: Journal should not take care of saving the journals.
// Journal should have entries (SRP) - Journal component
// Storage should have separate component (SRP) - Persistant component
struct PersistenceManager
{
  static void save(const JournalBooks& j, const std::string& filename)
  {
    std::ofstream ofs(filename);
    for (auto& s : j.entries) {
      ofs << s << std::endl;
    }
  }
};

int main(int argc, char **argv)
{
  // Journal Entries
  JournalBooks journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

//   journal.save("diary.txt");

  // Persistance Storage
  PersistenceManager pm;
  pm.save(journal, "diary.txt");

  return 0;
}