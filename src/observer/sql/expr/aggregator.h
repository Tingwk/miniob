/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include "sql/parser/value.h"
#include "common/rc.h"

class Aggregator
{
public:
  virtual ~Aggregator() = default;

  virtual RC accumulate(const Value &value) = 0;
  virtual RC evaluate(Value &result)        = 0;
  void set_null() {value_.set_null();}
protected:
  Value value_;
  uint32_t count_{0};
};

class SumAggregator : public Aggregator {
public:
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
};

class CountAggregator : public Aggregator {
public:
  CountAggregator()  {value_.set_int(0);}
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
};

class MinAggregator : public Aggregator {
public:
  MinAggregator(AttrType type);
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
private:
  AttrType type_;
  bool started_;
};

class MaxAggregator : public Aggregator {
public:
  MaxAggregator(AttrType type) : type_(type) {}
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
private:
  AttrType type_;
};

class AvgAggrgator : public Aggregator {
public:
  AvgAggrgator(AttrType type) : type_(type) {
    //ASSERT(type == AttrType::INTS || type == AttrType::FLOATS, "only int & float are valid types");
  }
  RC accumulate(const Value &value) override;
  RC evaluate(Value &result) override;
private:
  AttrType type_;
};