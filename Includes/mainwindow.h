#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

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

    QWidget *container;
    QLabel *backgroundLabel;
    QLabel *statusLabel;
    QLabel *loginLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

    // Animation related members
    QGraphicsOpacityEffect *usernameLabelEffect;
    QGraphicsOpacityEffect *passwordLabelEffect;
    QPropertyAnimation *usernameAnimation;
    QPropertyAnimation *passwordAnimation;
};

#endif // MAINWINDOW_H