/*
 * Tiedosto: main.cpp
 * Kuvaus: Ohjelman aloituspiste. Luo MainWindow-olion ja käynnistää Qt-sovelluksen.
 * Tekijä: Tiina Salmi
 * Projekti: student/07/chess
 */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
