#include "sql/stmt/drop_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using namespace std;
using namespace common;

RC DropIndexStmt::create(Db *db, const DropIndexSqlNode &create_index, Stmt *&stmt)
{
  stmt = nullptr;

  const char *table_name = create_index.relation_name.c_str();
  if (is_blank(table_name) || is_blank(create_index.index_name.c_str()) ||
      is_blank(create_index.relation_name.c_str())) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index name=%s, relation name=%s",
        db, table_name, create_index.index_name.c_str(), create_index.relation_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  Index *index = table->find_index(create_index.index_name.c_str());
  if (nullptr == index) {
    LOG_WARN("index with name(%s) not exists. table name=%s", create_index.index_name.c_str(), table_name);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }

  stmt = new DropIndexStmt(table, create_index.index_name);
  return RC::SUCCESS;
}
