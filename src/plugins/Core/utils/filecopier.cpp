#include "filecopier.h"

#include <QFile>

namespace Core {

FileCopier::FileCopier(const QString &fromPath, const QString &toPath, QObject *parent) :
    QObject(parent),
    m_fromPath(fromPath),
    m_toPath(toPath)
{
}

void FileCopier::start()
{
    m_fromFile = new QFile(fromPath, this);
    m_toFile = new QFile(toPath, this);

    connect(m_toFile, SIGNAL(bytesWritten(qint64)), this, SIGNAL(bytesWritten(qint64)));
    m_fromFile->copy(m_toPath);

    emit started();
}

QString FileCopier::fromPath() const
{
    return m_fromPath;
}

QString FileCopier::toPath() const
{
    return m_toPath;
}

} // namespace Core
