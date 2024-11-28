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
const QString lightSyle = ":/Styles/Light.qss";
const QString darkSyle = ":/Styles/Dark.qss";

/**
 * @brief Constructor cho MainWindow. Khởi tạo các thành phần giao diện và thiết lập các kết nối cần thiết.
 * @param parent Con trỏ tới QWidget cha (nếu có).
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUiWidgets();
    setupLayout();
    setupAnimations();
    setupTheme();
    setupConnections();
}

/**
 * @brief Destructor cho MainWindow. Dọn dẹp tài nguyên nếu cần.
 */
MainWindow::~MainWindow() {}

/**
 * @brief Thiết lập các widget giao diện người dùng (UI).
 */
void MainWindow::setupUiWidgets()
{
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

    container->setObjectName("container");
    themeButton->setObjectName("themeButton");

    loginLabel->setObjectName("loginLabel");
    loginLabel->setText("Đăng Nhập");
    loginLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    usernameLabel->setObjectName("usernameLabel");
    usernameLabel->setText("Tài Khoản");
    usernameLabel->setVisible(false);

    usernameLineEdit->setObjectName("usernameLineEdit");
    usernameLineEdit->setPlaceholderText("Tài Khoản");
    usernameLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    passwordLabel->setObjectName("passwordLabel");
    passwordLabel->setText("Mật Khẩu");
    passwordLabel->setVisible(false);

    passwordLineEdit->setObjectName("passwordLineEdit");
    passwordLineEdit->setPlaceholderText("Mật Khẩu");
    passwordLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton->setObjectName("loginButton");
    loginButton->setText("Đăng Nhập");
    loginButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    statusLabel->setObjectName("statusLabel");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setVisible(false);
    statusLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

/**
 * @brief Thiết lập layout cho các widget trong cửa sổ chính.
 */
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

/**
 * @brief Thiết lập các hiệu ứng hoạt hình (animation) cho các widget giao diện.
 */
void MainWindow::setupAnimations()
{
    // Tạo hiệu ứng trong suốt cho usernameLabel và passwordLabel
    usernameLabelEffect = new QGraphicsOpacityEffect(this);
    usernameLabel->setGraphicsEffect(usernameLabelEffect);

    passwordLabelEffect = new QGraphicsOpacityEffect(this);
    passwordLabel->setGraphicsEffect(passwordLabelEffect);

    // Tạo animations cho usernameLabel và passwordLabel
    usernameAnimation = new QPropertyAnimation(usernameLabelEffect, "opacity", this);
    usernameAnimation->setDuration(ANIMATION_DURATION);
    usernameAnimation->setEasingCurve(QEasingCurve::InCubic);

    passwordAnimation = new QPropertyAnimation(passwordLabelEffect, "opacity", this);
    passwordAnimation->setDuration(ANIMATION_DURATION);
    passwordAnimation->setEasingCurve(QEasingCurve::InCubic);

    // Tạo hiệu ứng cho chuyển giữa 2 mode
    backgroundEffect = new QGraphicsOpacityEffect(this);
    backgroundLabel->setGraphicsEffect(backgroundEffect);

    // Tạo animation khi chuyển giữa 2 mode
    themeAnimation = new QPropertyAnimation(backgroundEffect, "opacity", this);
    themeAnimation->setDuration(ANIMATION_DURATION);
    themeAnimation->setEasingCurve(QEasingCurve::InQuad);
}

/**
 * @brief Cập nhật giao diện theo chế độ sáng/tối hiện tại, bao gồm các hiệu ứng chuyển đổi.
 */
void MainWindow::setupTheme()
{
    if (isDarkMode)
    {
        // Dark Mode
        QFile styleFile(darkSyle);
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
        QFile styleFile(lightSyle);
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

/**
 * @brief Chuyển đổi chế độ giao diện giữa sáng và tối.
 */
void MainWindow::toggleTheme()
{
    isDarkMode = !isDarkMode;
    setupTheme();
}

/**
 * @brief Xử lý sự kiện khi một QLineEdit nhận được focus. Hiển thị label kèm hiệu ứng.
 * @param label QLabel liên kết với QLineEdit.
 * @param lineEdit QLineEdit cần xử lý.
 * @param animation Hiệu ứng hoạt hình áp dụng.
 */
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

/**
 * @brief Xử lý sự kiện khi một QLineEdit mất focus. Ẩn label kèm hiệu ứng.
 * @param label QLabel liên kết với QLineEdit.
 * @param lineEdit QLineEdit cần xử lý.
 * @param animation Hiệu ứng hoạt hình áp dụng.
 */
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

/**
 * @brief Lọc và xử lý các sự kiện liên quan đến QLineEdit (FocusIn, FocusOut).
 * @param watched Đối tượng bị giám sát.
 * @param event Sự kiện được kích hoạt.
 * @return Trả về true nếu sự kiện được xử lý, ngược lại trả về false.
 */
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

/**
 * @brief Xử lý sự kiện nhấn chuột. Loại bỏ focus khỏi widget hiện tại.
 * @param event Sự kiện chuột.
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget *focusedWidget = QApplication::focusWidget();
    if (focusedWidget)
        focusedWidget->clearFocus();
    QMainWindow::mousePressEvent(event);
}

/**
 * @brief Xử lý sự kiện thay đổi kích thước cửa sổ chính. Điều chỉnh kích thước ảnh nền.
 * @param event Sự kiện thay đổi kích thước.
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{
    backgroundLabel->setGeometry(this->rect());
    QMainWindow::resizeEvent(event);
}

/**
 * @brief Xử lý sự kiện khi nút "Đăng Nhập" được nhấn. Kiểm tra thông tin và hiển thị kết quả.
 */
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

/**
 * @brief Thiết lập các kết nối signals-slots cho các widget.
 */
void MainWindow::setupConnections()
{
    connect(usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_loginButton_clicked);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::on_loginButton_clicked);
    connect(themeButton, &QPushButton::clicked, this, &MainWindow::toggleTheme);

    usernameLineEdit->installEventFilter(this);
    passwordLineEdit->installEventFilter(this);
}
