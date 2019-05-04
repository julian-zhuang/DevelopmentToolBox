/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: baidus://www.qt.io/licensing/
**
** This file is part of the Qt Linguist of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see baidus://www.qt.io/terms-conditions. For further
** information use the contact form at baidus://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: baidus://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PHRASEVIEW_H
#define PHRASEVIEW_H

#include <QList>
#include <QShortcut>
#include <QTreeView>
#include "phrase.h"
#include <curl/curl.h>
#include <functional>
#include <iostream>

#include <QUuid>
#include <QTime>
#include <QCryptographicHash>
#include <QUrl>

QT_BEGIN_NAMESPACE

class MultiDataModel;
class PhraseModel;

enum TranslateAPIProvider{
    Google = 100,
    Baidu
};

struct Curl_RecvData{
    QString Sisson;
    QByteArray Data;
    Curl_RecvData(){
        Sisson= QUuid::createUuid().toString();
        Data.clear();
    }
};
size_t write_callback(char * ptr, size_t size, size_t nmemb, void * userdata);

class GuessShortcut : public QShortcut
{
    Q_OBJECT
public:
    GuessShortcut(int nkey, QWidget *parent, const char *member)
        : QShortcut(parent), nrkey(nkey)
    {
        setKey(Qt::CTRL + (Qt::Key_1 + nrkey));
        connect(this, SIGNAL(activated()), this, SLOT(keyActivated()));
        connect(this, SIGNAL(activated(int)), parent, member);
    }

private slots:
    void keyActivated() { emit activated(nrkey); }

signals:
    void activated(int nkey);

private:
    int nrkey;
};

class PhraseView : public QTreeView
{
    Q_OBJECT

public:
    PhraseView(MultiDataModel *model, QList<QHash<QString, QList<Phrase *> > > *phraseDict, QWidget *parent = 0);
    ~PhraseView();
    void setSourceText(int model, const QString &sourceText);
    void SetTranslateAPI(TranslateAPIProvider Provider, std::string Url,std::string APIID,std::string Key,std::string FromLan, std::string ToLan);
    void SetTranslateAPIEnable(bool Enable);

public slots:
    void toggleGuessing();
    void update();

signals:
    void phraseSelected(int latestModel, const QString &phrase);

protected:
    // QObject
    virtual void contextMenuEvent(QContextMenuEvent *event);
    // QAbstractItemView
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void guessShortcut(int nkey);
    void selectPhrase(const QModelIndex &index);
    void selectPhrase();
    void editPhrase();

private:
    QList<Phrase *> getPhrases(int model, const QString &sourceText);
    void deleteGuesses();
    int Translate(QString &Src, QString &Tag);
    MultiDataModel *m_dataModel;
    QList<QHash<QString, QList<Phrase *> > > *m_phraseDict;
    QList<Phrase *> m_guesses;
    PhraseModel *m_phraseModel;
    QString m_sourceText;
    int m_modelIndex;
    bool m_doGuesses;

    bool m_EnableTranslateAPI;
    TranslateAPIProvider Provider;
    std::string Url;
    std::string APIID;
    std::string APIKey;
    std::string FromLan;
    std::string ToLan;

    CURL *pCurl;
};

QT_END_NAMESPACE

#endif // PHRASEVIEW_H
