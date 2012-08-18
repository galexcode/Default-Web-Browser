#include "UtilitiesMac.h"

#include <QDebug>
#include <QString>
#include <QStringList>
#include <ApplicationServices/ApplicationServices.h>

QString bundleIdentifier = "com.yourcompany.defaultwebbrowser";
QString contentTypes = "public.html;public.xhtml;public.url";
QString urlSchemes = "http;https";

void setBufferFromCFString(QString& qs, CFStringRef cfs)
{
   if (!cfs)
   {
      return;
   }

   CFIndex size = CFStringGetLength(cfs);
   UniChar fixedSizeBuffer[1024];
   UniChar* buffer;

   if (size > (CFIndex)(sizeof(fixedSizeBuffer) / sizeof(UniChar)))
   {
      buffer = (UniChar*)malloc(size* sizeof(UniChar));
   }
   else
   {
      buffer = fixedSizeBuffer;
   }

   CFStringGetCharacters(cfs, CFRangeMake(0, size), buffer);

   qs.setUnicode((const QChar*)buffer, (uint)size);

   if (buffer != fixedSizeBuffer)
   {
      free(buffer);
   }
}

QString qStringfromCFString(CFStringRef cfs)
{
   QString qs;
   setBufferFromCFString(qs, cfs);
   return qs;
}

CFStringRef cfStringRefFromQString(const QString& qString)
{
    return CFStringCreateWithCharacters(0, reinterpret_cast<const UniChar *>(qString.unicode()),
                                        qString.length());
}

Utilities::Utilities()
{}

bool Utilities::isDefault()
{
    foreach (QString urlScheme, urlSchemes.split(";"))
    {
        CFStringRef cfUrlScheme = cfStringRefFromQString(urlScheme);
        CFStringRef cfResult = LSCopyDefaultHandlerForURLScheme(cfUrlScheme);

        QString resultString = qStringfromCFString(cfResult);

        qDebug() << urlScheme << resultString;

        if (resultString != bundleIdentifier)
        {
            return false;
        }
    }

    foreach (QString contentType, contentTypes.split(";"))
    {
        CFStringRef cfContentType = cfStringRefFromQString(contentType);
        CFStringRef cfResult = LSCopyDefaultRoleHandlerForContentType(cfContentType, kLSRolesViewer);

        QString resultString = qStringfromCFString(cfResult);

        qDebug() << contentType << resultString;

        if (resultString != bundleIdentifier)
        {
            return false;
        }
    }

    return true;
}

void Utilities::setDefault()
{
    foreach (QString contentType, contentTypes.split(";"))
    {
        LSSetDefaultRoleHandlerForContentType(cfStringRefFromQString(contentType),
                                              kLSRolesViewer,
                                              cfStringRefFromQString(bundleIdentifier));
    }

    foreach (QString urlScheme, urlSchemes.split(";"))
    {
        LSSetDefaultHandlerForURLScheme(cfStringRefFromQString(urlScheme),
                                        cfStringRefFromQString(bundleIdentifier));
    }
}
