// Time complexity
// ---------------
// arrives():  less than or equal to max_size
// leaves():   O(n)
// locate():   constant time, groups have a reference to the table

#include <assert.h>
#include <vector>

using namespace std;

const int max_size = 6;

class Table;

class CustomerGroup {
public:
  const int size; //number of people in the group
  Table *table;
  CustomerGroup (int newSize) : size(newSize), table(NULL) {
  }
  ~CustomerGroup () {
  }
};

class Table {
public:
  const int size; //number of chairs around this table

  Table(int newSize) : size(newSize), empty(size) {
  }
  ~Table() {
  }
  int available() {
    return empty;
  }
  bool hasGroup(const CustomerGroup *group) {
    if (size - empty < group->size)
      return false;
    
    for (int i = 0; i < groups.size(); ++i)
      {
	if (group == groups[i])
	  {
	    return true;
	  }
      }
    
    return false;
  }
  void seat(CustomerGroup *group) {
    assert(empty <= group->size);
    
    empty -= group->size;
    groups.push_back(group);
    group->table = this;
  }
  void unseat(CustomerGroup *group) {
    assert(size >= empty + group->size);
    
    empty += group->size;
    for(int i = 0; i < groups.size(); ++i)  {
      if (groups[i] == group)
	{
	  groups.erase(groups.begin() + i);
	  group->table = NULL;
	}
    }
  }
  
private:
  int empty;
  vector<CustomerGroup *> groups;
};

class SeatingManager {
public:
  /* Constructor */
  SeatingManager(vector<Table *> tables);
  /* Destructor */
  ~SeatingManager();
  /* Group arrives and wants to be seated. */
  void arrives(CustomerGroup *group);
  /* Whether seated or not, the group leaves the restaurant. */
  void leaves(CustomerGroup *group);
  /* Return the table at which the group is seated, or null if
     they are not seated (whether they're waiting or already left). */
  Table *locate(CustomerGroup *group);

private:
  vector<CustomerGroup *> waiting;
  vector<Table *> empty[max_size+1];

  Table *findEmpty(int size);
  void seat(Table *emptyTable, CustomerGroup *group);
  void unseat(Table *theirTable, CustomerGroup *group);
  void dequeue(CustomerGroup *group);
};

SeatingManager::SeatingManager(vector<Table *> tables) {
  for(int i = 0; i < tables.size(); ++i)  {
    empty[tables[i]->size].push_back(tables[i]);
  }
}

SeatingManager::~SeatingManager() {
}

void SeatingManager::arrives(CustomerGroup *group) {
  Table *emptyTable = findEmpty(group->size);
  if (emptyTable)
    {
      seat(emptyTable, group);
    }
  else
    {
      waiting.push_back(group);
    }
}

void SeatingManager::leaves(CustomerGroup *group) {
  Table *theirTable = locate(group);
  if (theirTable)
    {
      unseat(theirTable, group);
      
      for (int i = 0; i < waiting.size(); ++i)
	{
	  if (waiting[i]->size <= theirTable->available())
	    {
	      waiting.erase(waiting.begin() + i);
	      seat(theirTable, waiting[i]);
	      break;
	    }
	}
    }
  else
    {
      dequeue(group);
    }
}

Table *SeatingManager::locate(CustomerGroup *group) {
  return group->table;
}

Table *SeatingManager::findEmpty(int size) {
  for (int i = size; i <= max_size; ++i)
    {
      if (empty[i].size() > 0)
	return empty[size][0];
    }
  
  return NULL;
}

void SeatingManager::seat(Table *emptyTable, CustomerGroup *group) {
  int index = emptyTable->available();
  assert (empty[index][0] == emptyTable);
  empty[index].erase(empty[index].begin());
  emptyTable->seat(group);
  empty[emptyTable->available()].push_back(emptyTable);
}

void SeatingManager::unseat(Table *theirTable, CustomerGroup *group) {
  int index = theirTable->available();
  for (int i = 0; i < empty[index].size(); ++i)
    {
      if (empty[index][i] == theirTable)
	{
	  empty[index].erase(empty[index].begin() + i);
	  break;
	}
    }
  theirTable->unseat(group);
  empty[theirTable->available()].push_back(theirTable);
}

void SeatingManager::dequeue(CustomerGroup *group) {
  for (int i = 0; i < waiting.size(); ++i)  {
    if (waiting[i] == group)
      {
	waiting.erase(waiting.begin() + i);
	return;
      }
  }
}
