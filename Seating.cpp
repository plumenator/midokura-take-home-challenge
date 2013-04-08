#include <vector>

using namespace std;

class Table {
public:
  const int size; //number of chairs around this table
};

class CustomerGroup {
public:
  const int size; //number of people in the group
};

class SeatingManager {
public:
  /* Constructor */
  SeatingManager(vector<Table *> tables);
  /* Group arrives and wants to be seated. */
  void arrives(CustomerGroup *group);
  /* Whether seated or not, the group leaves the restaurant. */
  void leaves(CustomerGroup *group);
  /* Return the table at which the group is seated, or null if
     they are not seated (whether they're waiting or already left). */
  Table *locate(CustomerGroup *group); 
};

