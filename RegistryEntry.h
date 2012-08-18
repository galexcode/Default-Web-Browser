#ifndef REGISTRYENTRY_H
#define REGISTRYENTRY_H

#include <QDebug>
#include <QString>

class RegistryEntry
{
private:
    QString mNode;
    QString mKey;
    QString mValue;

public:
    RegistryEntry();
    RegistryEntry(const QString& node, const QString& key, const QString& value);

    QString node() const;
    QString key() const;
    QString value() const;

    void setNode(const QString& node);
    void setKey(const QString& key);
    void setValue(const QString& value);
};

Q_DECLARE_METATYPE(RegistryEntry)

QDebug operator<<(QDebug dbg, const RegistryEntry& registryEntry);

#endif // REGISTRYENTRY_H
