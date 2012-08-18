#include "Application.h"

#include <QMessageBox>
#include <QFileOpenEvent>
#include <QStringList>

#include "MainWindow.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
    mainWindow_ = 0;
    mainWindow_ = new MainWindow;
    mainWindow_->show();


    QStringList arguments = qApp->arguments();
    if (arguments.count() > 1)
    {
        QMessageBox::information(0,
                                 qApp->applicationName(),
                                 arguments.value(1, QString()),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
        mainWindow_->openUrl(QUrl(arguments.value(1, QString())));
    }

    if (url_.isValid())
    {
        mainWindow_->openUrl(url_);
    }
}

bool Application::event(QEvent* event)
{
    bool eaten = false;

    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent* fileOpenEvent = static_cast<QFileOpenEvent*>(event);

        if (mainWindow_)
        {
            mainWindow_->openUrl(fileOpenEvent->url());
        }
        else
        {
            url_ = fileOpenEvent->url();
        }

        eaten = true;
    }
    else
    {
        eaten = QApplication::event(event);
    }

    return eaten;
}
