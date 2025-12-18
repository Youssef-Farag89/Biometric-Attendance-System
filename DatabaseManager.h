#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include "User.h"
#include "Attendance.h"
#include "Fingerprint.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    bool openDatabase();
    void closeDatabase();

    // User operations (DELETE ADDED BY YOUSSEF WAEL)
    bool addUser(const User &user);
    bool deleteUserById(int userId);
    QList<User> getAllUsers();

    // password operations (BY YOUSSEF WAEL)
    bool setUserPassword(int userId, const QString &password);
    QString getUserPassword(int userId);

    QString getUsername(int userId);

    // Attendance operations
    bool addAttendanceRecord(const AttendanceRecord &record);
    QList<AttendanceRecord> getAttendanceRecords(int userId = -1);
    bool updateCheckOut(int recordId, const QString &checkOutTime);



    // Fingerprint operations
    bool addFingerprint(const Fingerprint &fp);
    QList<Fingerprint> getFingerprints(int userId);

private:
    QSqlDatabase m_database;
    void createTables();
};

#endif // DATABASEMANAGER_H
