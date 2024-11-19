#include "mainwindow.h"
#include <QFile>
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), container(nullptr), backgroundLabel(nullptr),
      statusLabel(nullptr), loginLabel(nullptr), usernameLabel(nullptr),
      passwordLabel(nullptr), usernameLineEdit(nullptr),
      passwordLineEdit(nullptr), loginButton(nullptr),
      usernameLabelEffect(nullptr), passwordLabelEffect(nullptr),
      usernameAnimation(nullptr), passwordAnimation(nullptr)
{
    setupLayout();
    setupStyles();
    setupConnections();
    setupAnimations();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (backgroundLabel)
    {
        backgroundLabel->setGeometry(this->rect());
    }
}

void MainWindow::setupLayout()
{
    // Central widget setup
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    container = new QWidget(centralWidget);
    container->setObjectName("container");
    container->setMinimumSize(400, 300);
    container->setMaximumSize(600, 400);

    QVBoxLayout *vLayout = new QVBoxLayout(container);
    vLayout->setSpacing(15);
    vLayout->setContentsMargins(20, 20, 20, 20);

    // Login label
    loginLabel = new QLabel(container);
    loginLabel->setObjectName("loginLabel");
    vLayout->addWidget(loginLabel);

    // Username label
    usernameLabel = new QLabel(container);
    usernameLabel->setObjectName("usernameLabel");
    usernameLabel->setText("Tài Khoản");
    usernameLabel->setVisible(false);
    vLayout->addWidget(usernameLabel);

    // Username line edit
    usernameLineEdit = new QLineEdit(container);
    usernameLineEdit->setObjectName("usernameLineEdit");
    vLayout->addWidget(usernameLineEdit);

    // Password label
    passwordLabel = new QLabel(container);
    passwordLabel->setObjectName("passwordLabel");
    passwordLabel->setText("Mật Khẩu");
    passwordLabel->setVisible(false);
    vLayout->addWidget(passwordLabel);

    // Password line edit
    passwordLineEdit = new QLineEdit(container);
    passwordLineEdit->setObjectName("passwordLineEdit");
    vLayout->addWidget(passwordLineEdit);

    // Login button
    loginButton = new QPushButton(container);
    loginButton->setObjectName("loginButton");
    vLayout->addWidget(loginButton);

    // Status label
    statusLabel = new QLabel(container);
    statusLabel->setObjectName("statusLabel");
    statusLabel->setVisible(false);
    vLayout->addWidget(statusLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addStretch();
    mainLayout->addWidget(container);
    mainLayout->addStretch();
}

void MainWindow::setupStyles()
{
    // Load styles from file
    QFile styleFile(":/Style.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
    }

    // Background setup
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/Images/background.jpg"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();

    // Apply blur effect to the background label
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(1);
    backgroundLabel->setGraphicsEffect(blurEffect);

    // Widget text and styles
    loginLabel->setText(QString::fromUtf8("Đăng Nhập"));
    loginLabel->setAlignment(Qt::AlignCenter);

    usernameLineEdit->setPlaceholderText("Tài Khoản");
    usernameLineEdit->setAlignment(Qt::AlignLeft);

    passwordLineEdit->setPlaceholderText("Mật Khẩu");
    passwordLineEdit->setAlignment(Qt::AlignLeft);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton->setText(QString::fromUtf8("Đăng Nhập"));

    statusLabel->setVisible(false);
    statusLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::setupAnimations()
{
    // Setup opacity effects for labels
    usernameLabelEffect = new QGraphicsOpacityEffect(this);
    usernameLabelEffect->setOpacity(0);
    usernameLabel->setGraphicsEffect(usernameLabelEffect);

    passwordLabelEffect = new QGraphicsOpacityEffect(this);
    passwordLabelEffect->setOpacity(0);
    passwordLabel->setGraphicsEffect(passwordLabelEffect);

    // Setup animations
    usernameAnimation = new QPropertyAnimation(usernameLabelEffect, "opacity", this);
    usernameAnimation->setDuration(300);
    usernameAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    passwordAnimation = new QPropertyAnimation(passwordLabelEffect, "opacity", this);
    passwordAnimation->setDuration(300);
    passwordAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

void MainWindow::setupConnections()
{
    connect(usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);

    // Install event filter for focus events
    usernameLineEdit->installEventFilter(this);
    passwordLineEdit->installEventFilter(this);
}

void MainWindow::handleUsernameFocusIn()
{
    if (usernameLabel && usernameLineEdit)
    {
        usernameLabel->setVisible(true);
        usernameLineEdit->setPlaceholderText("");

        usernameAnimation->stop();
        usernameAnimation->setStartValue(0.0);
        usernameAnimation->setEndValue(1.0);
        usernameAnimation->start();
    }
}

void MainWindow::handlePasswordFocusIn()
{
    if (passwordLabel && passwordLineEdit)
    {
        passwordLabel->setVisible(true);
        passwordLineEdit->setPlaceholderText("");

        passwordAnimation->stop();
        passwordAnimation->setStartValue(0.0);
        passwordAnimation->setEndValue(1.0);
        passwordAnimation->start();
    }
}

void MainWindow::handleUsernameFocusOut()
{
    if (usernameLabel && usernameLineEdit)
    {
        if (usernameLineEdit->text().isEmpty())
        {
            usernameAnimation->stop();
            usernameAnimation->setStartValue(1.0);
            usernameAnimation->setEndValue(0.0);
            connect(usernameAnimation, &QPropertyAnimation::finished, this, [this]()
                    {
                usernameLabel->setVisible(false);
                usernameLineEdit->setPlaceholderText("Tài khoản");
                disconnect(usernameAnimation, &QPropertyAnimation::finished, this, nullptr); });
            usernameAnimation->start();
        }
    }
}

void MainWindow::handlePasswordFocusOut()
{
    if (passwordLabel && passwordLineEdit)
    {
        if (passwordLineEdit->text().isEmpty())
        {
            passwordAnimation->stop();
            passwordAnimation->setStartValue(1.0);
            passwordAnimation->setEndValue(0.0);
            connect(passwordAnimation, &QPropertyAnimation::finished, this, [this]()
                    {
                passwordLabel->setVisible(false);
                passwordLineEdit->setPlaceholderText("Mật khẩu");
                disconnect(passwordAnimation, &QPropertyAnimation::finished, this, nullptr); });
            passwordAnimation->start();
        }
    }
}

void MainWindow::on_loginButton_clicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();
    QString successColor = "#6BBF59";
    QString errorColor = "#FF6B6B";

    if (username.isEmpty() || password.isEmpty())
    {
        statusLabel->setVisible(true);
        statusLabel->setStyleSheet(QString("color: %1").arg(errorColor));
        statusLabel->setText("Vui lòng nhập đầy đủ thông tin!");
        return;
    }

    if (username == "test" && password == "test")
    {
        statusLabel->setVisible(true);
        statusLabel->setStyleSheet(QString("color: %1").arg(successColor));
        statusLabel->setText("Đăng nhập thành công.");
    }
    else
    {
        statusLabel->setVisible(true);
        statusLabel->setStyleSheet(QString("color: %1").arg(errorColor));
        statusLabel->setText("Đăng nhập thất bại.");
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == usernameLineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            handleUsernameFocusIn();
        }
        else if (event->type() == QEvent::FocusOut)
        {
            handleUsernameFocusOut();
        }
    }
    else if (watched == passwordLineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            handlePasswordFocusIn();
        }
        else if (event->type() == QEvent::FocusOut)
        {
            handlePasswordFocusOut();
        }
    }
    return QMainWindow::eventFilter(watched, event);
}