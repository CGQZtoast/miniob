#include "sql/executor/drop_index_executor.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/drop_index_stmt.h"
#include "storage/table/table.h"

RC DropIndexExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_INDEX,
      "drop index executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  DropIndexStmt *drop_index_stmt = static_cast<DropIndexStmt *>(stmt);

  Trx   *trx   = session->current_trx();
  Table *table = drop_index_stmt->table();
  return table->drop_index(trx, drop_index_stmt->index_name().c_str());
}