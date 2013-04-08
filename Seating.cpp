#include <assert.h>

#include <vector>

using namespace std;

const int max_size = 6;

class CustomerGroup {
public:
  const int size; //number of people in the group
};

class Table {
public:
  const int size; //number of chairs around this table

  Table(int newSize) : size(newSize), empty(0) {
  }
  int occupied() {
    return size-empty;
  }
  int available() {
    return empty;
  }
  bool hasGroup(const CustomerGroup *group) {
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
    assert(size >= group->size);
    empty -= group->size;
    groups.push_back(group);
  }
  void unseat(CustomerGroup *group) {
    empty += group->size;
    int j = -1;
    for(int i = 0; i != groups.size(); ++i)  {
      if (groups[i] == group)
	{
	  j = i;
	  break;
	}
    }

    if (j > 0)
      {
	groups.erase(groups.begin() + j);
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
  for(int i = 0; i != tables.size(); ++i)  {
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
    }
  else
    {
      dequeue(group);
    }
}

Table *SeatingManager::locate(CustomerGroup *group) {
  Table *theirTable = NULL;

  for (int i = 0; i <= max_size; ++i)
    {
      for (int j = 0; j < empty[i].size(); ++j)
	{
	  if (empty[i][j]->size < group->size)
	    continue;

	  if (empty[i][j]->hasGroup(group))
	    {
	      theirTable = empty[i][j];
	      break;
	    }
	}
    }
  
  return theirTable;
}

Table *SeatingManager::findEmpty(int size) {
  if (empty[size].size() == 0)
    return NULL;

  return empty[size][0];
}

void SeatingManager::seat(Table *emptyTable, CustomerGroup *group) {
  dequeue(group);
  int index = emptyTable->available();
  empty[index].erase(empty[index].begin());
  emptyTable->seat(group);
  empty[emptyTable->available()].push_back(emptyTable);
}

void SeatingManager::unseat(Table *theirTable, CustomerGroup *group) {
  int index = theirTable->available();
  empty[index].erase(empty[index].begin());
  theirTable->unseat(group);
  empty[theirTable->available()].push_back(theirTable);
}

void SeatingManager::dequeue(CustomerGroup *group) {
  int j = -1;
  for(int i = 0; i != waiting.size(); ++i)  {
    if (waiting[i] == group)
      {
	j = i;
	break;
      }
  }

  if (j > 0)
    {
      waiting.erase(waiting.begin() + j);
    }
}
