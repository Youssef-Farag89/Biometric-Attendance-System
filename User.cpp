#include "../headers/User.h"

User::User() : userId(0), name(""), email(""), department(""), isActive(true) {}

User::User(int id, const QString &name, const QString &email, const QString &dept)
    : userId(id), name(name), email(email), department(dept), isActive(true) {}

// Getters
int User::getUserId() const { return userId; }
QString User::getName() const { return name; }
QString User::getEmail() const { return email; }
QString User::getDepartment() const { return department; }
bool User::getIsActive() const { return isActive; }

// Setters
void User::setUserId(int id) { userId = id; }
void User::setName(const QString &n) { name = n; }
void User::setEmail(const QString &e) { email = e; }
void User::setDepartment(const QString &dept) { department = dept; }
void User::setIsActive(bool active) { isActive = active; }