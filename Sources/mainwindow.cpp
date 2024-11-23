#include <QFile>
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QApplication>
#include <QSpacerItem>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(nullptr), container(nullptr), backgroundLabel(nullptr),
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

MainWindow::~MainWindow()
{
    delete centralWidget;
}

void MainWindow::setupLayout()
{
    // Tạo centralWidget để quản lý tất cả các widgets
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Tạo container để quản lý Login-Form
    container = new QWidget(centralWidget);
    container->setObjectName("container");
    container->setMinimumSize(400, 300);
    container->setMaximumSize(600, 400);
    container->setFocus();

    // Login-Form được layout vertical trong container
    QVBoxLayout *vLayout = new QVBoxLayout(container);
    vLayout->setSpacing(20);
    vLayout->setContentsMargins(50, 50, 50, 50);

    // Login label
    loginLabel = new QLabel(container);
    loginLabel->setObjectName("loginLabel");
    loginLabel->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(loginLabel);

    // Username label
    usernameLabel = new QLabel(container);
    usernameLabel->setObjectName("usernameLabel");
    vLayout->addWidget(usernameLabel);

    // Username line edit
    usernameLineEdit = new QLineEdit(container);
    usernameLineEdit->setObjectName("usernameLineEdit");
    usernameLineEdit->setAlignment(Qt::AlignLeft);
    vLayout->addWidget(usernameLineEdit);

    // Password label
    passwordLabel = new QLabel(container);
    passwordLabel->setObjectName("passwordLabel");
    vLayout->addWidget(passwordLabel);

    // Password line edit
    passwordLineEdit = new QLineEdit(container);
    passwordLineEdit->setObjectName("passwordLineEdit");
    passwordLineEdit->setAlignment(Qt::AlignLeft);
    vLayout->addWidget(passwordLineEdit);

    // Login button
    loginButton = new QPushButton(container);
    loginButton->setObjectName("loginButton");
    vLayout->addWidget(loginButton);

    // Status label
    statusLabel = new QLabel(container);
    statusLabel->setObjectName("statusLabel");
    vLayout->addWidget(statusLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(container);
    mainLayout->addStretch();
}

void MainWindow::setupStyles()
{
    // Tải file Style.qss trong Resources.qrc
    QFile styleFile(":/Style.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
    }

    // Tạo backgroundLabel
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/Images/background.jpg"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect()); // this->react() trả về hình chữ nhật với kích thước toàn màn hình mainwindow
    backgroundLabel->lower();                   // Đẩy backgroundLabel xuống layer thấp nhất (dưới các Widgets khác)

    // // Tạo hiệu ứng làm mờ blurEffect
    // QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    // blurEffect->setBlurRadius(1);
    // backgroundLabel->setGraphicsEffect(blurEffect); // Dùng hiệu ứng làm mờ blurEffect cho backgroundLabel

    // Tạo Style Sheet cho các Widgets
    loginLabel->setText(QString::fromUtf8("Đăng Nhập"));

    usernameLabel->setText(QString::fromUtf8("Tài Khoản"));
    usernameLabel->setVisible(false);

    usernameLineEdit->setPlaceholderText(QString::fromUtf8("Tài Khoản"));

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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget *focusedWidget = QApplication::focusWidget();
    if (focusedWidget)
    {
        focusedWidget->clearFocus();
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    backgroundLabel->setGeometry(this->rect());
    QWidget::resizeEvent(event);
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

// Set up connections
void MainWindow::setupConnections()
{
    connect(usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);

    // Install event filter for focus events
    usernameLineEdit->installEventFilter(this);
    passwordLineEdit->installEventFilter(this);
}
