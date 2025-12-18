#include "../headers/ScannerDevice.h"
#include <QRandomGenerator>

ScannerDevice::ScannerDevice(int id, const QString &name)
    : deviceId(id), deviceName(name) {}

QString ScannerDevice::scanFingerprint()
{
    // Simulate fingerprint scanning
    int randomNum = QRandomGenerator::global()->bounded(10000);
    return "FP_SCAN_" + QString::number(deviceId) + "_" + QString::number(randomNum);
}

int ScannerDevice::getId() const { return deviceId; }
QString ScannerDevice::getName() const { return deviceName; }