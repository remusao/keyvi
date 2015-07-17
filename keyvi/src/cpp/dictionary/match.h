/* * keyvi - A key value store.
 *
 * Copyright 2015 Hendrik Muhs<hendrik.muhs@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * match.h
 *
 *  Created on: Jun 4, 2014
 *      Author: hendrik
 */

#ifndef MATCH_H_
#define MATCH_H_

#include <boost/container/flat_map.hpp>
#include <boost/variant.hpp>

#include "dictionary/fsa/automata.h"

//#define ENABLE_TRACING
#include "dictionary/util/trace.h"

namespace keyvi {
namespace dictionary {

#ifdef Py_PYTHON_H
class attributes_visitor : public boost::static_visitor<PyObject*>
{
public:
  PyObject* operator()(int i) const
    {
        return PyInt_FromLong(i);
    }

  PyObject* operator()(double i) const
    {
        return  PyFloat_FromDouble(i);
    }

  PyObject* operator()(bool i) const
    {
        return i ? Py_True : Py_False;
    }

  PyObject* operator()(const std::string & str) const
    {
        return PyString_FromString(str.c_str());
    }
};
#endif

struct Match {
  typedef std::shared_ptr<boost::container::flat_map<std::string, boost::variant<std::string, int, double, bool>>> attributes_t;

  Match(size_t a, size_t b, const std::string& matched_item, uint32_t score = 0)
      : start_(a),
        end_(b),
        matched_item_(matched_item),
        score_(score)
  {
    TRACE("initialized Match %d->%d %s", a, b, matched_item.c_str());
  }

  Match(size_t a, size_t b, const std::string& matched_item, uint32_t score,
        const fsa::automata_t& fsa, uint64_t state)
      : start_(a),
        end_(b),
        matched_item_(matched_item),
        score_(score),
        fsa_(fsa),
        state_(state)
  {
    TRACE("initialized Match %d->%d %s", a, b, matched_item.c_str());
  }

  Match()
  {
  }

  // todo: consider disallowing copy and assignment
  //Match& operator=(Match const&) = delete;
  //Match(const Match& that) = delete;

  size_t GetEnd() const {
    return end_;
  }

  void SetEnd(size_t end = 0) {
    end_ = end;
  }

  const std::string& GetMatchedString() const {
    return matched_item_;
  }

  void SetMatchedString(const std::string& matched_item) {
    matched_item_ = matched_item;
  }

  double GetScore() const {
    return score_;
  }

  void SetScore(double score = 0) {
    score_ = score;
  }

  size_t GetStart() const {
    return start_;
  }

  void SetStart(size_t start = 0) {
    start_ = start;
  }

  bool IsEmpty() const {
    return start_ == 0 && end_ == 0;
  }

#ifdef Py_PYTHON_H
  PyObject* GetAttributePy (const std::string& key) {
      auto result = GetAttribute(key);
      return boost::apply_visitor( attributes_visitor(), result );
  }
#endif

  const boost::variant<std::string, int, double, bool>& GetAttribute(const std::string& key) {
    // lazy creation
    if (!attributes_){
      if (fsa_){
        attributes_ = fsa_->GetValueAsAttributeVector(state_);
      } else {
        attributes_ = attributes_t(new fsa::internal::IValueStoreReader::attributes_raw_t);
      }
    }

    return attributes_->at(key);
  }

  template<typename U>
  void SetAttribute(const std::string& key, U value) {
    if (!attributes_){
      if (fsa_){
        attributes_ = fsa_->GetValueAsAttributeVector(state_);
      } else {
        attributes_ = attributes_t(new fsa::internal::IValueStoreReader::attributes_raw_t);
      }
    }

    (*attributes_)[key] = value;
  }

  std::string GetValueAsString() const {

    if (!fsa_){
        return "";
    }

    return fsa_->GetValueAsString(state_);
  }

  std::string GetRawValueAsString() const {

    if (!fsa_){
        return "";
    }

    return fsa_->GetRawValueAsString(state_);
  }

 private:
  size_t start_ = 0;
  size_t end_ = 0;
  std::string matched_item_;
  double score_ = 0;
  fsa::automata_t fsa_ = 0;
  uint64_t state_ = 0;
  attributes_t attributes_ = 0;
};

} /* namespace dictionary */
} /* namespace keyvi */

#endif /* MATCH_H_ */
