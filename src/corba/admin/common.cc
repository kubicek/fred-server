#include "common.h"

std::string
formatDate(date d)
{
  if (d.is_special()) return "";
  std::ostringstream buf;
  buf.imbue(std::locale(
    buf.getloc(),
    new boost::gregorian::date_facet("%d.%m.%Y")
  ));
  buf << d; 
  return buf.str();
}

std::string 
formatTime(ptime p,bool date)
{
  if (p.is_special()) return "";
  ptime lt = boost::date_time::c_local_adjustor<ptime>::utc_to_local(p);
  std::ostringstream stime;
  stime << std::setfill('0') << std::setw(2)
        << lt.date().day() << "." 
        << std::setw(2)
        << (int)lt.date().month() << "." 
        << std::setw(2)
        << lt.date().year();
  if (date) 
   stime << " "
         << std::setw(2)
         << lt.time_of_day().hours() << ":"
         << std::setw(2)
         << lt.time_of_day().minutes() << ":"
         << std::setw(2)
         << lt.time_of_day().seconds();
  return stime.str();
}

std::string
formatMoney(Register::Invoicing::Money m)
{
  std::stringstream buf;
  buf << m / 100 << "." << std::setw(2) << std::setfill('0') << m % 100;
  return buf.str();
}

ptime
makeBoostTime(const ccReg::DateTimeType& t)
{
  date d;
  try {
    d = date(t.date.year,t.date.month,t.date.day);
  }
  catch (...) {}
  return ptime(d,time_duration(t.hour,t.minute,t.second));
}

date 
makeBoostDate(const ccReg::DateType& t) {
  date d;
  try {
    d = date(t.year,t.month,t.day);
  }
  catch (...) {}
  return d;
}

ccReg::DateTimeType
makeCorbaTime(ptime p)
{
  ccReg::DateTimeType d;
  if (p.is_special()) {
    d.date.day = 0;
    d.date.month = 0;
    d.date.year = 0;
    d.hour = 0;
    d.minute = 0;
    d.second = 0;
  } else {
    d.date.day = p.date().day();
    d.date.month = p.date().month();
    d.date.year = p.date().year();
    d.hour = p.time_of_day().hours();
    d.minute = p.time_of_day().minutes();
    d.second = p.time_of_day().seconds();
  }
  return d;
}

ccReg::DateType 
makeCorbaDate(date p) {
  ccReg::DateType d;
  if (p.is_special()) {
    d.day = 0;
    d.month = 0;
    d.year = 0;
  }
  else {
    d.day = p.day();
    d.month = p.month();
    d.year = p.year();
  }
  return d;
}

time_period 
setPeriod(const ccReg::DateTimeInterval& _v)
{
  return time_period(makeBoostTime(_v.from),makeBoostTime(_v.to));
}

time_period 
setPeriod(const ccReg::DateInterval& _v)
{
  date from;
  date to;
  try {
    from = date(_v.from.year,_v.from.month,_v.from.day);
  }
  catch (...) {}
  try {
    to = date(_v.to.year,_v.to.month,_v.to.day);
  }
  catch (...) {}
  return time_period(
    ptime(from,time_duration(0,0,0)),
    ptime(to,time_duration(0,0,0))
  );
}


void
clearPeriod(ccReg::DateTimeInterval& _v)
{
  _v.from.date.year = 0;
  _v.from.date.month = 0;
  _v.from.date.day = 0;
  _v.from.hour = 0;
  _v.from.minute = 0;
  _v.from.second = 0;
  _v.to.date.year = 0;
  _v.to.date.month = 0;
  _v.to.date.day = 0;
  _v.to.hour = 0;
  _v.to.minute = 0;
  _v.to.second = 0;
}