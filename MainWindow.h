#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFormLayout>
#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QScrollArea>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QInputDialog>
#include <QSoundEffect>
#include <QUrl>
#include "DatabaseManager.h"
#include "User.h"
#include "Attendance.h"
#include "Fingerprint.h"
#include "ScannerDevice.h"
#include "User.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showLoginScreen();
    void showDashboard();
    void showUsersManagement();
    void showAttendanceScreen();
    void showFingerprintRegistration();
    void showCreditsScreen();

    void showReportsScreen();
    void generateDailyReport();
    void generateUserReport();
    void generateMonthlyReport();
    
    void setUserPassword();
    void deleteUser();

    void handleLogin();
    void addNewUser();
    void registerFingerprint();
    void markCheckIn();
    void markCheckOut();
    void refreshUsersList();
    void refreshAttendanceList();

private:
    void setupUI();
    void createLoginScreen();
    void createDashboard();
    void createUsersScreen();
    void createAttendanceScreen();
    void createFingerprintScreen();
    void createReportsScreen();
    void createCreditsScreen();

    // USER MODES (ADDED BY YOUSSEF WAEL)
    void openAdminMode();
    void openEmployeeMode(const User &user);
    void playCustomMessageBox(const QString &title, const QString &text, const QString &soundFile);
    void playCustomInfoMessageBox(const QString &title, const QString &text, const QString &resourcePath);


    // (ADDED BY YOUSSEF WAEL)
    User loggedInUser;

    DatabaseManager *dbManager;
    QStackedWidget *stackedWidget;
    QPushButton *setPasswordBtn;
    
    // Login Screen
    QWidget *loginScreen;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    
    // Dashboard
    QWidget *dashboardScreen;
    
    // Users Management
    QWidget *usersScreen;
    QTableWidget *usersTable;
    QListWidget *usersList;
    QLineEdit *userNameEdit;
    QLineEdit *userEmailEdit;
    QLineEdit *userDeptEdit;
    
    // Attendance
    QWidget *attendanceScreen;
    QTableWidget *attendanceTable;
    QComboBox *userComboBox;
    
    // Fingerprint
    QWidget *fingerprintScreen;
    QComboBox *fpUserComboBox;
    QComboBox *fingerIndexComboBox;

    QWidget *reportsScreen;

    // Creating Avatar css for Credits tab
    QLabel* createAvatar(const QString &path);
    QWidget *creditsScreen;


};

#endif // MAINWINDOW_H
