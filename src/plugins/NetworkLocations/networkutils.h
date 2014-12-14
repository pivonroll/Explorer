#ifndef NETWORKLOCATIONS_LOCALHOSTSUPPORT_H
#define NETWORKLOCATIONS_LOCALHOSTSUPPORT_H

#include <QNetworkAddressEntry>

namespace NetworkLocations {

namespace NetworkUtils
{
    QList<QNetworkAddressEntry> getLocalHostIPAddresses();

    quint32 subNetStartIpAddress(quint32 ipAddress, quint32 subNetMask);
    quint32 subNetEndIpAddress(quint32 ipAddress, quint32 subNetMask);

} // namespace NetworkUtils
} // namespace NetworkLocations

#endif // NETWORKLOCATIONS_LOCALHOSTSUPPORT_H
