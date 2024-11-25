#include <QFile>
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    setupUiWidgets();
    setupLayout();
    setupStyles();
    setupAnimations();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete centralWidget;
}

void MainWindow::setupUiWidgets()
{
    // UI Widgets
    centralWidget = new QWidget(this);
    container = new QWidget(centralWidget);
    loginLabel = new QLabel(container);
    usernameLabel = new QLabel(container);
    usernameLineEdit = new QLineEdit(container);
    passwordLabel = new QLabel(container);
    passwordLineEdit = new QLineEdit(container);
    loginButton = new QPushButton(container);
    statusLabel = new QLabel(container);
    backgroundLabel = new QLabel(this);

    // Đặt Object Name cho Qss
    container->setObjectName("container");
    loginLabel->setObjectName("loginLabel");
    usernameLabel->setObjectName("usernameLabel");
    passwordLabel->setObjectName("passwordLabel");
    usernameLineEdit->setObjectName("usernameLineEdit");
    passwordLineEdit->setObjectName("passwordLineEdit");
    loginButton->setObjectName("loginButton");
    statusLabel->setObjectName("statusLabel");
}

void MainWindow::setupLayout()
{
    setCentralWidget(centralWidget);
    container->setMinimumSize(CONTAINER_MIN_WIDTH, CONTAINER_MIN_HEIGHT);
    container->setFocus();
    container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Tạo Login-Form layout dọc
    QVBoxLayout *formLayout = new QVBoxLayout(container);
    formLayout->setSpacing(20);
    formLayout->setContentsMargins(50, 50, 50, 50);

    // Thêm các Widgets vào layout
    formLayout->addWidget(loginLabel);
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(usernameLineEdit);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordLineEdit);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(statusLabel);

    // Tạo main layout ngang
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(container, 0, Qt::AlignCenter);
    mainLayout->addStretch();
}

void MainWindow::setupStyles()
{
    // Tải Source.qss từ Resource.qrc
    QFile styleFile(":/Style.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
    }

    // Background
    backgroundLabel->setPixmap(QPixmap(":/Images/background.jpg"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();

    // Login Label
    loginLabel->setText(QString::fromUtf8("Đăng Nhập"));
    loginLabel->setAlignment(Qt::AlignCenter);

    // Username
    usernameLabel->setText(QString::fromUtf8("Tài Khoản"));
    usernameLabel->setVisible(false);
    usernameLineEdit->setPlaceholderText(QString::fromUtf8("Tài Khoản"));

    // Password
    passwordLabel->setText("Mật Khẩu");
    passwordLabel->setVisible(false);
    passwordLineEdit->setPlaceholderText(QString::fromUtf8("Mật Khẩu"));
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton->setText(QString::fromUtf8("Đăng Nhập"));

    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setVisible(false);
}

// Tạo Animations
void MainWindow::setupAnimations()
{
    // Tạo hiệu ứng trong suốt cho usernameLabel và passwordLabel
    usernameLabelEffect = new QGraphicsOpacityEffect(this);
    usernameLabelEffect->setOpacity(0);
    usernameLabel->setGraphicsEffect(usernameLabelEffect);

    passwordLabelEffect = new QGraphicsOpacityEffect(this);
    passwordLabelEffect->setOpacity(0);
    passwordLabel->setGraphicsEffect(passwordLabelEffect);

    // Tạo animations cho usernameLabel và passwordLabel
    usernameAnimation = new QPropertyAnimation(usernameLabelEffect, "opacity", this);
    usernameAnimation->setDuration(500);
    usernameAnimation->setEasingCurve(QEasingCurve::InCubic);

    passwordAnimation = new QPropertyAnimation(passwordLabelEffect, "opacity", this);
    passwordAnimation->setDuration(500);
    passwordAnimation->setEasingCurve(QEasingCurve::InCubic);
}

// Quản lý các events
void MainWindow::handleUsernameFocusIn()
{
    if (usernameLabel && usernameLineEdit)
    {
        usernameLabel->setVisible(true);
        usernameLineEdit->setPlaceholderText("");

        usernameAnimation->stop();
        usernameAnimation->setStartValue(0);
        usernameAnimation->setEndValue(1);
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
        passwordAnimation->setStartValue(0);
        passwordAnimation->setEndValue(1);
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

// Bỏ focus khi bấm ra ngoài
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget *focusedWidget = QApplication::focusWidget();
    if (focusedWidget)
    {
        focusedWidget->clearFocus();
    }
    QMainWindow::mousePressEvent(event);
}

// Điều chỉnh kích cỡ của Background
void MainWindow::resizeEvent(QResizeEvent *event)
{
    backgroundLabel->setGeometry(this->rect());
    QWidget::resizeEvent(event);
}

// Xử lý khi Login Button được bấm
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

// Kết nối Signals và Slots
void MainWindow::setupConnections()
{
    connect(usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);

    usernameLineEdit->installEventFilter(this);
    passwordLineEdit->installEventFilter(this);
}
