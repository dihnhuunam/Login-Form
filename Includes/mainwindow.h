#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsBlurEffect>
#include <QFocusEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QLabel *backgroundLabel;
    QWidget *container;
    QLabel *statusLabel;
    QLabel *loginLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

    void setupStyles();
    void setupLayout();
    void setupConnections();

private slots:
    void on_loginButton_clicked();
    void handleUsernameFocusIn();
    void handlePasswordFocusIn();
    void handleUsernameFocusOut();
    void handlePasswordFocusOut();
};

#endif // MAINWINDOW_H
