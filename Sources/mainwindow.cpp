#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QtWidgets>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), backgroundLabel(nullptr)
{
    ui->setupUi(this);

    setupStyles();
    setupLayout();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QWidget *container = new QWidget(ui->centralWidget);
    container->setObjectName(QString::fromUtf8("container"));

    container->setMinimumSize(400, 300);
    container->setMaximumSize(600, 400);

    QVBoxLayout *vLayout = new QVBoxLayout(container);
    vLayout->setSpacing(15);
    vLayout->setContentsMargins(20, 20, 20, 20);

    vLayout->addWidget(ui->loginLabel);
    vLayout->addWidget(ui->usernameLineEdit);
    vLayout->addWidget(ui->passwordLineEdit);
    vLayout->addWidget(ui->loginButton);
    vLayout->addWidget(ui->statusLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout(ui->centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addStretch();
    mainLayout->addWidget(container);
    mainLayout->addStretch();

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::setupStyles()
{
    QFile styleFile(":/Style.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
    }

    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/Images/background.jpg"));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();

    // QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    // blurEffect->setBlurRadius(15);
    // backgroundLabel->setGraphicsEffect(blurEffect);

    ui->loginLabel->setText(QString::fromUtf8("Đăng Nhập"));
    ui->loginLabel->setAlignment(Qt::AlignCenter);

    ui->usernameLineEdit->setPlaceholderText("Tài Khoản");
    ui->usernameLineEdit->setAlignment(Qt::AlignLeft);
    ui->usernameLineEdit->setFocus();

    ui->passwordLineEdit->setPlaceholderText("Mật Khẩu");
    ui->passwordLineEdit->setAlignment(Qt::AlignLeft);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->loginButton->setText(QString::fromUtf8("Đăng Nhập"));

    ui->statusLabel->setVisible(false);
    ui->statusLabel->setAlignment(Qt::AlignCenter);
}

void MainWindow::setupConnections()
{
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString successColor = "#6BBF59";
    QString errorColor = "#FF6B6B";

    if (username == "test" && password == "test")
    {
        ui->statusLabel->setVisible(true);
        ui->statusLabel->setStyleSheet(QString("color: %1;").arg(successColor));
        ui->statusLabel->setText("Đăng nhập thành công.");
    }
    else
    {
        ui->statusLabel->setVisible(true);
        ui->statusLabel->setStyleSheet(QString("color: %1;").arg(errorColor));
        ui->statusLabel->setText("Đăng nhập thất bại.");
    }
}
