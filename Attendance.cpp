#include "../headers/Attendance.h"
#include <QDateTime>
#include <QTime>

AttendanceRecord::AttendanceRecord() 
    : recordId(0), userId(0), date(""), checkInTime(""), checkOutTime(""), status("Absent") {}

AttendanceRecord::AttendanceRecord(int recID, int uid, const QString &d)
    : recordId(recID), userId(uid), date(d), checkInTime(""), checkOutTime(""), status("Absent") {}

// Getters
int AttendanceRecord::getRecordId() const { return recordId; }
int AttendanceRecord::getUserId() const { return userId; }
QString AttendanceRecord::getDate() const { return date; }
QString AttendanceRecord::getCheckInTime() const { return checkInTime; }
QString AttendanceRecord::getCheckOutTime() const { return checkOutTime; }
QString AttendanceRecord::getStatus() const { return status; }

// Setters
void AttendanceRecord::setRecordId(int id) { recordId = id; }
void AttendanceRecord::setUserId(int uid) { userId = uid; }
void AttendanceRecord::setDate(const QString &d) { date = d; }
void AttendanceRecord::setCheckInTime(const QString &time) { checkInTime = time; }      // دي
void AttendanceRecord::setCheckOutTime(const QString &time) { checkOutTime = time; }    // ودي
void AttendanceRecord::setStatus(const QString &s) { status = s; }

void AttendanceRecord::markCheckIn()
{
    QTime currentTime = QTime::currentTime();
    checkInTime = currentTime.toString("hh:mm:ss");
    
    // Consider late after 9:00 AM
    if (currentTime > QTime(9, 0, 0)) {
        status = "Late";
    } else {
        status = "Present";
    }
    
    date = QDate::currentDate().toString("yyyy-MM-dd");
}

QString AttendanceRecord::markCheckOut()
{
    QTime currentTime = QTime::currentTime();
    checkOutTime = currentTime.toString("hh:mm:ss");
    return checkOutTime;
}
