#include "networkscanner.h"
#include "networkutils.h"

namespace NetworkLocations {

QList<NetworkScanner *> NetworkScanner::m_instanceList = QList<NetworkScanner *>();

void NetworkScanner::lookupHosts(QObject *receiver, const char *member)
{
    if (!receiver || !member)
        return;

    NetworkScanner *scanner = new NetworkScanner;
    m_instanceList.append(scanner);

    scanner->connect(scanner, SIGNAL(hostFound(QHostInfo)), receiver, member);
    scanner->start();
}

NetworkScanner::NetworkScanner()
{
    m_ipAddressRegExp = QRegExp("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
}

void NetworkScanner::start()
{
    QList<QNetworkAddressEntry> addresses = NetworkUtils::getLocalHostIPAddresses();

    foreach (const QNetworkAddressEntry &address, addresses)
        start(address.ip().toIPv4Address(), address.netmask().toIPv4Address());
}

void NetworkScanner::start(const QString &address, const QString &subnetMask)
{
    start(QHostAddress(address).toIPv4Address(), QHostAddress(subnetMask).toIPv4Address());
}

void NetworkScanner::start(quint32 address, quint32 subnetMask)
{
    quint32 startIp = NetworkUtils::subNetStartIpAddress(address, subnetMask);
    quint32 endIp = NetworkUtils::subNetEndIpAddress(address, subnetMask);

    while (startIp <= endIp) {
        start(startIp);
        ++startIp;
    }
}

void NetworkScanner::start(const QString &address)
{
    QHostInfo::lookupHost(address, this, SLOT(onHostLooked(QHostInfo)));
}

void NetworkScanner::start(quint32 address)
{
    start(QHostAddress(address).toString());
}

void NetworkScanner::onHostLooked(QHostInfo info)
{
    if (info.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << info.errorString();
        return;
    }

    if (!m_ipAddressRegExp.exactMatch(info.hostName()))
        return;

    emit hostFound(info);

    foreach (const QHostAddress &address, info.addresses())
        qDebug() << "Found address:" << address.toString();
}

} // namespace NetworkLocations
