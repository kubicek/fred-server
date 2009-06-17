#ifndef EPP_SESSION_FILTER_H_
#define EPP_SESSION_FILTER_H_

#include "db/base_filters.h"
#include "registrar_filter.h"

namespace DBase {
namespace Filters {

class EppSession : virtual public Compound {
public:
  virtual ~EppSession() {
  }

  virtual Table& joinLoginTable() = 0;
  virtual Registrar& addRegistrar() = 0;
  virtual Interval<DBase::DateInterval>& addLogin() = 0;
};

class EppSessionImpl : virtual public EppSession {
public:
  EppSessionImpl();
  virtual ~EppSessionImpl();

  virtual Table& joinLoginTable();
  virtual Registrar& addRegistrar();
  virtual Interval<DBase::DateInterval>& addLogin();
};

}
}

#endif /*EPP_SESSION_FILTER_H_*/