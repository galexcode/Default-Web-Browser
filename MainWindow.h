#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"

#include <QUrl>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    
private:
    int mProgress;
    bool mFinished;
    QString mTitle;

public:
    explicit MainWindow(QWidget* parent = 0);

    void openUrl(const QUrl& url);

private:
    void checkDefault();
    void updateUi();

private slots:
    void webViewTitleChanged(const QString& title);
    void webViewUrlChanged(const QUrl& url);
    void webViewLoadProgress(int progress);
    void webViewLoadFinished(bool ok);
    void webViewLoadStarted();

    void on_addressEdit_returnPressed();
    void on_setDefaultButton_clicked();
};

#endif // MAINWINDOW_H
