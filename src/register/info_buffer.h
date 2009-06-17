#ifndef _INFO_BUFFER_H_
#define _INFO_BUFFER_H_

#include <string>
#include "types.h"
#include "domain.h"
#include "contact.h"
#include "nsset.h"
#include "exceptions.h" 

namespace Register
{
  namespace InfoBuffer
  {
    struct INVALID_REGISTRAR {};
    /// type of info query
    enum Type
    {
      T_LIST_CONTACTS, ///< list contact that belongs to particular registrar
      T_LIST_DOMAINS, ///< list domains that belongs to particular registrar
      T_LIST_NSSETS, ///< list nssets that belongs to particular registrar
      T_DOMAINS_BY_NSSET, ///< list domains that are using specified nsset
      T_DOMAINS_BY_CONTACT, ///< list domains somewhat connected to contact
      T_NSSETS_BY_CONTACT, ///< list nssets with specified admin contact
      T_NSSETS_BY_NS ///< list nssets containing specified host as nameserver
    };
    /// one chunk of data returned by one call of retrieving function
    class Chunk
    {
     public:
      /// destructor 
      virtual ~Chunk() {}
      /// returns number of records in chunk
      virtual unsigned long getCount() const = 0;
      /// returns actual record in chunk and move ahead, at the end return ""
      virtual const std::string& getNext() = 0;
    };
    /// management class for info buffer manipulation
    class Manager
    {
     public:
      /// destructor 
      virtual ~Manager() {}
      /// factory method
      static Manager *create(
        DB *db, Domain::Manager *dm, NSSet::Manager *nm, Contact::Manager *cm
      );
      /// fill buffer with result of info command and reset pointer to start
      virtual unsigned long info(
        TID registrar, Type infotype, const std::string& request
      ) throw (SQL_ERROR, INVALID_REGISTRAR) = 0;
      /// get chunk of result of specified size and update pointer 
      virtual Chunk* getChunk(TID registrar, unsigned size) 
        throw (SQL_ERROR, INVALID_REGISTRAR) = 0;
    }; 
  };
};

#endif