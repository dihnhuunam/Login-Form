#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QResizeEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void on_loginButton_clicked();
    void handleUsernameFocusIn();
    void handlePasswordFocusIn();
    void handleUsernameFocusOut();
    void handlePasswordFocusOut();

private:
    void setupLayout();
    void setupStyles();
    void setupConnections();
    void setupAnimations();

    // Base Widgets
    QWidget *centralWidget;
    QWidget *container;
    QLabel *backgroundLabel;
    QLabel *statusLabel;
    QLabel *loginLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

    // Aminations
    QGraphicsOpacityEffect *usernameLabelEffect;
    QGraphicsOpacityEffect *passwordLabelEffect;
    QPropertyAnimation *usernameAnimation;
    QPropertyAnimation *passwordAnimation;
};

#endif // MAINWINDOW_H