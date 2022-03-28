#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spots.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QTimer>
#include <QTime>
Spots sp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int centerX = width()/2;
    int centerY = height()/2;
    int tableSide = 402;
    ui->spTable->setGeometry(centerX-tableSide/2, centerY-tableSide/2, tableSide, tableSide);
    ui->spTable->setRowCount(4);
    ui->spTable->setColumnCount(4);
    for(int i = 0;i<4;i++) {
        ui->spTable->setColumnWidth(i, 100);
        ui->spTable->setRowHeight(i, 100);
    }
   cell->setTextAlignment(Qt::AlignCenter);
   ui->spTable->setEditTriggers(0);
   m = 0;
   ms = 0;
   s = 0;
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
   timer->start(1);
   showTable();
}


void MainWindow::showTable() {
    for(auto i=0;i<4;i++) {
        for(auto j=0;j<4; j++) {
            QTableWidgetItem* item = new QTableWidgetItem(*cell);
            item->setText(QString::number(sp.getItem(i,j)));
            ui->spTable->setItem(i,j,item);
        }
    }
    ui->spTable->setItem(sp.getEmptyX(), sp.getEmptyY(), new QTableWidgetItem(*empty));
    ui->moves->setText("Moves: "+QString::number(sp.getMoves()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
}

void MainWindow::on_spTable_cellClicked(int row, int column)
{
    sp.reCalc(row, column);
    showTable();
    if (sp.isFinished()) {
        timer -> stop();
        if (QMessageBox::question(this, "Игра закончена!", "Победа! Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            QApplication::quit();
        else {
            ms = 0;
            s = 0;
            m = 0;
            sp.nullMovings();
            timer->start();
            sp.startGame();
            showTable();
        }
    }
}

void MainWindow::on_restartGame_triggered()
{
    ms = 0;
    m = 0;
    s = 0;
    sp.restartGame();
    showTable();
}

void MainWindow::on_newGame_triggered()
{
    ms = 0;
    m = 0;
    s = 0;
    sp.startGame();
    showTable();
}

void MainWindow::on_quit_triggered()
{
    QApplication::quit();
}

void MainWindow::TimerSlot()
{
    ms++;
    if (ms>=1000) {
        ms = 0;
        s++;
    }
    if (s>=60) {
        s=0;
        m++;
    }
    ui->minutes->setText(QString::number(m) + " : ");
    ui->seconds->setText(QString::number(s));
    ui->miliseconds->setText(" : " + QString::number(ms));
}
