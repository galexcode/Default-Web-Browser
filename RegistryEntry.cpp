#include "RegistryEntry.h"

#include <QDebug>

RegistryEntry::RegistryEntry()
{
    mNode = "";
    mKey = "";
    mValue = "";
}

RegistryEntry::RegistryEntry(const QString& path, const QString& key,
                             const QString& value)
{
    mNode = path;
    mKey = key;
    mValue = value;
}

QString RegistryEntry::node() const
{
    return mNode;
}

QString RegistryEntry::key() const
{
    return mKey;
}

QString RegistryEntry::value() const
{
    return mValue;
}

void RegistryEntry::setNode(const QString& path)
{
    mNode = path;
}

void RegistryEntry::setKey(const QString& key)
{
    mKey = key;
}

void RegistryEntry::setValue(const QString& value)
{
    mValue = value;
}

QDebug operator<<(QDebug dbg, const RegistryEntry& registryEntry)
{
    QString message = QString("\"%1\" \"%2\" = \"%3\"")
            .arg(registryEntry.node())
            .arg(registryEntry.key())
            .arg(registryEntry.value());

    dbg.nospace() << message;

    return dbg.maybeSpace();
}
