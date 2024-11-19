#include "mainwindow.h"
#include <QFile>
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), container(nullptr), backgroundLabel(nullptr),
      statusLabel(nullptr), loginLabel(nullptr), usernameLineEdit(nullptr),
      passwordLineEdit(nullptr), loginButton(nullptr)
{
    setupLayout();
    setupStyles();
    setupConnections();
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

    // Username line edit
    usernameLineEdit = new QLineEdit(container);
    usernameLineEdit->setObjectName("usernameLineEdit");
    vLayout->addWidget(usernameLineEdit);

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

    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(15);
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
}

void MainWindow::setupConnections()
{
    connect(usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
}

void MainWindow::on_loginButton_clicked()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString successColor = "#6BBF59";
    QString errorColor = "#FF6B6B";

    if (username == "test" && password == "test")
    {
        statusLabel->setVisible(true);
        statusLabel->setStyleSheet(QString("color: %1;").arg(successColor));
        statusLabel->setText("Đăng nhập thành công.");
    }
    else
    {
        statusLabel->setVisible(true);
        statusLabel->setStyleSheet(QString("color: %1;").arg(errorColor));
        statusLabel->setText("Đăng nhập thất bại.");
    }
}
