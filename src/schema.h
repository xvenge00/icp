#ifndef ICP_SCHEMA_H
#define ICP_SCHEMA_H

#include <map>

#include "block.h"
#include "connection.h"

using namespace std;

class Schema {
    std::map<int, Block *> blocks;
    std::map<int, Connection *> connections;
    unsigned int block_id_gen;
    unsigned int conn_id_gen;

    void loadBlck(Block *blck);

    void loadConn(Connection *conn);

  public:
    Schema();

    ~Schema();

    void save(const string &file_name);

    void load(const string &file_name);

    /* Returns ID of the new block */
    unsigned int newAddBlock(unsigned int in_size = DEFAULT_ADD_INPUT_SIZE,
                             int pos_x = 1, int pos_y = 1);
    unsigned int newMulBlock(unsigned int in_size = DEFAULT_MUL_INPUT_SIZE,
                             int pos_x = 1, int pos_y = 1);
    unsigned int newSubBlock(int pos_x = 1, int pos_y = 1);
    //    unsigned int newDivBlock(int pos_x = 1, int pos_y = 1);   //TODO
    unsigned int newOutBlock(double output, int pos_x = 1, int pos_y = 1);

    bool deleteBlock(unsigned int ID);

    /* Returns ID of the new connection */
    unsigned int newConnection(Block *in, Block *out, unsigned int pos);
    bool deleteConnection(unsigned int ID);

    Block *getBlckByID(unsigned int ID);

    Connection *getConByID(unsigned int ID);

    /* On success returns true */
    bool compute();

    friend ostream &operator<<(ostream &s, const Schema &schema);

    friend std::istream &operator>>(std::ifstream &s, Schema &b);
};

#endif // ICP_SCHEMA_H
