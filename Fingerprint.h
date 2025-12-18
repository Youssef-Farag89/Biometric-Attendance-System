#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <QString>

class Fingerprint
{
private:
    int fingerprintId;
    int userId;
    QString fingerprintData;
    int fingerIndex;

public:
    Fingerprint();
    Fingerprint(int fingerId, int userId, const QString &data, int index);

    // Getters
    int getFingerprintId() const;
    int getUserId() const;
    QString getFingerprintData() const;
    int getFingerIndex() const;

    // Setters
    void setFingerprintId(int id);
    void setUserId(int uid);
    void setFingerprintData(const QString &data);
    void setFingerIndex(int index);

    bool matchFingerprint(const QString &scannedData);
};

#endif // FINGERPRINT_H