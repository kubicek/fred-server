/*
 * Copyright (C) 2012  CZ.NIC, z.s.p.o.
 *
 * This file is part of FRED.
 *
 * FRED is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * FRED is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FRED.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
*  @server_i.h
*  header of mojeid corba wrapper
*  pregenerated by $> omniidl -bcxx -Wba -Wbexample -C./src/corba ~/workspace/enum/idl/idl/MojeID.idl
*/
#ifndef SERVER_I_H_
#define SERVER_I_H_

#include "src/corba/corba_auto_garbaged_list.h"
#include "src/corba/MojeID.hh"
#include <memory>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/thread/thread.hpp>


namespace Registry
{
    namespace MojeID
    {

        class ContactHandleListIter_i : public POA_Registry::MojeID::ContactHandleListIter
        {
        public:
            // standard constructor
            ContactHandleListIter_i(const std::vector<std::string> &_handles);

            virtual ~ContactHandleListIter_i();

            // methods corresponding to defined IDL attributes and operations
            Registry::MojeID::ContactHandleList* getNext(::CORBA::ULong count);

            void destroy();

            // methods for compatibility with CorbaAutoGarbageList
            void close();

            bool is_closed() const;

            const boost::posix_time::ptime& get_last_used() const;


        private:
            enum Status
            {
                ACTIVE = 1,
                CLOSED = 2
            };

            Status status_;
            boost::posix_time::ptime last_used_;
            std::vector<std::string> handles_;
            std::vector<std::string>::const_iterator it_;
        };


        class MojeIDImpl;//pimpl class


        ///mojeid corba interface
        class Server_i: public POA_Registry::MojeID::Server
        {
        private:
            // do not copy
            const std::auto_ptr<MojeIDImpl> pimpl_;

            CorbaAutoGarbagedList<ContactHandleListIter_i> contact_handle_list_objects_;

            Server_i(const Server_i&);//no body
            Server_i& operator= (const Server_i&);//no body


        public:
          // standard constructor
          Server_i(const std::string &_server_name);
          virtual ~Server_i();
          // methods corresponding to defined IDL attributes and operations
          ::CORBA::ULongLong contactCreatePrepare(
                  const Registry::MojeID::Contact& c
                  , const char* trans_id
                  , ::CORBA::ULongLong request_id
                  , ::CORBA::String_out ident);

          ::CORBA::ULongLong contactTransferPrepare(
                  const char* handle
                  , const char* trans_id
                  , ::CORBA::ULongLong request_id
                  , ::CORBA::String_out ident);

          void contactUpdatePrepare(
                  const Registry::MojeID::Contact& c
                  , const char* trans_id
                  , ::CORBA::ULongLong request_id);

          Registry::MojeID::Contact* contactInfo(
                  ::CORBA::ULongLong contact_id);

          ::CORBA::ULongLong processIdentification(
                  const char* ident_request_id
                  , const char* password
                  , ::CORBA::ULongLong request_id);

          char* getIdentificationInfo(
                  ::CORBA::ULongLong contact_id);

          void commitPreparedTransaction(
                  const char* trans_id);

          void rollbackPreparedTransaction(
                  const char* trans_id);

          Registry::MojeID::Buffer* getValidationPdf(
                  ::CORBA::ULongLong contact_id);

          void createValidationRequest(
                  ::CORBA::ULongLong contact_id
                   , ::CORBA::ULongLong request_id);

          Registry::MojeID::ContactStateInfoList* getContactsStates(
                  ::CORBA::ULong last_hours);

          Registry::MojeID::ContactStateInfo getContactState(
                  ::CORBA::ULongLong contact_id);

          ::CORBA::ULongLong getContactId(
                  const char* handle);

          void contactCancelAccountPrepare(
              ::CORBA::ULongLong contact_id
               , const char* trans_id
               , ::CORBA::ULongLong request_id);

          Registry::MojeID::ContactHandleList* getUnregistrableHandles();

          Registry::MojeID::ContactHandleListIter_ptr getUnregistrableHandlesIter();

          char* contactAuthInfo(::CORBA::ULongLong contact_id);
        };//class Server_i
    }//namespace MojeID
}//namespace Registry

#endif //SERVER_I_H_
