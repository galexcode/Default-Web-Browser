#include "UtilitiesWin.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include <QSysInfo>
#include <QString>
#include <QStringList>

#define _WIN32_WINNT 0x0601

#undef UNICODE
#undef _UNICODE

#include <Windows.h>
#include <Shlobj.h>

QString ApplicationName = "My Browser";
QString ApplicationDescription = "The best browser ever!";
QString DocumentName = "MyBrowserHTML";
QString DocumentDescription = "My Browser HTML Document";

#define ExecutablePath QString("\"%1\"").arg(QDir::toNativeSeparators(QApplication::applicationFilePath()))
#define ExecutableDirectory QDir::toNativeSeparators(QApplication::applicationDirPath())
#define ExecutableName QFileInfo(QDir::toNativeSeparators(QApplication::applicationFilePath())).fileName()
#define OpenCommand QString("%1 %2").arg(ExecutablePath).arg("\"%1\"")
#define MainIcon QString("%1,0").arg(ExecutablePath)
#define DocumentIcon QString("%1,0").arg(ExecutablePath)


bool coInitialized = false;

Utilities::Utilities()
{}

void Utilities::writeRegistryEntry(const RegistryEntry& entry)
{
    QSettings settings(entry.node(), QSettings::NativeFormat);
    settings.setValue(entry.key(), entry.value());
}

bool Utilities::testRegistryEntry(const RegistryEntry& entry)
{
    QSettings settings(entry.node(), QSettings::NativeFormat);

    if (settings.value(entry.key()).toString() != entry.value())
    {
        QMessageBox::information(0, "Utilities::testRegistryEntry",
                                 entry.node() + "\r\n" +
                                 entry.key() + "\r\n" +
                                 entry.value() + "\r\n" +
                                 settings.value(entry.key()).toString());
        return false;
    }

    return true;
}

void Utilities::writeRegistryValue(const QString& node, const QString& attribute,
                                   const QString& value)
{
    QSettings settings(node, QSettings::NativeFormat);
    settings.setValue(attribute, value);
}

QString Utilities::readRegistryValue(const QString& node, const QString& attribute)
{
    QSettings settings(node, QSettings::NativeFormat);
    return settings.value(attribute).toString();
}


QList<RegistryEntry> Utilities::applicationRegistrationEntries()
{
    QList<RegistryEntry> result;

// MyBrowserHTML document type

    QString HKLMSoftwareClasses = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Classes";

    result << RegistryEntry(HKLMSoftwareClasses + "\\" + DocumentName,
                            "URL Protocol",
                            "");

    result << RegistryEntry(HKLMSoftwareClasses + "\\" + DocumentName,
                            "",
                            DocumentDescription);

    result << RegistryEntry(HKLMSoftwareClasses + "\\" + DocumentName + "\\DefaultIcon",
                            "",
                            DocumentIcon);

    result << RegistryEntry(HKLMSoftwareClasses + "\\" + DocumentName + "\\shell\\open\\command",
                            "",
                            OpenCommand);

// Start menu application registration

    QString HKLMStartMenuInternet = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Clients\\StartMenuInternet";

//    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ExecutableName,
//                            "LocalizedString",
//                            ApplicationName);

//    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ExecutableName + "\\shell\\open\\command",
//                            "",
//                            ExecutablePath);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName,
                            "LocalizedString",
                            ApplicationName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName,
                            "",
                            ApplicationName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities",
                            "ApplicationName",
                            ApplicationName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities",
                            "ApplicationIcon",
                            MainIcon);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities",
                            "ApplicationDescription",
                            ApplicationDescription);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\FileAssociations",
                            ".xhtml",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\FileAssociations",
                            ".xht",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\FileAssociations",
                            ".shtml",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\FileAssociations",
                            ".html",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\FileAssociations",
                            ".htm",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\Startmenu",
                            "StartMenuInternet",
                            ApplicationName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\URLAssociations",
                            "https",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\Capabilities\\URLAssociations",
                            "http",
                            DocumentName);

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\DefaultIcon",
                            "",
                            MainIcon);


    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\InstallInfo",
                            "IconsVisible",
                            "1");

    result << RegistryEntry(HKLMStartMenuInternet + "\\" + ApplicationName + "\\shell\\open\\command",
                            "",
                            ExecutablePath);

    return result;
}

QList<RegistryEntry> Utilities::defaultWebBrowserEntries()
{
    QList<RegistryEntry> result;

// set as default web browser

    QString HKLMStartMenuInternet = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Clients\\StartMenuInternet";
    result << RegistryEntry(HKLMStartMenuInternet,
                            "",
                            ApplicationName);

    QString HCUStartMenuInternet = "HKEY_CURRENT_USER\\Software\\Clients\\StartMenuInternet";
    result << RegistryEntry(HCUStartMenuInternet,
                            "",
                            ApplicationName);

    QString HCUSoftwareClasses = "HKEY_CURRENT_USER\\Software\\Classes";

    result << RegistryEntry(HCUSoftwareClasses + "\\http\\DefaultIcon",
                            "",
                            DocumentIcon);

    result << RegistryEntry(HCUSoftwareClasses + "\\http\\Shell\\open\\command",
                            "",
                            OpenCommand);

    result << RegistryEntry(HCUSoftwareClasses + "\\https\\DefaultIcon",
                            "",
                            DocumentIcon);

    result << RegistryEntry(HCUSoftwareClasses + "\\https\\Shell\\open\\command",
                            "",
                            OpenCommand);

    result << RegistryEntry(HCUSoftwareClasses + "\\.xhtml",
                            "",
                            DocumentName);

    result << RegistryEntry(HCUSoftwareClasses + "\\.xht",
                            "",
                            DocumentName);

    result << RegistryEntry(HCUSoftwareClasses + "\\.shtml",
                            "",
                            DocumentName);

    result << RegistryEntry(HCUSoftwareClasses + "\\.html",
                            "",
                            DocumentName);

    result << RegistryEntry(HCUSoftwareClasses + "\\.htm",
                            "",
                            DocumentName);

    return result;
}

bool Utilities::isRegisteredApplicastion()
{
    bool result = true;
    QList<RegistryEntry> entries = applicationRegistrationEntries();

    foreach (RegistryEntry entry, entries)
    {
        result = result && testRegistryEntry(entry);
    }

    return result;
}

void Utilities::registerApplication()
{
    if (isRegisteredApplicastion())
    {
        QMessageBox::information(0,
                                 "Utilities::registerApplication",
                                 "Already registered",
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
        return;
    }

    QList<RegistryEntry> entries = applicationRegistrationEntries();
    foreach (RegistryEntry entry, entries)
    {
        writeRegistryEntry(entry);
    }
}

bool Utilities::isDefault()
{
    if (!isRegisteredApplicastion())
    {
        return false;
    }

    QList<RegistryEntry> entries = defaultWebBrowserEntries();
    foreach (RegistryEntry entry, entries)
    {
        if (!testRegistryEntry(entry))
        {
            return false;
        }
    }

    if (QSysInfo::windowsVersion() > QSysInfo::WV_VISTA)
    {
        if (!coInitialized)
        {
            CoInitialize(NULL);
            coInitialized = true;
        }

        IApplicationAssociationRegistration* pAAR;

        HRESULT hr = CoCreateInstance(CLSID_ApplicationAssociationRegistration,
                                      NULL,
                                      CLSCTX_INPROC,
                                      IID_IApplicationAssociationRegistration,
                                      (void**)&pAAR);

        if (SUCCEEDED(hr))
        {
            BOOL isDefaultBrowser = true;
            pAAR->QueryAppIsDefaultAll(AL_EFFECTIVE,
                                       ApplicationName.toStdWString().c_str(),
                                       &isDefaultBrowser);

            qDebug() << "isDefaultBrowser" << isDefaultBrowser;

            return isDefaultBrowser;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void Utilities::setDefault()
{
    if (isDefault())
    {
        return;
    }

    if (!isRegisteredApplicastion())
    {
        registerApplication();
    }

    if (QSysInfo::windowsVersion() > QSysInfo::WV_VISTA)
    {
        if (!coInitialized)
        {
            CoInitialize(NULL);
            coInitialized = true;
        }

        IApplicationAssociationRegistration* aar;

        CLSID clsid = __uuidof(IApplicationAssociationRegistration);
        HRESULT result = CoCreateInstance(CLSID_ApplicationAssociationRegistration,
                                          NULL, CLSCTX_INPROC, clsid, (void**)&aar);

        if (!SUCCEEDED(result))
        {
            return;
        }

        aar->SetAppAsDefaultAll(ApplicationName.toStdWString().c_str());

        aar->Release();
    }

    QList<RegistryEntry> entries = defaultWebBrowserEntries();
    foreach (RegistryEntry entry, entries)
    {
        writeRegistryEntry(entry);
    }
    // send windows notification
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
}
