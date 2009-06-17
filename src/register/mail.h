#ifndef MAIL_H_
#define MAIL_H_

#include "common_object.h"
#include "object.h"
#include "db/dbs.h"
#include "model/model_filters.h"

namespace Register {
namespace Mail {

enum MemberType {
  MT_CRDATE,
  MT_TYPE,
  MT_STATUS
};


class Mail : virtual public Register::CommonObject {
public:
  virtual const DBase::DateTime& getCreateTime() const = 0;
  virtual const DBase::DateTime& getModTime() const = 0;
  virtual const long getType() const = 0;
  virtual const std::string& getTypeDesc() const = 0;
  virtual const long getStatus() const = 0;
  virtual const std::string& getContent() const = 0;
  
  virtual void addHandle(const std::string& _handle) = 0;
  virtual unsigned getHandleSize() const = 0;
  virtual const std::string& getHandle(unsigned _idx) const = 0;
  
  virtual void addAttachment(const DBase::ID& _id) = 0;
  virtual unsigned getAttachmentSize() const = 0;
  virtual const DBase::ID& getAttachment(unsigned _idx) const = 0;
};


class List : virtual public Register::CommonList {
public:
  virtual Mail* get(unsigned _idx) const = 0;
  virtual void reload(DBase::Filters::Union& _filter) = 0;
  virtual void sort(MemberType _member, bool _asc) = 0;
  
  /// from CommonList; propably will be removed in future
  virtual const char* getTempTableName() const = 0;
  virtual void makeQuery(bool, bool, std::stringstream&) const = 0;
  virtual void reload() = 0;
};


class Manager {
public:
  virtual ~Manager() {
  }
  
  virtual List* createList() const = 0;
  static Manager* create(DBase::Manager *_db_manager);
};

}
}

#endif /*MAIL_H_*/
