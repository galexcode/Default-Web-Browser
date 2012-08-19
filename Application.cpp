#include "Application.h"

#include <QMessageBox>
#include <QFileOpenEvent>
#include <QStringList>

#include "MainWindow.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
    mMainWindow = 0;
    mMainWindow = new MainWindow;
    mMainWindow->show();


    QStringList arguments = qApp->arguments();
    if (arguments.count() > 1)
    {
        QMessageBox::information(0,
                                 qApp->applicationName(),
                                 arguments.value(1, QString()),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
        mMainWindow->openUrl(QUrl(arguments.value(1, QString())));
    }

    if (mUrl.isValid())
    {
        mMainWindow->openUrl(mUrl);
    }
}

bool Application::event(QEvent* event)
{
    bool eaten = false;

    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent* fileOpenEvent = static_cast<QFileOpenEvent*>(event);

        if (mMainWindow)
        {
            mMainWindow->openUrl(fileOpenEvent->url());
        }
        else
        {
            mUrl = fileOpenEvent->url();
        }

        eaten = true;
    }
    else
    {
        eaten = QApplication::event(event);
    }

    return eaten;
}
