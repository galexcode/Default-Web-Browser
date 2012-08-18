#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QUrl>

class MainWindow;
class Application : public QApplication
{
    Q_OBJECT

private:
    MainWindow* mainWindow_;
    QUrl url_;

public:
    explicit Application(int& argc, char** argv);

protected:
    bool event(QEvent* event);
};

#endif // APPLICATION_H
