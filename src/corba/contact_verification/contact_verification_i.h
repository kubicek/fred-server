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
*  @contact_verification_i.h
*  header of contact verification corba wrapper
*  pregenerated by $> omniidl -bcxx -Wba -Wbexample -C./src/corba ~/workspace/enum/idl/idl/ContactVerification.idl
*/

#ifndef CONTACT_VERIFICATION_I_H__
#define CONTACT_VERIFICATION_I_H__

#include "src/corba/ContactVerification.hh"
#include <memory>
#include <string>

namespace Registry
{
    namespace Contact
    {
        namespace Verification
        {
            class ContactVerificationImpl;//pimpl class

            class ContactVerification_i: public POA_Registry::ContactVerification
            {
            private:
                // do not copy
                const std::auto_ptr<ContactVerificationImpl> pimpl_;
                ContactVerification_i(const ContactVerification_i&);//no body
                ContactVerification_i& operator= (const ContactVerification_i&);//no body

            public:
              // standard constructor
              ContactVerification_i(const std::string &_server_name);
              virtual ~ContactVerification_i();

              // methods corresponding to defined IDL attributes and operations
              ::CORBA::ULongLong createConditionalIdentification(
                      const char* contact_handle
                      , const char* registrar_handle
                      , ::CORBA::ULongLong log_id
                      , ::CORBA::String_out request_id);

              ::CORBA::ULongLong processConditionalIdentification(
                      const char* request_id
                      , const char* password
                      , ::CORBA::ULongLong log_id);

              ::CORBA::ULongLong processIdentification(
                      const char* contact_handle
                      , const char* password
                      , ::CORBA::ULongLong log_id);

              char* getRegistrarName(const char* registrar_handle);

            };//class ContactVerification_i
        }
    }
}

#endif //CONTACT_VERIFICATION_I_H__

