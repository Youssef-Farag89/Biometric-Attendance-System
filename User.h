#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    int userId;
    QString name;
    QString email;
    QString department;
    bool isActive;

public:
    User();
    User(int id, const QString &name, const QString &email, const QString &dept);

    // Getters
    int getUserId() const;
    QString getName() const;
    QString getEmail() const;
    QString getDepartment() const;
    bool getIsActive() const;

    // Setters
    void setUserId(int id);
    void setName(const QString &name);
    void setEmail(const QString &email);
    void setDepartment(const QString &dept);
    void setIsActive(bool active);
};

#endif // USER_H