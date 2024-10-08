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
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include <sstream>
#include <cstdio>

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "floats","dates", "booleans"};

const char *attr_type_to_string(AttrType type) {
  if (type >= AttrType::UNDEFINED && type <= AttrType::BOOLEANS) {
    return ATTR_TYPE_NAME[static_cast<int>(type)];
  }
  return "unknown";
}
const char * attr_types_to_string(const std::vector<AttrType>& types) {
  stringstream ss;
  for (size_t i = 0; i < types.size(); i++)
    ss << attr_type_to_string(types[i]);
  return ss.str().c_str();
}
AttrType attr_type_from_string(const char *s) {
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return AttrType::UNDEFINED;
}
RC date_str_to_int(const std::string& val, int& date_int_val) {
  try {
    // auto val = values[i].get_string();
    int day,month,year;
    day = month = year = -1;
    int ret = sscanf(val.c_str(), "%d-%d-%d",&year,&month,&day);
    
    if ((ret != 3) || (year < 0) || (month < 1) || (month > 12) || (day < 1) || (day > 31)) {
      return RC::INTERNAL;
    }
    bool is_leap_year = year % 100 == 0 ? (year % 400 == 0) : (year % 4 == 0);
    switch (month)
    {
    case 4:
    case 6:
    case 9:
    case 11:
      if (day > 30) {
        return RC::INTERNAL;
      }
      break;
    case 2:
      if ((is_leap_year && day > 29) || (!is_leap_year && day > 28)) {
        return RC::INTERNAL;
      }
    default:
      break;
    }
    int time_val = ((year & 0xffff) << 16) | ((month & 0xff) << 8) | (day & 0xff); 
    date_int_val = time_val;
  } catch(std::exception& e) {
    return RC::INTERNAL;
  }
  return RC::SUCCESS;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      set_string(data, length);
    } break;
    case AttrType::INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
     case AttrType::DATES: {
      num_value_.int_value_ = *(int*)data;
      length_ = length;
    } break;
    case AttrType::FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case AttrType::BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val) {
  attr_type_            = AttrType::INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_date(int val) {
  attr_type_ = AttrType::DATES;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val) {
  attr_type_              = AttrType::FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_boolean(bool val) {
  attr_type_             = AttrType::BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}
void Value::set_null() {
  attr_type_ = AttrType::NULLS; 
}
void Value::set_string(const char *s, int len /*= 0*/) {
  attr_type_ = AttrType::CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_value(const Value &value) {
  switch (value.attr_type_) {
    case AttrType::INTS: {
      set_int(value.get_int());
    } break;
    case AttrType::FLOATS: {
      set_float(value.get_float());
    } break;
    case AttrType::CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case AttrType::BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case AttrType::UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
    default:
      break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case AttrType::INTS: {
      os << num_value_.int_value_;
    } break;
    case AttrType::FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case AttrType::BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case AttrType::DATES: {
      os << get_date();
    } break;
    case AttrType::CHARS: {
      os << str_value_;
    } break;
    case AttrType::NULLS: {
      os << "null";
    }break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case AttrType::INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case AttrType::FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case AttrType::CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case AttrType::BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      case AttrType::DATES:{
        return common::compare_int((void *)&num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == AttrType::INTS && other.attr_type_ == AttrType::FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == AttrType::FLOATS && other.attr_type_ == AttrType::INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type() == AttrType::CHARS) {
    if (other.attr_type() == AttrType::FLOATS) {
      auto f1 = get_float();
      auto f2 = other.get_float();
      return common::compare_float(&f1, &f2);
    } else if (other.attr_type() == AttrType::INTS) {
      int left = get_int();
      int right = other.get_int();
      return common::compare_int(&left, &right);
    }
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case AttrType::INTS: {
      return num_value_.int_value_;
    }
    case AttrType::FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case AttrType::BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case AttrType::INTS: {
      return float(num_value_.int_value_);
    } break;
    case AttrType::FLOATS: {
      return num_value_.float_value_;
    } break;
    case AttrType::BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case AttrType::CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case AttrType::INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case AttrType::FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case AttrType::BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

std::string Value::get_date() const {
  std::stringstream ss;
  int val = num_value_.int_value_;
  ss << std::to_string((val >> 16) & 0xffff) << "-";
  int month = (val >> 8) & 0xff;
  if (month < 10)
    ss << "0";
  ss << month << "-";
  int day = (val & 0xff);
  if (day < 10)
    ss << "0";
  ss << day;
  return ss.str();
}
