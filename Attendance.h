#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QString>

class AttendanceRecord
{
private:
    int recordId;
    int userId;
    QString date;
    QString checkInTime;
    QString checkOutTime;
    QString status;

public:
    AttendanceRecord();
    AttendanceRecord(int recID, int uid, const QString &d);

    // Getters
    int getRecordId() const;
    int getUserId() const;
    QString getDate() const;
    QString getCheckInTime() const;
    QString getCheckOutTime() const;
    QString getStatus() const;

    // Setters
    void setRecordId(int id);
    void setUserId(int uid);
    void setDate(const QString &d);
    void setCheckInTime(const QString &time);
    void setCheckOutTime(const QString &time);
    void setStatus(const QString &s);

    // Operations
    void markCheckIn();
    QString markCheckOut();
};

#endif // ATTENDANCE_H
