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

#include "sql/expr/aggregator.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
RC SumAggregator::accumulate(const Value &value) {
  if (value.attr_type() == AttrType::NULLS) {
    return RC::SUCCESS;
  }
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
    return RC::SUCCESS;
  }
  
  ASSERT(value.attr_type() == value_.attr_type(), "type mismatch. value type: %s, value_.type: %s", 
        attr_type_to_string(value.attr_type()), attr_type_to_string(value_.attr_type()));
  
  switch (value.attr_type())
  {
    case AttrType::INTS: {
      value_.set_int(value.get_int() + value_.get_int());
    } break;
    case AttrType::FLOATS: {
      value_.set_float(value.get_float() + value_.get_float());
    } break;
    default: {
      return RC::INTERNAL;
    }
  }
  return RC::SUCCESS;
}

RC SumAggregator::evaluate(Value& result)
{
  result = value_;
  return RC::SUCCESS;
}

RC CountAggregator::accumulate(const Value & value) {
  if (value.attr_type() == AttrType::NULLS) {
    return RC::SUCCESS;
  }
  if (value.attr_type() == AttrType::UNDEFINED) {
    value_.set_int(1);
    return RC::SUCCESS;
  }
  value_.set_int(value_.get_int() + 1);
  return RC::SUCCESS;
}

RC CountAggregator::evaluate(Value& result) {
  result = value_;
  return RC::SUCCESS;
}

MinAggregator::MinAggregator(AttrType type) : type_(type), started_(false) {}
RC MinAggregator::accumulate(const Value& value) {
  if (value.attr_type() == AttrType::NULLS) {
    return RC::SUCCESS;
  }
  if (!started_) {
    value_ = value;
    started_ = true;
  } else {
    switch (type_) {
      case AttrType::INTS: {
        if (value.get_int() < value_.get_int()) {
          value_ = value;
        }
      } break;
      case AttrType::DATES: {
        // auto our_date = static_cast<uint32_t>(value_.get_int());
        // auto other_date = static_cast<uint32_t>(value.get_int());
        // if (our_date > other_date) {
        //   value_ = value;
        // }
        if (value.get_uint() < value_.get_uint()) {
          value_ = value;
        }
      } break;
      case AttrType::FLOATS: {
        if (value.get_float() < value_.get_float()) {
          value_ = value;
        }
      } break;
      case AttrType::CHARS: {
        auto str1 = value.get_string();
        auto str2 = value_.get_string();
        if (common::compare_string((void*)(str1.c_str()), str1.size(), (void*)(str2.c_str()), str2.size()) < 0) {
          value_ = value;
        }
      } break;
      default:
        // unsupported type.
        return RC::INVALID_ARGUMENT;
      break;
    }
  }
  return RC::SUCCESS;
}

RC MinAggregator::evaluate(Value &result) {
  result = value_;
  return RC::SUCCESS;
}

RC MaxAggregator::accumulate(const Value& value) {
  if (value.attr_type() == AttrType::NULLS) {
    return RC::SUCCESS;
  }
  if (value_.attr_type() == AttrType::UNDEFINED) {
    value_ = value;
  } else {
    switch (type_) {
      case AttrType::INTS: {
        if (value.get_int() > value_.get_int()) {
          value_ = value;
        }
      } break;
      case AttrType::DATES: {
        // auto our_date = static_cast<uint32_t>(value_.get_int());
        // auto other_date = static_cast<uint32_t>(value.get_int());
        if (value.get_uint() > value_.get_uint()) {
          value_ = value;
        }
      } break;
      case AttrType::FLOATS: {
        if (value.get_float() > value_.get_float()) {
          value_ = value;
        }
      } break;
      case AttrType::CHARS: {
        auto str1 = value.get_string();
        auto str2 = value_.get_string();
        if (common::compare_string((void*)(str1.c_str()), str1.size(), (void*)(str2.c_str()), str2.size()) > 0) {
          value_ = value;
        }
      } break;
      default:
        // unsupported type.
        return RC::INVALID_ARGUMENT;
      break;
    }
  }
  return RC::SUCCESS;
}

RC MaxAggregator::evaluate(Value& result) {
  result = value_;
  return RC::SUCCESS;
}

RC AvgAggrgator::accumulate(const Value& v) {
  if (v.attr_type() == AttrType::NULLS) {
    return RC::SUCCESS;
  }
  if (count_ == 0) {
    value_ = v;
  } else {
    if (type_ == AttrType::INTS) {
      value_.set_int(value_.get_int() + v.get_int());
    } else {
      value_.set_float(value_.get_float() + v.get_float());
    }
  }
  ++count_;
  return RC::SUCCESS;
}

RC AvgAggrgator::evaluate(Value& v) {
  if (count_ == 0) {
    v.set_float(0.0);
  } else {
    if (type_ == AttrType::INTS) {
      v.set_float(value_.get_int() * 1.0 / count_);
    } else {
      v.set_float(value_.get_float() / count_);
    }
  }
  return RC::SUCCESS;
}