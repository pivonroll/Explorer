#ifndef CORE_FILECOPIER_H
#define CORE_FILECOPIER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE

namespace Core {

class FileCopier : public QObject
{
    Q_OBJECT
public:
    explicit FileCopier(const QString &fromPath, const QString &toPath, QObject *parent = 0);

    void start();

    QString fromPath() const;
    QString toPath() const;

signals:
    void bytesWritten(qint64 bytes);
    void started();
    void finished();
    void error();
    void stopped();

private:
    QFile *m_fromFile;
    QFile *m_toFile;
    QString m_fromPath;
    QString m_toPath;
};

} // namespace Core

#endif // CORE_FILECOPIER_H
