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

void MainWindow::setupStyles()
{
    // Tải tệp QSS
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style = QString::fromUtf8(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
    }

    // Tạo QLabel để làm hình nền
    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/Images/background.jpg"));
    backgroundLabel->setScaledContents(true); // Đảm bảo hình nền bao phủ toàn bộ
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower(); // Đưa QLabel xuống dưới cùng

    // Tạo hiệu ứng làm mờ
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(15); // Điều chỉnh độ mờ (giá trị càng cao càng mờ)
    backgroundLabel->setGraphicsEffect(blurEffect);

    // Cấu hình các widget khác
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

void MainWindow::setupLayout()
{
    // Xóa layout cũ nếu có
    if (ui->centralwidget->layout())
    {
        delete ui->centralwidget->layout();
    }

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *hLayout = new QHBoxLayout();
    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addWidget(ui->loginLabel);
    vLayout->addWidget(ui->usernameLineEdit);
    vLayout->addWidget(ui->passwordLineEdit);
    vLayout->addWidget(ui->loginButton);
    vLayout->addWidget(ui->statusLabel);

    hLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout->addLayout(vLayout);
    hLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(hLayout);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    ui->centralwidget->setLayout(mainLayout);
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
