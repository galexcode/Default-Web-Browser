#ifndef UTILITIES_H
#define UTILITIES_H


#include <QSet>

#include "RegistryEntry.h"

class QString;

class Utilities
{
public:
    Utilities();

private:
    static void writeRegistryEntry(const RegistryEntry& entry);
    static bool testRegistryEntry(const RegistryEntry& entry);

    static void writeRegistryValue(const QString& node, const QString& attribute,
                                   const QString& value);
    static QString readRegistryValue(const QString& node, const QString& attribute);

    static QStringList applicationRegistrationEntriesList();
    static QList<RegistryEntry> applicationRegistrationEntries();
    static QList<RegistryEntry> defaultWebBrowserEntries();

    static bool isRegisteredApplicastion();
    static void registerApplication();

public:
    static bool isDefault();
    static void setDefault();
};

#endif // UTILITIES_H
