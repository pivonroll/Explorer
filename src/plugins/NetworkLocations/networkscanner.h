#ifndef NETWORKLOCATIONS_NETWORKSCANNER_H
#define NETWORKLOCATIONS_NETWORKSCANNER_H

#include <QObject>
#include <QHostInfo>

namespace NetworkLocations {

class NetworkScanner : public QObject
{
    Q_OBJECT

public:
    static void lookupHosts(QObject *receiver, const char *member);

    NetworkScanner();

    void start();
    void start(const QString &address, const QString &subnetMask);
    void start(quint32 address, quint32 subnetMask);
    void start(const QString &address);
    void start(quint32 address);

signals:
    void hostFound(QHostInfo);

private slots:
    void onHostLooked(QHostInfo info);

private:
    QRegExp m_ipAddressRegExp;

    static QList<NetworkScanner *> m_instanceList;
};

} // namespace NetworkLocations

#endif // NETWORKLOCATIONS_NETWORKSCANNER_H
