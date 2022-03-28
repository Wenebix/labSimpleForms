#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QLineEdit>
#include <QTime>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *tmr;
    QTableWidgetItem *cell = new QTableWidgetItem;
    QTableWidgetItem* empty = new QTableWidgetItem;
    void showTable();
private slots:
    void updateTime();
    void on_spTable_cellClicked(int row, int column);

    void on_restartGame_triggered();

    void on_newGame_triggered();

    void on_quit_triggered();
    void TimerSlot();

private:
    int ms, s, m;
    QTimer *timer;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
