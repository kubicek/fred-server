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
 *  @server_i.cc
 *  implementational code for administrativeblocking IDL interface
 *  pregenerated by $> omniidl -bcxx -Wba -Wbexample -C./src/corba ~/workspace/enum/idl/idl/AdministrativeBlocking.idl
 */


#include "server_i.h"
#include "corba_conversion.h"
#include "src/admin_block/administrativeblocking.h"
#include <string>


namespace Registry
{
    namespace Administrative
    {

        Server_i::Server_i(const std::string &_server_name)
        : bimpl_(new BlockingImpl(_server_name))
        {}

        Server_i::~Server_i()
        {}

        //   Methods corresponding to IDL attributes and operations
        StatusDescList* Server_i::getBlockingStatusDescList(const char* _lang)
        {
            try {
                return corba_wrap_status_desc_list(bimpl_->getBlockingStatusDescList(_lang));
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
        }

        DomainOwnerChangeList* Server_i::blockDomains(
            const ::Registry::Administrative::DomainList &domain_list,
            const ::Registry::Administrative::StatusList &status_list,
            ::Registry::Administrative::OwnerBlockMode owner_block_mode,
            const char *reason)
        {
            throw std::runtime_error("blockDomains not implemented");
        }

        DomainIdHandleOwnerChangeList* Server_i::blockDomainsId(
            const ::Registry::Administrative::DomainIdList& domain_list,
            const ::Registry::Administrative::StatusList& status_list,
            ::Registry::Administrative::OwnerBlockMode owner_block_mode,
            ::Registry::Administrative::NullableDate *block_to_date,
            const char* reason,
            ::CORBA::ULongLong log_req_id)
        {
            try {
                return corba_wrap_owner_change_list(bimpl_->blockDomainsId(corba_unwrap_domain_id_list(domain_list),
                                                                           corba_unwrap_status_list(status_list),
                                                                           corba_unwrap_owner_block_mode(owner_block_mode),
                                                                           corba_unwrap_nullable_date(block_to_date),
                                                                           reason,
                                                                           log_req_id));
            }
            catch (const EX_DOMAIN_ID_NOT_FOUND &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_UNKNOWN_STATUS &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_DOMAIN_ID_ALREADY_BLOCKED &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_OWNER_HAS_OTHER_DOMAIN &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_CONTACT_BLOCK_PROHIBITED &e) {
                throw corba_wrap_exception(e);
            }
        }

        void Server_i::updateBlockDomains(
            const ::Registry::Administrative::DomainList &domain_list,
            const ::Registry::Administrative::StatusList &status_list,
            const char *reason)
        {
            throw std::runtime_error("updateBlockDomains not implemented");
        }
        
        void Server_i::updateBlockDomainsId(
            const ::Registry::Administrative::DomainIdList &domain_list,
            const ::Registry::Administrative::StatusList &status_list,
            ::Registry::Administrative::NullableDate *block_to_date,
            const char *reason,
            ::CORBA::ULongLong log_req_id)
        {
            try {
                bimpl_->updateBlockDomainsId(corba_unwrap_domain_id_list(domain_list),
                                             corba_unwrap_status_list(status_list),
                                             corba_unwrap_nullable_date(block_to_date),
                                             reason,
                                             log_req_id);
            }
            catch (const EX_DOMAIN_ID_NOT_FOUND &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_UNKNOWN_STATUS &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
        }
        
        void Server_i::restorePreAdministrativeBlockStates(
            const ::Registry::Administrative::DomainList &domain_list,
            ::Registry::Administrative::NullableString *new_owner,
            const char *reason)
        {
            throw std::runtime_error("restorePreAdministrativeBlockStates not implemented");
        }

        void Server_i::restorePreAdministrativeBlockStatesId(
            const ::Registry::Administrative::DomainIdList &domain_list,
            ::Registry::Administrative::NullableString *new_owner,
            const char* reason,
            ::CORBA::ULongLong log_req_id)
        {
            try {
                bimpl_->restorePreAdministrativeBlockStatesId(corba_unwrap_domain_id_list(domain_list),
                                                              corba_unwrap_nullable_string(new_owner),
                                                              reason,
                                                              log_req_id);
            }
            catch (const EX_DOMAIN_ID_NOT_FOUND &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_DOMAIN_ID_NOT_BLOCKED &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_NEW_OWNER_DOES_NOT_EXISTS &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
        }

        void Server_i::unblockDomains(
            const ::Registry::Administrative::DomainList &domain_list,
            ::Registry::Administrative::NullableString *new_owner,
            ::CORBA::Boolean remove_admin_c,
            const char* reason)
        {
            throw std::runtime_error("unblockDomains not implemented");
        }
        
        void Server_i::unblockDomainsId(
            const ::Registry::Administrative::DomainIdList &domain_list,
            ::Registry::Administrative::NullableString *new_owner,
            ::CORBA::Boolean remove_admin_c,
            const char* reason,
            ::CORBA::ULongLong log_req_id)
        {
            try {
                bimpl_->unblockDomainsId(corba_unwrap_domain_id_list(domain_list),
                                         corba_unwrap_nullable_string(new_owner),
                                         remove_admin_c,
                                         reason,
                                         log_req_id);
            }
            catch (const EX_DOMAIN_ID_NOT_FOUND &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_DOMAIN_ID_NOT_BLOCKED &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_NEW_OWNER_DOES_NOT_EXISTS &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
        }
        
        void Server_i::blacklistAndDeleteDomains(
            const ::Registry::Administrative::DomainList &domain_list,
            ::Registry::Administrative::NullableDate *blacklist_to_date)
        {
            throw std::runtime_error("blacklistAndDeleteDomains not implemented");
        }

        void Server_i::blacklistAndDeleteDomainsId(
            const ::Registry::Administrative::DomainIdList &domain_list,
            ::Registry::Administrative::NullableDate *blacklist_to_date,
            const char* reason,
            ::CORBA::ULongLong log_req_id)
        {
            try {
                bimpl_->blacklistAndDeleteDomainsId(corba_unwrap_domain_id_list(domain_list),
                                                    corba_unwrap_nullable_date(blacklist_to_date),
                                                    reason,
                                                    log_req_id);
            }
            catch (const EX_DOMAIN_ID_NOT_FOUND &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
        }

        void Server_i::blacklistDomains(
            const ::Registry::Administrative::DomainList &domain_list,
            ::Registry::Administrative::NullableDate *blacklist_to_date,
            ::CORBA::Boolean with_delete)
        {
            throw std::runtime_error("blacklistDomains not implemented");
        }

        void Server_i::blacklistDomainsId(
            const ::Registry::Administrative::DomainIdList &domain_list,
            ::Registry::Administrative::NullableDate *blacklist_to_date,
            ::CORBA::Boolean with_delete,
            ::CORBA::ULongLong log_req_id)
        {
            try {
                bimpl_->blacklistDomainsId(corba_unwrap_domain_id_list(domain_list),
                                           corba_unwrap_nullable_date(blacklist_to_date),
                                           with_delete,
                                           log_req_id);
            }
            catch (const EX_DOMAIN_ID_NOT_FOUND &e) {
                throw corba_wrap_exception(e);
            }
            catch (const EX_INTERNAL_SERVER_ERROR &e) {
                throw corba_wrap_exception(e);
            }
        }

        void Server_i::unblacklistAndCreateDomains(
            const ::Registry::Administrative::DomainList &domain_list,
            const char* owner)
        {
            throw std::runtime_error("unblacklistAndCreateDomains not implemented");
        }

    }//namespace Administrative
}//namespace Registry
