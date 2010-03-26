/*
 *  Copyright (C) 2008  CZ.NIC, z.s.p.o.
 *
 *  This file is part of FRED.
 *
 *  FRED is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *
 *  FRED is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with FRED.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BANKCLIENT_H_
#define _BANKCLIENT_H_


#define BANK_SHOW_OPTS_NAME         "bank_show_opts"
#define BANK_SHOW_OPTS_NAME_DESC    "show all banking options"
#define BANK_ONLINE_LIST_NAME       "bank_online_list"
#define BANK_ONLINE_LIST_NAME_DESC  "list of online payments"
#define BANK_STATEMENT_LIST_NAME    "bank_statement_list"
#define BANK_STATEMENT_LIST_NAME_DESC "list of bank statements"

#define BANK_ADD_ACCOUNT_NAME           "bank_add_account"
#define BANK_ADD_ACCOUNT_NAME_DESC      "add bank account"
#define BANK_ADD_ACCOUNT_HELP_NAME      "bank_add_account_help"
#define BANK_ADD_ACCOUNT_HELP_NAME_DESC "add bank account help"
#define BANK_ZONE_ID_NAME               "zone_id"
#define BANK_ZONE_ID_NAME_DESC          "zone id"
#define BANK_ZONE_NAME_NAME             "zone_fqdn"
#define BANK_ZONE_NAME_NAME_DESC        "zone fully qualified domain name"
#define BANK_ACCOUNT_NAME_NAME          "account_name"
#define BANK_ACCOUNT_NAME_NAME_DESC     "account name"
#define BANK_ACCOUNT_NUMBER_NAME        "bank_account_number"
#define BANK_ACCOUNT_NUMBER_NAME_DESC   "bank_account_number description"
#define BANK_BANK_CODE_NAME             "bank_code"
#define BANK_BANK_CODE_NAME_DESC        "bank_code description"

#include <boost/program_options.hpp>
#include <iostream>

#include "corba/admin/admin_impl.h"
#include "old_utils/dbsql.h"
#include "baseclient.h"


namespace Admin {

class BankClient : public BaseClient {
private:
    CORBA::Long m_clientId;
    DB m_db;
    ccReg::EPP_var m_epp;
    Config::Conf m_conf;

    boost::program_options::options_description *m_options;
    boost::program_options::options_description *m_optionsInvis;
public:
    BankClient();
    BankClient(std::string connstring,
            std::string nsAddr);
    ~BankClient();
    void init(std::string connstring,
            std::string nsAddr,
            Config::Conf &conf);

    boost::program_options::options_description *getVisibleOptions() const;
    boost::program_options::options_description *getInvisibleOptions() const;
    void show_opts() const;

    int online_list();
    int statement_list();
    void add_bank_account();

    void add_bank_account_help();
};

} // namespace Admin;

#endif //_BANKCLIENT_H_
