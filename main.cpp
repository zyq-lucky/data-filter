#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QSet>
#include <QString>
#include <fstream>
#include <iostream>
#include <map>

QString Get(QString s) {
  return s.mid(s.indexOf("[") + 1, s.indexOf("]") - s.indexOf("[") - 1);
}

QString GetFirst(QString s) { return s.mid(0, s.indexOf(" ")); }

QString Clip(QString s) {
  return s.mid(s.indexOf(".") + 1, s.indexOf("[") - s.indexOf(".") - 1);
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget w;
  QString txtfileName = QFileDialog::getOpenFileName(&w);
  QFile txtfile(txtfileName);

  if (!txtfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Can't open the file!" << endl;
  }

  QSet<QString> ids;
  QFile csvFile("p_data.csv");
  if (csvFile.open(QIODevice::ReadWrite)) {
    while (!txtfile.atEnd()) {
      QByteArray line = txtfile.readLine();
      QString str(line);
      QString tmp = Get(str);
      qDebug() << tmp;
      if (ids.find(tmp) == ids.end()) {
        ids.insert(tmp);
        QString title = GetFirst(tmp);
        if (title != tmp) {
          QString tmp2 = title + "," + tmp + "," + Clip(str) + "\n";
          csvFile.write(tmp2.toUtf8());
          qDebug() << tmp2;
        }
      }
      txtfile.readLine();
      txtfile.readLine();
      txtfile.readLine();
    }
    csvFile.close();
  }
  txtfile.close();

  //  QString csvFileName = QFileDialog::getOpenFileName(&w);
  //  QFile csvFile(csvFileName);

  //  if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
  //    qDebug() << "Can't open the file!" << endl;
  //  }

  //  QFile countFile("p_count.csv");
  //  std::map<QString, int> counts;

  //  if (countFile.open(QIODevice::ReadOnly)) {
  //    while (!countFile.atEnd()) {
  //      QString tmp = csvFile.readLine();
  //      QString title = tmp.mid(0, tmp.indexOf(","));
  //      counts[title]++;
  //    }

  //    for (auto pair : counts) {
  //      countFile.write(
  //          (pair.first + "," + QString::number(pair.second) +
  //          "\n").toUtf8());
  //    }
  //    countFile.close();

  //  }
  //  csvFile.close();

  qDebug() << "finish";
  return 0;
}
