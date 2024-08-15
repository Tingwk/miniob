#pragma once 
class SQLStageEvent;
#include "common/rc.h"
class DropTableExecutor {
 public:
  DropTableExecutor() = default;
  virtual ~DropTableExecutor() = default;
  RC execute(SQLStageEvent *sql_event);
 
};