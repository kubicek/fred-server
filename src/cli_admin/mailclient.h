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

#ifndef _MAILCLIENT_H_
#define _MAILCLIENT_H_

#define MAIL_SHOW_OPTS_NAME         "mail_show_opts"
#define MAIL_SHOW_OPTS_NAME_DESC    "show all mail command line options"
#define MAIL_LIST_NAME              "mail_list"
#define MAIL_LIST_NAME_DESC         "list all mails"
#define MAIL_LIST_HELP_NAME         "mail_list_help"
#define MAIL_LIST_HELP_NAME_DESC    "help for mail list"

#define MAIL_STATUS_NAME            "status"
#define MAIL_STATUS_NAME_DESC       "status description"
#define MAIL_ATTEMPT_NAME           "attempt"
#define MAIL_ATTEMPT_NAME_DESC      "attempt description"
#define MAIL_MESSAGE_NAME           "message"
#define MAIL_MESSAGE_NAME_DESC      "message desc"
#define MAIL_ATTACHMENT_ID_NAME           "attachment_id"
#define MAIL_ATTACHMENT_ID_NAME_DESC      "attachment_id desc"
#define MAIL_ATTACHMENT_NAME_NAME         "attachment_name"
#define MAIL_ATTACHMENT_NAME_NAME_DESC    "attachment_name desc"
#define MAIL_MODDATE_FROM_NAME            "mod_date_from"
#define MAIL_MODDATE_FROM_NAME_DESC       "mod date from"
#define MAIL_MODDATE_TO_NAME              "mod_date_to"
#define MAIL_MODDATE_TO_NAME_DESC         "mod date to"
#define MAIL_TYPE_NAME              "mail_type"
#define MAIL_TYPE_NAME_DESC         "mail type"

#include <iostream>
#include <boost/program_options.hpp>
#include "old_utils/dbsql.h"

#include "register/register.h"
#include "corba/admin/admin_impl.h"
#include "corba/mailer_manager.h"

namespace Admin {

class MailClient {
private:
    std::string m_connstring;
    std::string m_nsAddr;
    CORBA::Long m_clientId;
    DB m_db;
    Database::Manager *m_dbman;
    ccReg::EPP_var m_epp;
    Config::Conf m_conf;

    boost::program_options::options_description *m_options;
    boost::program_options::options_description *m_optionsInvis;
public:
    MailClient();
    MailClient(std::string connstring,
            std::string nsAddr);
    ~MailClient();
    void init(std::string connstring,
            std::string nsAddr,
            Config::Conf &conf);

    boost::program_options::options_description *getVisibleOptions() const;
    boost::program_options::options_description *getInvisibleOptions() const;
    void show_opts() const;

    void list();
    void list_help();
};

} // namespace Admin;

#endif // _MAILCLIENT_H_
