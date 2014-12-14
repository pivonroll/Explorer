#include "networkutils.h"

#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>

namespace NetworkLocations {

QList<QNetworkAddressEntry> NetworkUtils::getLocalHostIPAddresses()
{
    QList<QNetworkAddressEntry> addresses;

    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        foreach (const QNetworkAddressEntry &addressEntry, interface.addressEntries()) {
            if (addressEntry.ip() != QHostAddress(QHostAddress::LocalHost) && addressEntry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                addresses << addressEntry;
        }
    }

    return addresses;
}

quint32 NetworkUtils::subNetStartIpAddress(quint32 ipAddress, quint32 subNetMask)
{
    return ipAddress & subNetMask + 1;
}

quint32 NetworkUtils::subNetEndIpAddress(quint32 ipAddress, quint32 subNetMask)
{
    return (~subNetMask) | subNetStartIpAddress(ipAddress, subNetMask);
}

} // namespace NetworkLocations
