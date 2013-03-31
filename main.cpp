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


/* A dive plot widget prototype to show proof of concept.
 *
 * Based on example from GUI Programming with Qt4 (Summerfield/Blanchette).
 *
 * We read a dive in from a simple text file and render the dive plot on
 * a QWidget using basic QPainter operations.  We show the colour of the
 * depth profile changing with dy/dx, the ability to fill the enclosed area
 * with a gradient and some simple drawing and text placement.
 *
 * Panning and zooming are pretty much unaltered from the example, with the
 * exception of mods to reverse the direction of the vertical axis to use
 * a "going down means counting up" convention which makes more sense for
 * a dive.
 *
 * Aim is to show proof of concept to non-Qt programmers working on subsurface.
 * Question: what if any capabilities are needed that aren't on show here?
 *
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Plotter plotter;
    plotter.setWindowTitle(QObject::tr("Dive Plotter"));
    readDive(&plotter, "dive.txt");
    plotter.show();
    return app.exec();
}
