#include <QtGui>
#include <QtDebug>

#include "plotter.h"

void readDive(Plotter *plotter, const QString &fileName)
{
    QVector<QPointF> data;
    QFile file(fileName);
    int lineCount = 0;
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "opened a read only file called " << fileName;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList coords = line.split('|');
            double x = coords[0].toDouble();
            double y = coords[1].toDouble();
            data.append(QPointF(x,y));
            lineCount++;
        }
        qDebug() << "read " << lineCount << " lines from " << fileName;
    } else {
        qDebug() << "Failed to open " << fileName;
    }
    plotter->setCurveData(0, data);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Plotter plotter;
    plotter.setWindowTitle(QObject::tr("Dive Plotter"));
    readDive(&plotter, "dive.txt");
    plotter.show();
    return app.exec();
}
