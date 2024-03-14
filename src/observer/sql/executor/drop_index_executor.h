#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 删除索引的执行器
 * @ingroup Executor
 * @note 
 */
class DropIndexExecutor
{
public:
  DropIndexExecutor()          = default;
  virtual ~DropIndexExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};