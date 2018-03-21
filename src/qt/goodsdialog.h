// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015 The SibCoin developers
// Copyright (c) 2018 The SurCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GOODSDIALOG_H
#define	GOODSDIALOG_H

#include "walletmodel.h"
#include "surmodel.h"

#include <QDialog>
#include <QObject>

namespace Ui {
    class GoodsDialog;
}

/** Dialog to show the HTML page with sales points that accept surcoins */
class GoodsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoodsDialog(QWidget *parent=0);
    ~GoodsDialog();

    void setModel(WalletModel *model);
    void setSurModel(SurModel *surModel);

private:
    Ui::GoodsDialog *ui;
    QString header;
    QString coreOptions;
    QString uiOptions;

    WalletModel *model;
    SurModel *surModel;

    const QString page_name;

public slots:
    void on_resourceReady(std::string res_root);

};


#endif	/* GOODSDIALOG_H */
