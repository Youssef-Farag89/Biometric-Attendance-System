#include "../headers/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("biometric.db");
}
bool DatabaseManager::openDatabase()
{
    if (!m_database.open()) {
        qDebug() << "Error: Could not open database:" << m_database.lastError();
        return false;
    }

    createTables();
    return true;
}


void DatabaseManager::createTables()
{
    QSqlQuery query;

    // Create Users table   (EDITED BY YOUSSEF WAEL)
    query.exec("CREATE TABLE IF NOT EXISTS Users ("
               "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "email TEXT UNIQUE NOT NULL, "
               "department TEXT, "
               "password TEXT DEFAULT '', "
               "is_active INTEGER DEFAULT 1)");



    // Create Attendance table
    query.exec("CREATE TABLE IF NOT EXISTS Attendance ("
               "record_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER NOT NULL, "
               "check_in_time TEXT, "
               "check_out_time TEXT, "
               "date TEXT NOT NULL, "
               "status TEXT, "
               "FOREIGN KEY(user_id) REFERENCES Users(user_id))");

    // Create Fingerprints table
    query.exec("CREATE TABLE IF NOT EXISTS Fingerprints ("
               "fingerprint_id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER NOT NULL, "
               "fingerprint_data TEXT NOT NULL, "
               "finger_index INTEGER, "
               "FOREIGN KEY(user_id) REFERENCES Users(user_id))");

    // Insert sample data
    query.exec("INSERT OR IGNORE INTO Users (name, email, department) VALUES "
               "('Ahmed Mohamed', 'ahmed@company.com', 'IT'), "
               "('Sara Mahmoud', 'sara@company.com', 'HR'), "
               "('Ali Hassan', 'ali@company.com', 'Finance')");
}

// User operations
bool DatabaseManager::addUser(const User &user)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Users (name, email, department) VALUES (?, ?, ?)");
    query.addBindValue(user.getName());
    query.addBindValue(user.getEmail());
    query.addBindValue(user.getDepartment());

    return query.exec();
}

QList<User> DatabaseManager::getAllUsers()
{
    QList<User> users;
    QSqlQuery query("SELECT * FROM Users WHERE is_active = 1");

    while (query.next()) {
        User user;
        user.setUserId(query.value("user_id").toInt());
        user.setName(query.value("name").toString());
        user.setEmail(query.value("email").toString());
        user.setDepartment(query.value("department").toString());
        users.append(user);
    }

    return users;
}

// DELETING USERS (BY YOUSSEF WAEL)
bool DatabaseManager::deleteUserById(int userId)
{
    QSqlQuery query;

    query.prepare("DELETE FROM Fingerprints WHERE user_id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) return false;

    query.prepare("DELETE FROM Attendance WHERE user_id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) return false;

    query.prepare("DELETE FROM Users WHERE user_id = :id");
    query.bindValue(":id", userId);
    return query.exec();
}



// password operations (ADDED BY YOUSSEF WAEL)
bool DatabaseManager::setUserPassword(int userId, const QString &password) {
    QSqlQuery query;
    query.prepare("UPDATE Users SET password = ? WHERE user_id = ?");
    query.addBindValue(password);
    query.addBindValue(userId);
    return query.exec();
}

QString DatabaseManager::getUserPassword(int userId) {
    QSqlQuery query;
    query.prepare("SELECT password FROM Users WHERE user_id = ?");
    query.addBindValue(userId);
    if (query.exec() && query.next()) {
        return query.value("password").toString();
    }
    return "";
}

QString DatabaseManager::getUsername(int userId)  {
    QSqlQuery query;
    query.prepare("SELECT name FROM users WHERE user_id = ?");
    query.addBindValue(userId);
    query.exec();
    query.next();
    return query.value("name").toString();
}


// Attendance operations
bool DatabaseManager::addAttendanceRecord(const AttendanceRecord &record)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Attendance (user_id, check_in_time, date, status) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(record.getUserId());
    query.addBindValue(record.getCheckInTime());
    query.addBindValue(record.getDate());
    query.addBindValue(record.getStatus());

    return query.exec();
}

QList<AttendanceRecord> DatabaseManager::getAttendanceRecords(int userId)
{
    QList<AttendanceRecord> records;
    QString sql = "SELECT * FROM Attendance";

    if (userId != -1) {
        sql += " WHERE user_id = " + QString::number(userId);
    }

    QSqlQuery query(sql);

    while (query.next()) {
        AttendanceRecord record;
        record.setRecordId(query.value("record_id").toInt());
        record.setUserId(query.value("user_id").toInt());
        record.setDate(query.value("date").toString());
        record.setCheckInTime(query.value("check_in_time").toString());
        record.setCheckOutTime(query.value("check_out_time").toString());
        record.setStatus(query.value("status").toString());
        records.append(record);
    }

    return records;
}

bool DatabaseManager::updateCheckOut(int recordId, const QString &checkOutTime)
{
    QSqlQuery query;
    query.prepare("UPDATE Attendance SET check_out_time = ? WHERE record_id = ?");
    query.addBindValue(checkOutTime);
    query.addBindValue(recordId);

    return query.exec();
}

// Fingerprint operations
bool DatabaseManager::addFingerprint(const Fingerprint &fp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Fingerprints (user_id, fingerprint_data, finger_index) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(fp.getUserId());
    query.addBindValue(fp.getFingerprintData());
    query.addBindValue(fp.getFingerIndex());

    return query.exec();
}




QList<Fingerprint> DatabaseManager::getFingerprints(int userId)
{
    QList<Fingerprint> fingerprints;
    QSqlQuery query;
    query.prepare("SELECT * FROM Fingerprints WHERE user_id = ?");
    query.addBindValue(userId);

    if (query.exec()) {
        while (query.next()) {
            Fingerprint fp;
            fp.setFingerprintId(query.value("fingerprint_id").toInt());
            fp.setUserId(query.value("user_id").toInt());
            fp.setFingerprintData(query.value("fingerprint_data").toString());
            fp.setFingerIndex(query.value("finger_index").toInt());
            fingerprints.append(fp);
        }
    }

    return fingerprints;
}

void DatabaseManager::closeDatabase()
{
    m_database.close();
}
