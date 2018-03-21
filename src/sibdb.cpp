// Copyright (c) 2015 The Sibcoin developers
// Copyright (c) 2018 The SurCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sibdb.h"

using namespace boost;
using namespace std;


bool CSurDB::WriteName(const std::string& key, const std::string& arr)
{
    return Write(key, arr);
}

bool CSurDB::ReadName(const std::string& key, std::string& arr)
{
    return Read(key, arr);
}


bool CSurDB::EraseName(const std::string& key)
{
    return Erase(key);
}
