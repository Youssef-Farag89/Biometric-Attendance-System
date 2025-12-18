#ifndef SCANNERDEVICE_H
#define SCANNERDEVICE_H

#include <QString>

class ScannerDevice
{
private:
    int deviceId;
    QString deviceName;

public:
    ScannerDevice(int id, const QString &name);
    QString scanFingerprint();
    int getId() const;
    QString getName() const;
};

#endif // SCANNERDEVICE_H