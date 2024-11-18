#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsBlurEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QLabel *backgroundLabel; // Biến thành viên để quản lý QLabel

    void setupStyles();
    void setupLayout();
    void setupConnections();

private slots:
    void on_loginButton_clicked();
};

#endif // MAINWINDOW_H
