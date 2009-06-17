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

#ifndef _FILECLIENT_H_
#define _FILECLIENT_H_

#define FILE_LIST_NAME              "file_list"
#define FILE_LIST_NAME_DESC         "list all files"
#define FILE_LIST_HELP_NAME         "file_list_help"
#define FILE_LIST_HELP_NAME_DESC    "help for file list"

#define FILE_SHOW_OPTS_NAME         "file_show_opts"
#define FILE_SHOW_OPTS_NAME_DESC    "show all file command line options"
#define FILE_PATH_NAME              "path"
#define FILE_PATH_NAME_DESC         "path"
#define FILE_MIME_NAME              "mime"
#define FILE_MIME_NAME_DESC         "mime"
#define FILE_SIZE_NAME              "size"
#define FILE_SIZE_NAME_DESC         "size"
#define FILE_TYPE_NAME              "file_type"
#define FILE_TYPE_NAME_DESC         "file type"

#include <iostream>
#include <boost/program_options.hpp>
#include "old_utils/dbsql.h"

#include "register/register.h"
#include "corba/admin/admin_impl.h"
#include "corba/mailer_manager.h"

namespace Admin {

class FileClient {
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
    FileClient();
    FileClient(std::string connstring,
            std::string nsAddr);
    ~FileClient();
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

#endif // _FILECLIENT_H_

