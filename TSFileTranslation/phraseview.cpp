/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Linguist of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "globals.h"
#include "mainwindow.h"
#include "messagemodel.h"
#include "phrase.h"
#include "phraseview.h"
#include "phrasemodel.h"
#include "simtexth.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QHeaderView>
#include <QKeyEvent>
#include <QSettings>
#include <QTreeView>
#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE

// Maximum number of guesses to display
static const int MaxCandidates = 5;

static QString phraseViewHeaderKey()
{
    return settingPath("PhraseViewHeader");
}

PhraseView::PhraseView(MultiDataModel *model, QList<QHash<QString, QList<Phrase *> > > *phraseDict, QWidget *parent)
    : QTreeView(parent),
      m_dataModel(model),
      m_phraseDict(phraseDict),
      m_modelIndex(-1),
      m_doGuesses(true)
{
    setObjectName(QLatin1String("phrase list view"));

    m_phraseModel = new PhraseModel(this);

    setModel(m_phraseModel);
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setRootIsDecorated(false);
    setItemsExpandable(false);

    for (int i = 0; i < 10; i++)
        (void) new GuessShortcut(i, this, SLOT(guessShortcut(int)));

    header()->setSectionResizeMode(QHeaderView::Interactive);
    header()->setSectionsClickable(true);
    header()->restoreState(QSettings().value(phraseViewHeaderKey()).toByteArray());

    connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(selectPhrase(QModelIndex)));

    Provider = TranslateAPIProvider::Baidu;
    Url = "https://fanyi-api.baidu.com/api/trans/vip/translate";
    APIID = "-";
    APIKey = "-";
    FromLan = "en";
    ToLan = "zh";

    IsSetAPi = false;
    pCurl = nullptr;
    pCurl = curl_easy_init();
    if (pCurl != nullptr){

    }
}

PhraseView::~PhraseView()
{
    QSettings().setValue(phraseViewHeaderKey(), header()->saveState());
    deleteGuesses();
}

void PhraseView::toggleGuessing()
{
    m_doGuesses = !m_doGuesses;
    update();
}

void PhraseView::update()
{
    setSourceText(m_modelIndex, m_sourceText);
}


void PhraseView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (!index.isValid())
        return;

    QMenu *contextMenu = new QMenu(this);

    QAction *insertAction = new QAction(tr("Insert"), contextMenu);
    connect(insertAction, SIGNAL(triggered()), this, SLOT(selectPhrase()));

    QAction *editAction = new QAction(tr("Edit"), contextMenu);
    connect(editAction, SIGNAL(triggered()), this, SLOT(editPhrase()));
    editAction->setEnabled(model()->flags(index) & Qt::ItemIsEditable);

    contextMenu->addAction(insertAction);
    contextMenu->addAction(editAction);

    contextMenu->exec(event->globalPos());
    event->accept();
}

void PhraseView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (!index.isValid())
        return;

    emit phraseSelected(m_modelIndex, m_phraseModel->phrase(index)->target());
    event->accept();
}

void PhraseView::guessShortcut(int key)
{
    foreach (const Phrase *phrase, m_phraseModel->phraseList())
        if (phrase->shortcut() == key) {
            emit phraseSelected(m_modelIndex, phrase->target());
            return;
        }
}

void PhraseView::selectPhrase(const QModelIndex &index)
{
    emit phraseSelected(m_modelIndex, m_phraseModel->phrase(index)->target());
}

void PhraseView::selectPhrase()
{
    emit phraseSelected(m_modelIndex, m_phraseModel->phrase(currentIndex())->target());
}

void PhraseView::editPhrase()
{
    edit(currentIndex());
}

static CandidateList similarTextHeuristicCandidates(MultiDataModel *model, int mi,
    const char *text, int maxCandidates)
{
    QList<int> scores;
    CandidateList candidates;

    StringSimilarityMatcher stringmatcher(QString::fromLatin1(text));

    for (MultiDataModelIterator it(model, mi); it.isValid(); ++it) {
        MessageItem *m = it.current();
        if (!m)
            continue;

        TranslatorMessage mtm = m->message();
        if (mtm.type() == TranslatorMessage::Unfinished
            || mtm.translation().isEmpty())
            continue;

        QString s = m->text();

        int score = stringmatcher.getSimilarityScore(s);

        if (candidates.count() == maxCandidates && score > scores[maxCandidates - 1])
            candidates.removeLast();
        if (candidates.count() < maxCandidates && score >= textSimilarityThreshold ) {
            Candidate cand(s, mtm.translation());

            int i;
            for (i = 0; i < candidates.size(); ++i) {
                if (score >= scores.at(i)) {
                    if (score == scores.at(i)) {
                        if (candidates.at(i) == cand)
                            goto continue_outer_loop;
                    } else {
                        break;
                    }
                }
            }
            scores.insert(i, score);
            candidates.insert(i, cand);
        }
        continue_outer_loop:
        ;
    }
    return candidates;
}


void PhraseView::setSourceText(int model, const QString &sourceText)
{
    m_modelIndex = model;
    m_sourceText = sourceText;
    m_phraseModel->removePhrases();
    deleteGuesses();

    if (model < 0)
        return;

    foreach (Phrase *p, getPhrases(model, sourceText))
        m_phraseModel->addPhrase(p);

    if (!sourceText.isEmpty() && m_doGuesses) {
        CandidateList cl = similarTextHeuristicCandidates(m_dataModel, model, sourceText.toLatin1(), MaxCandidates);
        bool RecvNetworkTranslate = false;

        QString Src = sourceText;
        QString Tag ="";
        if (Translate(Src,Tag) == 0){
            Candidate kl;
            kl.source = Src;
            kl.target = Tag;
            cl.push_front(kl);
            RecvNetworkTranslate = true;
        }

        int n = 0;
        foreach (const Candidate &candidate, cl) {
            QString def;
            if (n == 0 && RecvNetworkTranslate){
                def = tr("Guess (%1)").arg(QKeySequence(Qt::CTRL | (Qt::Key_0 + (n + 1))).toString(QKeySequence::NativeText));
                def += " (From Baidu Translate)";
                Phrase *guess = new Phrase(candidate.source, candidate.target, def, 0);
                m_guesses.append(guess);
                m_phraseModel->addPhrase(guess);
                ++n;
                continue;
            }
            if (n < 9)
                def = tr("Guess (%1)").arg(QKeySequence(Qt::CTRL | (Qt::Key_0 + (n + 1))).toString(QKeySequence::NativeText));
            else
                def = tr("Guess");
            Phrase *guess = new Phrase(candidate.source, candidate.target, def, n);
            m_guesses.append(guess);
            m_phraseModel->addPhrase(guess);
            ++n;
        }
    }
}

void PhraseView::SetTranslateAPI(TranslateAPIProvider Provider, std::__cxx11::string Url, std::__cxx11::string APIID, std::__cxx11::string Key,std::string FromLan, std::string ToLan)
{
    this->Provider = Provider;
    this->Url = Url;
    this->APIID = APIID;
    this->APIKey = Key;
    this->FromLan = FromLan;
    this->ToLan = ToLan;
}

QList<Phrase *> PhraseView::getPhrases(int model, const QString &source)
{
    QList<Phrase *> phrases;
    QString f = MainWindow::friendlyString(source);
    QStringList lookupWords = f.split(QLatin1Char(' '));

    foreach (const QString &s, lookupWords) {
        if (m_phraseDict->at(model).contains(s)) {
            foreach (Phrase *p, m_phraseDict->at(model).value(s)) {
                if (f.contains(MainWindow::friendlyString(p->source())))
                    phrases.append(p);
            }
        }
    }
    return phrases;
}

void PhraseView::deleteGuesses()
{
    qDeleteAll(m_guesses);
    m_guesses.clear();
}

int PhraseView::Translate(QString &Src, QString &Tag)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    if (Provider == TranslateAPIProvider::Google){

        return -1;
    }
    if (Provider == TranslateAPIProvider::Baidu){
        QString Salt = QString::number(qrand());
        QString Sign = QString(APIID.c_str()) + Src + Salt + QString(APIKey.c_str());
        Sign = QCryptographicHash::hash(Sign.toUtf8(),QCryptographicHash::Md5).toHex();

        curl_easy_setopt(pCurl, CURLOPT_URL, Url.c_str());
        std::string PostData="";
        PostData += "appid=" + APIID;
        PostData += "&salt=" + Salt.toStdString();
        PostData += "&sign=" + Sign.toStdString();
        PostData += "&from=" + FromLan;
        PostData += "&to=" + ToLan;
        PostData += "&q=" + QUrl::toPercentEncoding(Src).toStdString();
        Curl_RecvData m_RecvData;
        curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &m_RecvData);
        curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, PostData.c_str());
        CURLcode res = curl_easy_perform(pCurl);

        if (res == CURLE_OK){
            QJsonDocument Doc = QJsonDocument::fromJson(m_RecvData.Data);
            QJsonArray trans_result = Doc.object()["trans_result"].toArray();
            Src = trans_result[0].toObject().toVariantMap()["src"].toString();
            Tag = trans_result[0].toObject().toVariantMap()["dst"].toString();
            return 0;
        }else{
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            return -1;
        }
    }
}

QT_END_NAMESPACE

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    ((Curl_RecvData *)userdata)->Data.append(ptr,nmemb);
    return nmemb;
}
