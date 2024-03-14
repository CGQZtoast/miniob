#pragma once

#include <string>

#include "sql/stmt/stmt.h"

struct DropIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 删除索引的语句
 * @ingroup Statement
 */
class DropIndexStmt : public Stmt
{
public:
  DropIndexStmt(Table *table, const std::string &index_name)
      : table_(table), index_name_(index_name)
  {}

  virtual ~DropIndexStmt() = default;

  StmtType type() const override { return StmtType::DROP_INDEX; }

  Table             *table() const { return table_; }
  const FieldMeta   *field_meta() const { return field_meta_; }
  const std::string &index_name() const { return index_name_; }

public:
  static RC create(Db *db, const DropIndexSqlNode &drop_index, Stmt *&stmt);

private:
  Table           *table_      = nullptr;
  const FieldMeta *field_meta_ = nullptr;
  std::string      index_name_;
};