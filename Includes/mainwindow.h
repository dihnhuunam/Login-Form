#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QWidget *centralWidget;
    QLabel *backgroundLabel;
    QWidget *container;
    QLabel *loginLabel;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QLabel *statusLabel;
    QPushButton *themeButton;
    QPropertyAnimation *usernameAnimation;
    QPropertyAnimation *passwordAnimation;
    QGraphicsOpacityEffect *usernameLabelEffect;
    QGraphicsOpacityEffect *passwordLabelEffect;
    QGraphicsOpacityEffect *backgroundEffect;
    QPropertyAnimation *themeAnimation;

    bool isDarkMode = false;

    void toggleTheme();
    void setupTheme();
    void setupUiWidgets();
    void setupLayout();
    void setupConnections();
    void setupAnimations();
    void handleFocusIn(QLabel *label, QLineEdit *lineEdit, QPropertyAnimation *animation);
    void handleFocusOut(QLabel *label, QLineEdit *lineEdit, QPropertyAnimation *animation);

private slots:
    void on_loginButton_clicked();
};

#endif // MAINWINDOW_H