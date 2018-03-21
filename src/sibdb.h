// Copyright (c) 2015 The Sibcoin developers
// Copyright (c) 2018 The SurCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SURDB_H
#define	SURDB_H

#include "db.h"

#include <string>

/** Access to the wallet database (sib.dat) */
class CSurDB : public CDB
{
public:
    CSurDB(const std::string& strFilename, const char* pszMode = "cr+") : CDB(strFilename, pszMode)
    {
    }

    bool WriteName(const std::string& key, const std::string &arr);
    bool ReadName(const std::string& key,  std::string &arr);
    bool EraseName(const std::string& key);

};
#endif	/* SURDB_H */
