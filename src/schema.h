#ifndef ICP_SCHEMA_H
#define ICP_SCHEMA_H

//#include <vector>
#include <map>

#include "block.h"
#include "connection.h"

using namespace std;

class Schema {
  std::map<int, Block *> blocks;
  std::map<int, Connection *> connections;

  void loadBlck(Block *blck);

  void loadConn(Connection *conn);

public:
  Schema();

  ~Schema();

  void save(const string &file_name);

  void load(const string &file_name);

  uint32_t newBlock(func_type type, int pos_x = 1, int pos_y = 1);

  uint32_t newConnection(Block *in, Block *out);

  Block *getBlckByID(uint32_t ID);

  Connection *getConByID(uint32_t ID);

  friend ostream &operator<<(ostream &s, const Schema &schema);

  friend std::istream &operator>>(std::ifstream &s, Schema &b);
};

#endif // ICP_SCHEMA_H
