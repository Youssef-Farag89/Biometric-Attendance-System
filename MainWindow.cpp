#include "../headers/MainWindow.h"
#include "../headers/ScannerDevice.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    dbManager = new DatabaseManager(this);
    setupUI();
    showLoginScreen();

    if (!dbManager->openDatabase()) {
        QMessageBox::critical(this, "Error", "Cannot open database!");
    }
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    setWindowTitle("Biometric Attendance System");
    setFixedSize(1000, 700);
    
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    createLoginScreen();
    createDashboard();
    createUsersScreen();
    createAttendanceScreen();
    createFingerprintScreen();
    createReportsScreen();
    createCreditsScreen();

}
void MainWindow::createReportsScreen()
{
    reportsScreen = new QWidget;
    reportsScreen->setStyleSheet("background-color: #1e1e1e;");
    QVBoxLayout *mainLayout = new QVBoxLayout(reportsScreen);
    mainLayout->setContentsMargins(25, 20, 25, 20);

    QLabel *titleLabel = new QLabel(" Attendance Reports");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px; color: #2E86AB;");

    QVBoxLayout *btns = new QVBoxLayout(reportsScreen);

    QPushButton *dailyBtn = new QPushButton(" Daily Report");
    dailyBtn->setFixedWidth(500);
    QPushButton *userBtn = new QPushButton(" User Report");
    userBtn->setFixedWidth(500);
    QPushButton *monthlyBtn = new QPushButton(" Monthly Report");
    monthlyBtn->setFixedWidth(500);

    QString btnStyle = "QPushButton { padding: 10px; margin: 5px; }";
    dailyBtn->setStyleSheet(btnStyle);
    userBtn->setStyleSheet(btnStyle);
    monthlyBtn->setStyleSheet(btnStyle);

    QPushButton *backBtn = new QPushButton("Back");
    //backBtn->setStyleSheet(
    //    "QPushButton {padding: 8px; border-radius: 5px; background-color: #7f8c8d; color: white; font-weight: bold;}"
    //    "QPushButton:hover { background-color: #636e72; }"
    //    );
    backBtn->setFixedWidth(120);
    backBtn->setFixedHeight(36);

    btns->addWidget(dailyBtn);
    btns->addWidget(userBtn);
    btns->addWidget(monthlyBtn);
    btns->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(backBtn);
    mainLayout->addSpacing(130);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(btns);
    mainLayout->addStretch();

    connect(dailyBtn, &QPushButton::clicked, this, &MainWindow::generateDailyReport);
    connect(userBtn, &QPushButton::clicked, this, &MainWindow::generateUserReport);
    connect(monthlyBtn, &QPushButton::clicked, this, &MainWindow::generateMonthlyReport);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showDashboard);

    stackedWidget->addWidget(reportsScreen);
}
void MainWindow::showReportsScreen()
{
    if (reportsScreen) {
        stackedWidget->setCurrentWidget(reportsScreen);
    }
}

void MainWindow::generateDailyReport()
{
    QMessageBox::information(this, "Daily Report", "Daily report will be generated here");
}

void MainWindow::generateUserReport()
{
    QMessageBox::information(this, "User Report", "User report will be generated here");
}

void MainWindow::generateMonthlyReport()
{
    QMessageBox::information(this, "Monthly Report", "Monthly report will be generated here");
}


void MainWindow::createLoginScreen()
{
    loginScreen = new QWidget;
    loginScreen->setStyleSheet("background-color: #1e1e1e;");
    loginScreen->setObjectName("loginScreen");

    QVBoxLayout *layout = new QVBoxLayout(loginScreen);

    loginScreen->setStyleSheet(
        "#loginScreen "
        "{"
        "background-image: url(:/img/img/login_img.png);"
        "background-position: center;"
        "background-repeat: no-repeat;"
        "}"
        );


    QLabel *titleLabel = new QLabel("Biometric Attendance");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; margin: 20px;");


    QVBoxLayout *loginLayout = new QVBoxLayout;


    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Enter your User ID");
    usernameEdit->setMaximumWidth(300);
    usernameEdit->setMinimumHeight(36);

    // password (ADDED BY YOUSSEF WAEL)
    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Enter password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMaximumWidth(300);
    passwordEdit->setMinimumHeight(36);

    QVBoxLayout *btnLayout = new QVBoxLayout;

    //STYLE SHEETS (EDITED BY YOUSSEF WAEL)
    QPushButton *loginBtn = new QPushButton("Login");
    loginBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #4caf50;"     // green
        "color: white;"
        "padding: 12px 18px;"
        "border-radius: 6px;"
        "border: 1px solid #388e3c;"    // dark green لو احتجت منه تاني
        "font-weight: bold; font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "background-color: #388e3c;"
        "}"
        "QPushButton:disabled {"
        "background-color: #2e7d32;"
        "border: 1px solid #1b5e20;"
        "color: #aaa;"
        "}"
        );
        loginBtn->setMinimumWidth(126);
        loginBtn->setMinimumHeight(36);



    loginLayout->addWidget(usernameEdit);
    loginLayout->addWidget(passwordEdit);
    loginLayout->setAlignment(Qt::AlignCenter);

    btnLayout->addWidget(loginBtn);
    btnLayout->setAlignment(Qt::AlignCenter);


    layout->addSpacing(150);
    layout->addWidget(titleLabel);
    layout->addSpacing(40);
    layout->addLayout(loginLayout);
    layout->addSpacing(20);
    layout->addLayout(btnLayout);
    layout->addStretch();

    connect(loginBtn, &QPushButton::clicked, this, &MainWindow::handleLogin);

    stackedWidget->addWidget(loginScreen);
}

void MainWindow::createDashboard()
{
    dashboardScreen = new QWidget;
    dashboardScreen->setStyleSheet("background-color: #1e1e1e;");
    QVBoxLayout *layout = new QVBoxLayout(dashboardScreen);
    layout->setContentsMargins(25, 20, 25, 20);
    
    QLabel *titleLabel = new QLabel("Dashboard");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 35px; font-weight: bold; margin: 15px;");
    
    QPushButton *usersBtn = new QPushButton(" Manage Users");
    usersBtn->setMinimumWidth(600);
    QPushButton *attendanceBtn = new QPushButton(" Attendance");
    attendanceBtn->setMinimumWidth(600);
    QPushButton *fingerprintBtn = new QPushButton(" Fingerprints");
    fingerprintBtn->setMinimumWidth(600);
    QPushButton *reportsBtn = new QPushButton(" Reports (coming soon...)");      // البروجكت الجاي و عليك خير
    reportsBtn->setMinimumWidth(600);
    QPushButton *logoutBtn = new QPushButton("Logout");
    QPushButton *creditsBtn = new QPushButton(" Credits");
    creditsBtn->setMinimumWidth(600);



    QString buttonStyle = "QPushButton { text-align: left; padding: 26px; font-size: 20px; border: 3px solid #ccc; border-radius: 8px; margin: 8px;}"
                          "QPushButton:hover { "
                          "background-color: #3a3a3a;} ";
    usersBtn->setStyleSheet(buttonStyle);
    attendanceBtn->setStyleSheet(buttonStyle);
    fingerprintBtn->setStyleSheet(buttonStyle);
    reportsBtn->setStyleSheet(buttonStyle);
    creditsBtn->setStyleSheet(buttonStyle);
    logoutBtn->setStyleSheet(
        "QPushButton { "
        "background-color: #2b2b2b; "
        "color: white; "
        "padding: 8px 12px; "
        "border-radius: 6px; "
        "border: 1px solid #3a3a3a; "
        "} "
        "QPushButton:hover { "
        "background-color: #3a3a3a; "
        "} "
        "QPushButton:pressed { "
        "background-color: #222; "
        "} "
        );
    logoutBtn->setMinimumWidth(170);
    logoutBtn->setMinimumHeight(50);
    QHBoxLayout *backLayout = new QHBoxLayout;
    backLayout->addWidget(logoutBtn);
    backLayout->setAlignment(Qt::AlignRight);


    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(titleLabel);
    buttonsLayout->addWidget(usersBtn);
    buttonsLayout->addWidget(attendanceBtn);
    buttonsLayout->addWidget(fingerprintBtn);
    buttonsLayout->addWidget(reportsBtn);
    buttonsLayout->addWidget(creditsBtn);
    buttonsLayout->setAlignment(Qt::AlignCenter);


    layout->addLayout(backLayout);
    layout->addLayout(buttonsLayout);
    layout->addStretch();



    connect(logoutBtn, &QPushButton::clicked, this, &MainWindow::showLoginScreen);
    connect(usersBtn, &QPushButton::clicked, this, &MainWindow::showUsersManagement);
    connect(attendanceBtn, &QPushButton::clicked, this, &MainWindow::showAttendanceScreen);
    connect(fingerprintBtn, &QPushButton::clicked, this, &MainWindow::showFingerprintRegistration);
    connect(reportsBtn, &QPushButton::clicked, this, &MainWindow::showReportsScreen);
    connect(creditsBtn, &QPushButton::clicked,this, &MainWindow::showCreditsScreen);
    
    stackedWidget->addWidget(dashboardScreen);
}

// fully edited by meeee ;D
void MainWindow::createUsersScreen()
{
    usersScreen = new QWidget;
    usersScreen->setStyleSheet("background-color: #1e1e1e;");
    QVBoxLayout *layout = new QVBoxLayout(usersScreen);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(18);

    QLabel *titleLabel = new QLabel("Manage Users");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; margin-bottom: 15px;");

    QGroupBox *addUserGroup = new QGroupBox("Add New User");
    addUserGroup->setStyleSheet("font-weight: bold; font-size: 14px; padding: 10px;");
    QFormLayout *formLayout = new QFormLayout(addUserGroup);
    formLayout->setSpacing(10);

    userNameEdit = new QLineEdit;
    userEmailEdit = new QLineEdit;
    userDeptEdit = new QLineEdit;
    QString lineEditStyle = "padding: 6px; border: 1px solid #ccc; border-radius: 4px;";
    userNameEdit->setStyleSheet(lineEditStyle);
    userEmailEdit->setStyleSheet(lineEditStyle);
    userDeptEdit->setStyleSheet(lineEditStyle);

    formLayout->addRow("Name:", userNameEdit);
    formLayout->addRow("Email:", userEmailEdit);
    formLayout->addRow("Department:", userDeptEdit);

    QPushButton *addUserBtn = new QPushButton("Add User");
    addUserBtn->setFixedWidth(120);
    addUserBtn->setFixedHeight(33);

    usersTable = new QTableWidget;
    usersTable->setColumnCount(4);
    usersTable->setHorizontalHeaderLabels({"ID","Name","Email","Department"});
    usersTable->horizontalHeader()->setStretchLastSection(true);

    usersTable->verticalHeader()->setDefaultSectionSize(40);

    usersTable->setColumnWidth(0, 80);
    usersTable->setColumnWidth(1, 200);
    usersTable->setColumnWidth(2, 260);
    usersTable->setColumnWidth(3, 180);



    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->verticalHeader()->setVisible(false);


    // Set Password & Delete Buttons
    QPushButton *setPasswordBtn = new QPushButton("Set Password");
    setPasswordBtn->setFixedWidth(120);
    setPasswordBtn->setFixedHeight(33);

    QPushButton *deleteUserBtn = new QPushButton("Delete User");
    deleteUserBtn->setFixedWidth(120);
    deleteUserBtn->setFixedHeight(33);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(setPasswordBtn);
    buttonsLayout->addWidget(deleteUserBtn);
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->setSpacing(50);

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setFixedWidth(120);
    backBtn->setFixedHeight(33);

    QHBoxLayout *backLayout = new QHBoxLayout;
    backLayout->addWidget(backBtn);
    backLayout->setAlignment(Qt::AlignRight);

    layout->addLayout(backLayout);
    layout->addWidget(titleLabel);
    layout->addWidget(addUserGroup);
    layout->addWidget(addUserBtn, 0, Qt::AlignCenter);
    layout->addWidget(new QLabel("All Users:"));
    layout->addWidget(usersTable);
    layout->addLayout(buttonsLayout);


    connect(addUserBtn, &QPushButton::clicked, this, &MainWindow::addNewUser);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showDashboard);

    connect(setPasswordBtn, &QPushButton::clicked, this, &MainWindow::setUserPassword);

    connect(deleteUserBtn, &QPushButton::clicked, this, &MainWindow::deleteUser);

    stackedWidget->addWidget(usersScreen);
}



void MainWindow::createAttendanceScreen()
{
    attendanceScreen = new QWidget;
    attendanceScreen->setStyleSheet("background-color: #1e1e1e;");
    QVBoxLayout *layout = new QVBoxLayout(attendanceScreen);
    layout->setContentsMargins(25, 20, 25, 20);
    layout->setSpacing(15);

    QLabel *titleLabel = new QLabel("Attendance Management");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 23px; font-weight: bold; margin: 10px;");

    QHBoxLayout *userLayout = new QHBoxLayout;
    userLayout->addWidget(new QLabel("Select User:"));
    userComboBox = new QComboBox;
    userComboBox->setFixedWidth(205);
    userComboBox->setFixedHeight(30);
    userLayout->addWidget(userComboBox);
    userLayout->setAlignment(Qt::AlignLeft);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *checkInBtn = new QPushButton("Check-In");
    checkInBtn->setFixedWidth(200);
    checkInBtn->setFixedHeight(30);
    QPushButton *checkOutBtn = new QPushButton("Check-Out");
    checkOutBtn->setFixedWidth(200);
    checkOutBtn->setFixedHeight(30);
    QPushButton *refreshBtn = new QPushButton("Refresh");
    refreshBtn->setFixedWidth(200);
    refreshBtn->setFixedHeight(30);

    checkInBtn->setStyleSheet("background-color: #4CAF50; color: white;");
    checkOutBtn->setStyleSheet("background-color: #FF9800; color: white;");

    btnLayout->addWidget(checkInBtn);
    btnLayout->addWidget(checkOutBtn);
    btnLayout->addWidget(refreshBtn);

    attendanceTable = new QTableWidget;
    attendanceTable->setColumnCount(5);
    attendanceTable->setHorizontalHeaderLabels({"ID", "User", "Date", "Check-In", "Status"});
    attendanceTable->horizontalHeader()->setStretchLastSection(true);

    attendanceTable->verticalHeader()->setDefaultSectionSize(40);

    attendanceTable->setColumnWidth(0, 80);
    attendanceTable->setColumnWidth(1, 230);
    attendanceTable->setColumnWidth(2, 230);
    attendanceTable->setColumnWidth(3,150);

    attendanceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    attendanceTable->setSelectionMode(QAbstractItemView::SingleSelection);
    attendanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    attendanceTable->verticalHeader()->setVisible(false);

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setFixedWidth(120);
    backBtn->setFixedHeight(30);

    backBtn->setObjectName("backBtn");
    QHBoxLayout *backLayout = new QHBoxLayout;
    backLayout->addWidget(backBtn);
    backLayout->setAlignment(Qt::AlignCenter);


    layout->addWidget(titleLabel);
    layout->addLayout(userLayout);
    layout->addLayout(btnLayout);
    layout->addWidget(attendanceTable);
    layout->addLayout(backLayout);

    connect(checkInBtn, &QPushButton::clicked, this, &MainWindow::markCheckIn);
    connect(checkOutBtn, &QPushButton::clicked, this, &MainWindow::markCheckOut);
    connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::refreshAttendanceList);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showDashboard);

    stackedWidget->addWidget(attendanceScreen);
}

void MainWindow::createFingerprintScreen()
{
    fingerprintScreen = new QWidget;
    fingerprintScreen->setStyleSheet("background-color: #1e1e1e;");
    QVBoxLayout *layout = new QVBoxLayout(fingerprintScreen);
    layout->setSpacing(15);
    layout->setContentsMargins(25, 20, 25, 60);


    QLabel *titleLabel = new QLabel("Fingerprint Registration");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    titleLabel->setContentsMargins(10, 130, 10, 10);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->setSpacing(10);

    fpUserComboBox = new QComboBox;
    fpUserComboBox->setFixedHeight(36);
    fpUserComboBox->setFixedWidth(450);

    fingerIndexComboBox = new QComboBox;
    fingerIndexComboBox->setFixedHeight(36);
    fingerIndexComboBox->setFixedWidth(450);

    for (int i = 1; i <= 10; i++) {
        fingerIndexComboBox->addItem("Finger " + QString::number(i));
    }

    formLayout->addRow("User:", fpUserComboBox);
    formLayout->addRow("Finger:", fingerIndexComboBox);
    formLayout->setFormAlignment(Qt::AlignCenter);

    QPushButton *registerBtn = new QPushButton("Register Fingerprint");
    registerBtn->setFixedHeight(36);
    registerBtn->setFixedWidth(175);

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setFixedHeight(36);
    backBtn->setFixedWidth(120);


    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(registerBtn);
    btnLayout->addStretch();

    QVBoxLayout *backLayout = new QVBoxLayout;
    backLayout->addWidget(backBtn);

    layout->addLayout(backLayout);
    layout->setSpacing(100);
    layout->addWidget(titleLabel);
    layout->setSpacing(30);
    layout->addLayout(formLayout);
    layout->addLayout(btnLayout);
    layout->addStretch();



    connect(registerBtn, &QPushButton::clicked, this, &MainWindow::registerFingerprint);
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showDashboard);

    stackedWidget->addWidget(fingerprintScreen);
}

// (BY YOUSSEF WAEL) ;D
void MainWindow::createCreditsScreen()
{
    creditsScreen = new QWidget;
    creditsScreen->setStyleSheet("background-color: #1e1e1e;");

    QVBoxLayout *mainLayout = new QVBoxLayout(creditsScreen);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *title = new QLabel("Project Credits");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 26px;"
        "font-weight: bold;"
        "color: white;"
        "margin-bottom: 15px;"
        );

    QVBoxLayout *listLayout = new QVBoxLayout;
    listLayout->setSpacing(15);

    // lamda function from cpc
    auto addPerson = [&](const QString &img,
                         const QString &name,
                         const QString &role)
    {
        QWidget *card = new QWidget;
        card->setStyleSheet(
            "background-color: #2b2b2b;"
            "border-radius: 10px;"
            "padding: 12px;"
            );

        QHBoxLayout *cardLayout = new QHBoxLayout(card);
        cardLayout->setSpacing(15);

        QLabel *avatar = createAvatar(img);

        QLabel *text = new QLabel(
            "<b style='color:white; font-size:15px;'>" + name + "</b><br>"
                "<span style='color:#b0b0b0;'>" + role + "</span>"
            );
        text->setWordWrap(true);

        cardLayout->addWidget(avatar);
        cardLayout->addWidget(text);
        cardLayout->addStretch();

        listLayout->addWidget(card);
    };

    addPerson(":/img/img/wael.png", "Youssef Wael",
              "Backend integration, UI design, Database integration");

    addPerson(":/img/img/farag.png", "Youssef Farag",
              "Backend integration, UI design");

    addPerson(":/img/img/mahmoud.png", "Youssef Mahmoud",
              "Backend logic and Classes Creation");

    addPerson(":/img/img/kemoo.png", "Kareem",
              "Backend logic , Database Creation");


    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget *container = new QWidget;
    container->setLayout(listLayout);
    scroll->setWidget(container);

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setFixedSize(120, 36);
    backBtn->setStyleSheet(
        "QPushButton { "
        "background-color: #2b2b2b; "
        "color: white; "
        "padding: 12px 18px; "
        "border-radius: 6px; "
        "border: 1px solid #3a3a3a; "
        "} "
        "QPushButton:hover { "
        "background-color: #3a3a3a; "
        "} "
        "QPushButton:pressed { "
        "background-color: #222; "
        "} "
        );

    QHBoxLayout *backLayout = new QHBoxLayout;
    backLayout->addStretch();
    backLayout->addWidget(backBtn);
    backLayout->addStretch();

    mainLayout->addWidget(title);
    mainLayout->addWidget(scroll);
    mainLayout->addLayout(backLayout);

    connect(backBtn, &QPushButton::clicked, this, &MainWindow::showDashboard);

    stackedWidget->addWidget(creditsScreen);
}



void MainWindow::handleLogin()
{
    QString idText = usernameEdit->text();

    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter your ID");
        return;
    }

    bool ok;
    int userId = idText.toInt(&ok);

    if (!ok) {
        playCustomMessageBox("Login Failed", "Invalid ID format","qrc:/sfx/sfx/sad_horn.wav");
        return;
    }

    // check if ID is registered
    QList<User> users = dbManager->getAllUsers();
    bool userExists = false;
    QString userName;

    // STORES USER NAME IN logged in user
    for (const User &user : users) {
        if (user.getUserId() == userId) {
            userExists = true;
            userName = user.getName();
            loggedInUser = user;
            break;
        }
    }

    if (!userExists) {
        playCustomMessageBox("Login Failed", "ID not registered in system","qrc:/sfx/sfx/sad_horn.wav");
        return;
    }

    //PASSWORD LOGIC (BY YOUSSEF WAEL)  dX
    QString enteredPassword = passwordEdit->text();
    QString storedPassword = dbManager->getUserPassword(userId);

    if (!storedPassword.isEmpty() && storedPassword != enteredPassword) {
        playCustomMessageBox("Login Failed", "Incorrect password","qrc:/sfx/sfx/not_welcome.wav");
        return;
    }


    playCustomInfoMessageBox("Login Success","Welcome " + userName + "!","qrc:/sfx/sfx/welcome.wav");


    //User mode (ADDED BY YOUSSEF WAEL ADMIN ID =12 )
    if (loggedInUser.getDepartment().toLower() == "admin") {
        openAdminMode();
    } else {
        openEmployeeMode(loggedInUser);
    }

    //showDashboard(); // NOT NEEDED بس احتياطي عشان لو عكت معاك و مسحت الادمن تخش من هنا
}

void MainWindow::openAdminMode()
{
    showDashboard();
}

void MainWindow::openEmployeeMode(const User &user)
{
    loggedInUser = user;
    showAttendanceScreen();
}


void MainWindow::showLoginScreen()
{
    stackedWidget->setCurrentWidget(loginScreen);
    usernameEdit->clear();
    passwordEdit->clear();
}

void MainWindow::showDashboard()
{
    stackedWidget->setCurrentWidget(dashboardScreen);
}

void MainWindow::showUsersManagement()
{
    refreshUsersList();
    stackedWidget->setCurrentWidget(usersScreen);
}

void MainWindow::showCreditsScreen()
{
    stackedWidget->setCurrentWidget(creditsScreen);
    // Play sound
    QSoundEffect *effect = new QSoundEffect(this);
    effect->setSource(QUrl("qrc:/sfx/sfx/credits.wav"));
    effect->setVolume(0.9f);
    effect->play();
}


// fully edited by youssef wael
void MainWindow::showAttendanceScreen()
{
    // Clear and populate user combo box
    userComboBox->clear();
    QList<User> users = dbManager->getAllUsers();

    if (loggedInUser.getDepartment().toLower() == "admin") {
        // Admin can see all users
        for (const User &user : users) {
            userComboBox->addItem(user.getName() + " (ID: " + QString::number(user.getUserId()) + ")", user.getUserId());
        }
        userComboBox->setEnabled(true);
    } else {
        // Employee can only see themselves
        userComboBox->addItem(loggedInUser.getName() + " (ID: " + QString::number(loggedInUser.getUserId()) + ")", loggedInUser.getUserId());
        userComboBox->setEnabled(false);
    }

    // Update back/logout button
    QPushButton *backBtn = attendanceScreen->findChild<QPushButton*>("backBtn");
    if (backBtn) {
        backBtn->disconnect();

        if (loggedInUser.getDepartment().toLower() == "admin") {
            backBtn->setText("Back");
            connect(backBtn, &QPushButton::clicked, this, &MainWindow::showDashboard);
        } else {
            backBtn->setText("Logout");
            connect(backBtn, &QPushButton::clicked, this, &MainWindow::showLoginScreen);
        }
    }

    refreshAttendanceList();
    stackedWidget->setCurrentWidget(attendanceScreen);
}



void MainWindow::showFingerprintRegistration()
{
    fpUserComboBox->clear();
    QList<User> users = dbManager->getAllUsers();
    for (const User &user : users) {
        fpUserComboBox->addItem(user.getName() + " (ID: " + QString::number(user.getUserId()) + ")", user.getUserId());
    }
    
    stackedWidget->setCurrentWidget(fingerprintScreen);
}

void MainWindow::addNewUser()
{
    if (userNameEdit->text().isEmpty() || userEmailEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields");
        return;
    }
    
    User newUser;
    newUser.setName(userNameEdit->text());
    newUser.setEmail(userEmailEdit->text());
    newUser.setDepartment(userDeptEdit->text());
    
    if (dbManager->addUser(newUser)) {
        QMessageBox::information(this, "Success", "User added successfully!");
        userNameEdit->clear();
        userEmailEdit->clear();
        userDeptEdit->clear();
        refreshUsersList();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add user!");
    }
}

void MainWindow::registerFingerprint()
{
    if (fpUserComboBox->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "Please select a user");
        return;
    }
    
    int userId = fpUserComboBox->currentData().toInt();
    int fingerIndex = fingerIndexComboBox->currentIndex() + 1;
    
    ScannerDevice scanner(1, "Main Scanner");
    QString fingerprintData = scanner.scanFingerprint();
    
    Fingerprint fp;
    fp.setUserId(userId);
    fp.setFingerprintData(fingerprintData);
    fp.setFingerIndex(fingerIndex);
    
    if (dbManager->addFingerprint(fp)) {
        QMessageBox::information(this, "Success", 
            "Fingerprint registered successfully!\nScan ID: " + fingerprintData);
    } else {
        QMessageBox::critical(this, "Error", "Failed to register fingerprint!");
    }
}

void MainWindow::markCheckIn()
{
    if (userComboBox->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "Please select a user");
        return;
    }

    int userId = userComboBox->currentData().toInt();

    AttendanceRecord record;
    record.setUserId(userId);
    record.markCheckIn();

    if (dbManager->addAttendanceRecord(record)) {
        playCustomInfoMessageBox("Success",
                                 "Check-in recorded!\nTime: " + record.getCheckInTime() +
                                     "\nStatus: " + record.getStatus(),"qrc:/sfx/sfx/riceee_check _in.wav");
        refreshAttendanceList();
    } else {
        QMessageBox::critical(this, "Error", "Failed to record check-in!");
    }
}


void MainWindow::markCheckOut()
{
    if (userComboBox->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "Please select a user");
        return;
    }

    int userId = userComboBox->currentData().toInt();
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");

    // البحث عن سجل الحضور لهذا اليوم
    QList<AttendanceRecord> records = dbManager->getAttendanceRecords(userId);
    int recordId = -1;
    QString checkInTime;

    for (const AttendanceRecord &record : records) {
        if (record.getDate() == currentDate && record.getCheckOutTime().isEmpty()) {
            recordId = record.getRecordId();
            checkInTime = record.getCheckInTime();
            break;
        }
    }

    if (recordId == -1) {
        QMessageBox::warning(this, "Error", "No check-in record found for today or already checked out");
        return;
    }


    QTime currentTime = QTime::currentTime();
    QString checkOutTime = currentTime.toString("hh:mm:ss");

    if (dbManager->updateCheckOut(recordId, checkOutTime)) {
        // حساب ساعات العمل
        QTime inTime = QTime::fromString(checkInTime, "hh:mm:ss");
        int hours = inTime.secsTo(currentTime) / 3600;
        int minutes = (inTime.secsTo(currentTime) % 3600) / 60;

        playCustomInfoMessageBox("Success",
                                 "Check-out recorded!\n"
                                 "Check-in: " + checkInTime + "\n" +
                                     "Check-out: " + checkOutTime + "\n" +
                                     "Working hours: " + QString::number(hours) + "h " + QString::number(minutes) + "m\n" +
                                     "Have a nice day!","qrc:/sfx/sfx/check_out.wav");
        refreshAttendanceList();
    } else {
        QMessageBox::critical(this, "Error", "Failed to record check-out!");
    }
}

// (FULLY EDITED BY YOUSSEF WAEL)
void MainWindow::refreshUsersList()
{
    usersTable->setRowCount(0);

    QList<User> allUsers = dbManager->getAllUsers();
    int row=0;
    for (const User &u : allUsers)
    {
        usersTable->insertRow(row);
        QTableWidgetItem* itemId = new QTableWidgetItem(QString::number(u.getUserId()));
        // Store ID hidden inside item
        itemId->setData(Qt::UserRole, u.getUserId());
        usersTable->setItem(row,0,itemId);

        QTableWidgetItem* itemName = new QTableWidgetItem(u.getName());
        itemName->setData(Qt::UserRole, u.getUserId());
        usersTable->setItem(row,1,itemName);

        QTableWidgetItem* itemEmail = new QTableWidgetItem(u.getEmail());
        itemEmail->setData(Qt::UserRole,u.getUserId());
        usersTable->setItem(row,2,itemEmail);

        QTableWidgetItem* itemDepartment = new QTableWidgetItem(u.getDepartment());
        itemDepartment->setData(Qt::UserRole,u.getUserId());
        usersTable->setItem(row,3,itemDepartment);

        row++;

    }
}


void MainWindow::refreshAttendanceList()
{
    attendanceTable->setRowCount(0);
    QList<AttendanceRecord> records = dbManager->getAttendanceRecords();
    
    int row = 0;
    for (const AttendanceRecord &record : records) {
        attendanceTable->insertRow(row);
        attendanceTable->setItem(row, 0, new QTableWidgetItem(QString::number(record.getUserId())));
        attendanceTable->setItem(row, 1, new QTableWidgetItem(dbManager->getUsername(record.getUserId())));
        attendanceTable->setItem(row, 2, new QTableWidgetItem(record.getDate()));
        attendanceTable->setItem(row, 3, new QTableWidgetItem(record.getCheckInTime()));
        attendanceTable->setItem(row, 4, new QTableWidgetItem(record.getStatus()));
        row++;
    }
}

// sets password (BY YOUSSEF WAEL)
void MainWindow::setUserPassword()
{
    int row = usersTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a user first.");
        return;
    }

    int userId = usersTable->item(row,0)->data(Qt::UserRole).toInt();

    bool ok;
    QString newPass = QInputDialog::getText(
        this,
        "Set Password",
        "Enter new password:",
        QLineEdit::Password,
        "",
        &ok
        );

    if(!ok){
        return;
    }

    if (!ok || newPass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Password cannot be empty.");
        return;
    }

    // Update DB
    if (dbManager->setUserPassword(userId, newPass)) {
        QMessageBox::information(this, "Success", "Password updated successfully!");
    } else {
        playCustomMessageBox("Error", "Failed to update password!","qrc:/sfx/sfx/sad_horn.wav");
    }
}



void MainWindow::deleteUser()
{
    int row = usersTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Delete User", "Please select a user to delete.");
        return;
    }

    int userId = usersTable->item(row, 0)->data(Qt::UserRole).toInt();


    if (QMessageBox::question(this, "Confirm Deletion",
                              "Are you sure you want to delete this user?")
        != QMessageBox::Yes)
        return;

    // Delete from DB
    if (dbManager->deleteUserById(userId))
    {
        usersTable->removeRow(row);
        QMessageBox::information(this, "Deleted", "User deleted successfully.");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to delete user.");
    }
}

// sfx+msg (BY YOUSSEF WAEL)
void MainWindow::playCustomMessageBox(const QString &title, const QString &text, const QString &resourcePath)
{
    // Play sound
    QSoundEffect *effect = new QSoundEffect(this);
    effect->setSource(QUrl(resourcePath));
    effect->setVolume(0.9f);
    effect->play();

    QMessageBox::warning(this, title, text);
}
// same sfx+msg but info message box
void MainWindow::playCustomInfoMessageBox(const QString &title, const QString &text, const QString &resourcePath)
{
    // Play sound
    QSoundEffect *effect = new QSoundEffect(this);
    effect->setSource(QUrl(resourcePath));
    effect->setVolume(0.9f);
    effect->play();

    QMessageBox::information(this, title, text);
}

QLabel* MainWindow::createAvatar(const QString &path)
{
    QLabel *img = new QLabel;
    img->setFixedSize(90, 90);

    img->setStyleSheet(
        "border-radius: 12px;"
        "background-image: url(" + path + ");"
                 "background-position: center;"
                 "background-repeat: no-repeat;"
                 "background-size: cover;"
        );

    return img;
}
