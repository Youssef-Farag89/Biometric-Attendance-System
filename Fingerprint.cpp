#include "../headers/Fingerprint.h"

Fingerprint::Fingerprint() 
    : fingerprintId(0), userId(0), fingerprintData(""), fingerIndex(0) {}

Fingerprint::Fingerprint(int fingerId, int uid, const QString &data, int index)
    : fingerprintId(fingerId), userId(uid), fingerprintData(data), fingerIndex(index) {}

// Getters
int Fingerprint::getFingerprintId() const { return fingerprintId; }
int Fingerprint::getUserId() const { return userId; }
QString Fingerprint::getFingerprintData() const { return fingerprintData; }
int Fingerprint::getFingerIndex() const { return fingerIndex; }

// Setters
void Fingerprint::setFingerprintId(int id) { fingerprintId = id; }
void Fingerprint::setUserId(int uid) { userId = uid; }
void Fingerprint::setFingerprintData(const QString &data) { fingerprintData = data; }
void Fingerprint::setFingerIndex(int index) { fingerIndex = index; }

bool Fingerprint::matchFingerprint(const QString &scannedData)
{
    return fingerprintData == scannedData;
}