// Copyright (c) 2015 The Sibcoin developers
// Copyright (c) 2018 The Surcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SIBMODEL_H
#define	SIBMODEL_H

#include "sibdb.h"

#include <QObject>

#include <QNetworkReply>

class QNetworkAccessManager;
class QResource;


/** Interface to Surcoin DB from Qt view code. */
class SurModel : public QObject
{
    Q_OBJECT

public:
    explicit SurModel(CSurDB *sibdb, QObject *parent = 0);
    ~SurModel();

    void fetch();
    void fetch_url(int _idx);
    bool saveResourceWithMD5();
    bool readResourceWithMD5();

private:
    enum ST {
        ST_INIT,
        ST_LOADING_RCC,
        ST_LOADING_MD5,
        ST_LOADED,
        ST_ERROR,
    };

    QString res_prefix;
    CSurDB *sibDB;
    QNetworkAccessManager* net_manager;
    QByteArray rccData;
    QString rccMD5;
    ST state;
    int try_idx;
    QString data_url;

signals:
    void resourceReady(std::string res_root);


public slots:
    void replyFinished(QNetworkReply* p_reply);

private:
    void loadLocalResource();
    void loadFromDB();
    bool registerRes();

};

#endif	/* SIBMODEL_H */
