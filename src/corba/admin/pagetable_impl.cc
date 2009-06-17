#include <math.h>
#include <memory>
#include <iomanip>
#include <corba/ccReg.hh>

#include "pagetable_impl.h"
#include "log/logger.h"

ccReg_PageTable_i::ccReg_PageTable_i()
  : aPageSize(10), aPage(0), sorted_by_(-1)
{
}

ccReg_PageTable_i::~ccReg_PageTable_i()
{
  //TRACE("[CALL] ccReg_PageTable_i::~ccReg_PageTable_i()");
}

CORBA::Short 
ccReg_PageTable_i::pageSize()
{
  return aPageSize;
}

void 
ccReg_PageTable_i::pageSize(CORBA::Short _v)
{
  aPageSize = _v;
  aPage = 0;
}

CORBA::Short 
ccReg_PageTable_i::page()
{
  return aPage;
}

void 
ccReg_PageTable_i::setPage(CORBA::Short _v) 
  throw (ccReg::PageTable::INVALID_PAGE)
{
  aPage = _v;
}

CORBA::Short 
ccReg_PageTable_i::start()
{
  return aPage*aPageSize;
}

CORBA::Short 
ccReg_PageTable_i::numPages()
{
  return (unsigned)ceil((double)numRows()/aPageSize);
}

ccReg::TableRow* 
ccReg_PageTable_i::getPageRow(CORBA::Short pageRow)
  throw (ccReg::Table::INVALID_ROW)
{
  return getRow(pageRow + start());
}

CORBA::Short 
ccReg_PageTable_i::numPageRows()
{
  unsigned s = start();
  unsigned n = numRows();
  if (s > n) return 0; /// something wrong
  unsigned l = n - s;
  return l < aPageSize ? l : aPageSize;
}

ccReg::TID 
ccReg_PageTable_i::getPageRowId(CORBA::Short row) 
  throw (ccReg::Table::INVALID_ROW)
{
  return getRowId(row + start());
}

void
ccReg_PageTable_i::reloadF()
{
}

ccReg::Filters::Compound_ptr
ccReg_PageTable_i::add()
{
  return ccReg::Filters::Compound::_nil();
}

ccReg::Filters::Iterator_ptr 
ccReg_PageTable_i::getIterator()
{
  TRACE("[CALL] ccPageTable_i::getIterator()");
  return it._this();
}

void 
ccReg_PageTable_i::setDB(DBase::Manager* _dbm)
{
  dbm = _dbm;
}

void
ccReg_PageTable_i::clear() {
  TRACE("[CALL] ccReg_PageTable_i::clear()");
  it.clearF();
  uf.clear();
}

void
ccReg_PageTable_i::loadFilter(ccReg::TID _id) {
  TRACE(boost::format("[CALL] ccReg_PageTable_i::loadFilter(%1%)") % _id);
  uf.clear();
  it.clearF();

  std::auto_ptr<Register::Filter::Manager>
      tmp_filter_manager(Register::Filter::Manager::create(dbm));
  tmp_filter_manager->load(_id, uf);
}

void
ccReg_PageTable_i::saveFilter(const char*  _name) {
}

CORBA::Short ccReg_PageTable_i::getSortedBy() {
  return sorted_by_;
}