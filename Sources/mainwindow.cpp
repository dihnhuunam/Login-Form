#include <QFile>
#include <QGraphicsOpacityEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QIcon>
#include "mainwindow.h"

const int CONTAINER_MIN_WIDTH = 500;
const int CONTAINER_MIN_HEIGHT = 300;
const int ANIMATION_DURATION = 800;
const QString successColor = "#6BBF59";
const QString errorColor = "#FF6B6B";
const QString lightIcon = ":/Images/light_icon.png";
const QString darkIcon = ":/Images/dark_icon.png";
const QString lightBackground = ":/Images/background_light.jpg";
const QString darkBackground = ":/Images/background_dark.jpg";

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUiWidgets();
    setupLayout();
    setupStyles();
    setupAnimations();
    setupConnections();
    updateTheme();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUiWidgets()
{
    // UI Widgets
    centralWidget = new QWidget(this);
    backgroundLabel = new QLabel(this);
    container = new QWidget(centralWidget);
    loginLabel = new QLabel(container);
    usernameLabel = new QLabel(container);
    usernameLineEdit = new QLineEdit(container);
    passwordLabel = new QLabel(container);
    passwordLineEdit = new QLineEdit(container);
    loginButton = new QPushButton(container);
    statusLabel = new QLabel(container);
    themeButton = new QPushButton(this);

    // Animations

    // Đặt Object Name cho Qss
    container->setObjectName("container");
    loginLabel->setObjectName("loginLabel");
    usernameLabel->setObjectName("usernameLabel");
    passwordLabel->setObjectName("passwordLabel");
    usernameLineEdit->setObjectName("usernameLineEdit");
    passwordLineEdit->setObjectName("passwordLineEdit");
    loginButton->setObjectName("loginButton");
    statusLabel->setObjectName("statusLabel");
    themeButton->setObjectName("themeButton");
}

void MainWindow::setupLayout()
{
    setCentralWidget(centralWidget);
    container->setMinimumSize(CONTAINER_MIN_WIDTH, CONTAINER_MIN_HEIGHT);

    auto *formLayout = new QVBoxLayout(container);
    formLayout->setSpacing(20);
    formLayout->setContentsMargins(50, 50, 50, 50);

    formLayout->addWidget(loginLabel);
    formLayout->addWidget(usernameLabel);
    formLayout->addWidget(usernameLineEdit);
    formLayout->addWidget(passwordLabel);
    formLayout->addWidget(passwordLineEdit);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(statusLabel);

    auto *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(themeButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(container, 0, Qt::AlignCenter);
    mainLayout->addStretch();
}

void MainWindow::updateTheme()
{

    themeAnimation->stop();
    themeAnimation->setStartValue(1.0);
    themeAnimation->setEndValue(0.0);
    themeAnimation->start();

    if (isDarkMode)
    {
        // Dark Mode
        QFile styleFile(":/Styles/Dark.qss");
        if (styleFile.open(QFile::ReadOnly))
        {
            setStyleSheet(QString::fromUtf8(styleFile.readAll()));
            styleFile.close();
        }
        backgroundLabel->setPixmap(QPixmap(darkBackground));
        QSize iconSize(28, 28);
        themeButton->setIcon(QIcon(darkIcon));
        themeButton->setIconSize(iconSize);
        themeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    else
    {
        // Light Mode
        QFile styleFile(":/Styles/Light.qss");
        if (styleFile.open(QFile::ReadOnly))
        {
            setStyleSheet(QString::fromUtf8(styleFile.readAll()));
            styleFile.close();
        }
        backgroundLabel->setPixmap(QPixmap(lightBackground));
        QSize iconSize(28, 28);
        themeButton->setIcon(QIcon(lightIcon));
        themeButton->setIconSize(iconSize);
        themeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    // Hiện ảnh nền
    themeAnimation->setStartValue(0.0);
    themeAnimation->setEndValue(1.0);
    themeAnimation->start();

    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();
}

void MainWindow::toggleTheme()
{
    isDarkMode = !isDarkMode;
    updateTheme();
}

void MainWindow::setupStyles()
{
    loginLabel->setText("Đăng Nhập");
    loginLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    usernameLabel->setText("Tài Khoản");
    usernameLabel->setVisible(false);

    usernameLineEdit->setPlaceholderText("Tài Khoản");
    usernameLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    passwordLabel->setText("Mật Khẩu");
    passwordLabel->setVisible(false);

    passwordLineEdit->setPlaceholderText("Mật Khẩu");
    passwordLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton->setText("Đăng Nhập");
    loginButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setVisible(false);
    statusLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Đặt icon và kích thước của themeButton
}

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

    // Tạo hiệu ứng cho chuyển giữa 2 mode
    backgroundEffect = new QGraphicsOpacityEffect(this);
    backgroundLabel->setGraphicsEffect(backgroundEffect);

    // Tạo animation khi chuyển giữa 2 mode
    themeAnimation = new QPropertyAnimation(backgroundEffect, "opacity", this);
    themeAnimation->setDuration(500);
    themeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

// FocusIn: Nếu đã có nội dung, hiển thị label nhưng không chạy animation.
void MainWindow::handleFocusIn(QLabel *label, QLineEdit *lineEdit, QPropertyAnimation *animation)
{
    if (label && lineEdit)
    {
        if (!(lineEdit->text().isEmpty()))
        {
            label->setVisible(true);
            return;
        }

        label->setVisible(true);
        lineEdit->setPlaceholderText("");

        animation->stop();
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->setDuration(ANIMATION_DURATION);
        animation->start();
    }
}

// FocusOut: Nếu không có nội dung, chạy animation và ẩn label.
void MainWindow::handleFocusOut(QLabel *label, QLineEdit *lineEdit, QPropertyAnimation *animation)
{
    if (label && lineEdit)
    {
        if (!(lineEdit->text().isEmpty()))
        {
            return;
        }

        if (lineEdit->text().isEmpty())
        {
            animation->stop();
            animation->setStartValue(1.0);
            animation->setEndValue(0.0);
            connect(animation, &QPropertyAnimation::finished, this, [label, lineEdit, animation]()
                    {
                label->setVisible(false);
                lineEdit->setPlaceholderText(label->text());
                disconnect(animation, &QPropertyAnimation::finished, nullptr, nullptr); });
            animation->start();
        }
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == usernameLineEdit || watched == passwordLineEdit)
    {
        QLabel *label = (watched == usernameLineEdit) ? usernameLabel : passwordLabel;
        QPropertyAnimation *animation = (watched == usernameLineEdit) ? usernameAnimation : passwordAnimation;

        if (event->type() == QEvent::FocusIn)
        {
            handleFocusIn(label, qobject_cast<QLineEdit *>(watched), animation);
        }
        else if (event->type() == QEvent::FocusOut)
        {
            handleFocusOut(label, qobject_cast<QLineEdit *>(watched), animation);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget *focusedWidget = QApplication::focusWidget();
    if (focusedWidget)
        focusedWidget->clearFocus();
    QMainWindow::mousePressEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    backgroundLabel->setGeometry(this->rect());
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_loginButton_clicked()
{
    QString username = usernameLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();

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

void MainWindow::setupConnections()
{
    connect(usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(themeButton, &QPushButton::clicked, this, &MainWindow::toggleTheme); // Kết nối nút đổi theme

    usernameLineEdit->installEventFilter(this);
    passwordLineEdit->installEventFilter(this);
}
