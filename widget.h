#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qwt_thermo.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_curve.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_color_map.h>
#include <qwt_scale_engine.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>


class Widget : public QWidget
{
    Q_OBJECT

    static constexpr int plotDataSize = 100;
    static constexpr double gain = 7.5;

    QPushButton  *button;
    QwtThermo    *thermo;
    QwtPlot      *plot;
    QwtPlotCurve *curve;

    // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
    QVBoxLayout  *vLayout;  // vertical layout
    QHBoxLayout  *hLayout;  // horizontal layout

    // data arrays for the plot
    double xData[plotDataSize];
    double yData[plotDataSize];

    long count = 0;

    void reset();

public:
     Widget(QWidget *parent = nullptr);
    ~Widget();

     void timerEvent( QTimerEvent * );
};
#endif // WIDGET_H
