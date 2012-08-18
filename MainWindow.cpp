#include "MainWindow.h"

#include <QDebug>

#if defined (Q_OS_MAC)

#include "UtilitiesMac.h"

#elif defined(Q_OS_WIN)

#include "UtilitiesWin.h"

#endif

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    mProgress = 0;
    mFinished = false;
    mTitle = "";

    setupUi(this);


    toolBar->addAction(webView->pageAction(QWebPage::Back));
    toolBar->addAction(webView->pageAction(QWebPage::Forward));
    toolBar->addAction(webView->pageAction(QWebPage::Stop));
    toolBar->addAction(webView->pageAction(QWebPage::Reload));
    toolBar->addWidget(addressEdit);
    toolBar->addWidget(setDefaultButton);

    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(webViewTitleChanged(QString)));
    connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(webViewUrlChanged(QUrl)));
    connect(webView, SIGNAL(loadProgress(int)), this, SLOT(webViewLoadProgress(int)));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(webViewLoadFinished(bool)));
    connect(webView, SIGNAL(loadStarted()), this, SLOT(webViewLoadStarted()));

    updateUi();
    checkDefault();
}

void MainWindow::openUrl(const QUrl& url)
{
    webView->setUrl(url);
}

void MainWindow::checkDefault()
{
    if (Utilities::isDefault())
    {
        setDefaultButton->setEnabled(false);
        setDefaultButton->setText(tr("Default"));
    }
    else
    {
        setDefaultButton->setEnabled(true);
        setDefaultButton->setText(tr("Set default"));
    }
}

void MainWindow::updateUi()
{
    if (mProgress == 0 || mProgress == 100)
    {
        setWindowTitle(mTitle);
    }
    else
    {
        setWindowTitle(QString("%1 - %2%").arg(mTitle).arg(mProgress));
    }

    addressEdit->setText(webView->url().toString());
}

void MainWindow::webViewTitleChanged(const QString& title)
{
    mTitle = title;
    updateUi();
}

void MainWindow::webViewUrlChanged(const QUrl& url)
{
    updateUi();
}

void MainWindow::webViewLoadProgress(int progress)
{
    mProgress = progress;
    updateUi();
}

void MainWindow::webViewLoadFinished(bool ok)
{
    mFinished = true;
    updateUi();
}

void MainWindow::webViewLoadStarted()
{
    mProgress = 0;
    mFinished = false;
    mTitle = "";

    updateUi();
}

void MainWindow::on_addressEdit_returnPressed()
{
    QUrl url(addressEdit->text());
    if (url.isValid())
    {
        webView->setUrl(url);
    }
}

void MainWindow::on_setDefaultButton_clicked()
{
    Utilities::setDefault();

    checkDefault();
}
