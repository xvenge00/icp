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
    uint32_t block_id_gen;
    uint32_t conn_id_gen;

    void loadBlck(Block *blck);

    void loadConn(Connection *conn);

  public:
    Schema();

    ~Schema();

    void save(const string &file_name);

    void load(const string &file_name);

    /* Returns ID of the new block */
    uint32_t newAddBlock(uint8_t in_size = DEFAULT_ADD_INPUT_SIZE, int pos_x = 1, int pos_y = 1);

    uint32_t newMulBlock(uint8_t in_size = DEFAULT_MUL_INPUT_SIZE, int pos_x = 1, int pos_y = 1);

    uint32_t newSubBlock(int pos_x = 1, int pos_y = 1);

//    uint32_t newDivBlock(int pos_x = 1, int pos_y = 1);   //TODO

    uint32_t newOutBlock(double output, int pos_x = 1, int pos_y = 1);

    uint32_t newConnection(Block *in, Block *out, uint8_t pos);

    Block *getBlckByID(uint32_t ID);

    Connection *getConByID(uint32_t ID);

    bool compute();

    friend ostream &operator<<(ostream &s, const Schema &schema);

    friend std::istream &operator>>(std::ifstream &s, Schema &b);
};

#endif // ICP_SCHEMA_H
