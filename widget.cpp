#include "widget.h"
#include<random>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    plot = new QwtPlot;

    int rows = 100; // Number of rows in the matrix
    int columns = 100; // Number of columns in the matrix


    QVector<double> dopplerVector ;
    std::vector<std::vector<double>> dopplerVector2(rows, std::vector<double>(columns));
    double c = 0.842;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            double x = i / static_cast<double>(rows);
            double y = j / static_cast<double>(columns);
            double v1 = x * x + (y - c) * (y + c);
            double v2 = x * (y + c) + x * (y + c);
            dopplerVector2[i][j] = 1.0 / (v1 * v1 + v2 * v2);
        }
    }
    for (int i = 0; i < rows; ++i) {
        dopplerVector+=QVector<double>::fromStdVector(dopplerVector2[i]);
    }

//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<double> distribution(0.0, 1.0);

//    // Generate random values between 0 and 1
//    for (int i = 0; i < 100*100; ++i)
//    {
//        double randomValue = distribution(gen);
//        dopplerVector.append(randomValue);
//    }


    QList<double> contourLevels;
    for ( double level = 0.5; level < 10.0; level += 1.0 )
        contourLevels += level;

    QVector<double> heat_values( 100 * 100 );
    for( int n = 0; n < 100 * 100; ++n ) {
        heat_values[n] = ( n % 100 ) + n / 100;
    };

    QwtPlotSpectrogram *heat =new QwtPlotSpectrogram;
    auto heat_data = std::make_unique<QwtMatrixRasterData>();
    heat_data->setValueMatrix( dopplerVector, 100 );
    heat_data->setResampleMode(
        QwtMatrixRasterData::ResampleMode::NearestNeighbour );
    heat_data->setInterval( Qt::XAxis, QwtInterval( -1.5, 1.5) );
    heat_data->setInterval( Qt::YAxis, QwtInterval( -1.5, 1.5 ) );
    heat_data->setInterval( Qt::ZAxis, QwtInterval( 0, 10.0 ) );

    heat->setDisplayMode( QwtPlotSpectrogram::DisplayMode::ImageMode, true );

    QwtLinearColorMap *cm= new QwtLinearColorMap( Qt::darkCyan, Qt::red ,QwtColorMap::RGB );
    cm->addColorStop(0.1,Qt::cyan);
    cm->addColorStop(0.6,Qt::green);
    cm->addColorStop(0.95,Qt::yellow);
    QwtColorMap *rgb = cm;

//    rgb->colorIndex(Qt::cyan,.1);
//    heat->setColorMap( new QwtLinearColorMap( Qt::red, Qt::blue ) );
    heat->setColorMap(rgb);

    heat->setContourLevels(contourLevels);
    heat->setDisplayMode( QwtPlotSpectrogram::ContourMode, 0 );
    heat->setData( heat_data.release() );
    heat->attach(plot);
    plot->repaint();
    



    QwtMatrixRasterData *data = new QwtMatrixRasterData();



    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            double value = 1; // Set the value for the specific cell
            data->setValue(column, row, value);
        }
    }

    data->setInterval(Qt::XAxis, QwtInterval(0, columns));
    data->setInterval(Qt::YAxis, QwtInterval(0, rows));
    data->setInterval(Qt::ZAxis, QwtInterval(0, 1)); // Adjust the range according to your data

//    auto x=data->valueMatrix();
//    QVector<int> t;
//    t.append(2);
//    qInfo()<<t;

//    QwtPlotSpectrogram *spectrogram = new QwtPlotSpectrogram;


//    QwtLinearColorMap colorMap(Qt::blue, Qt::red);

//    spectrogram->setAlpha(75);
//    spectrogram->setData(data);
//    spectrogram->attach(plot);






    thermo = new QwtThermo;
    thermo->setFillBrush( QBrush(Qt::red) );
    thermo->setScale(0, 10);
    thermo->show();

//    for( int index=0; index<plotDataSize; ++index )
//    {
//        xData[index] = index;
//        yData[index] = 0;
//    }

//    curve = new QwtPlotCurve;


//    curve->setSamples(xData, yData, plotDataSize);
//    curve->attach(plot);

//    plot->replot();
    plot->show();

    button = new QPushButton("Reset");

    connect(button,&QPushButton::clicked,this,&Widget::reset);

    // set up the layout - button above thermometer
    vLayout = new QVBoxLayout();
    vLayout->addWidget(button);
    vLayout->addWidget(thermo);

    // plot to the left of button and thermometer
    hLayout = new QHBoxLayout();
    hLayout->addLayout(vLayout);
    hLayout->addWidget(plot);

//    setLayout(hLayout);

    this->setLayout(hLayout);


//    this->setLayout(mainLayout);
}

Widget::~Widget()
{
}
void Widget::reset(){
    for( int index=0; index<plotDataSize; ++index )
    {
        xData[index] = index;
        yData[index] = 0;
    }
}

void Widget::timerEvent( QTimerEvent * )
{
    double inVal = gain * sin( M_PI * count/50.0 );
    ++count;

    // add the new input to the plot
    std::move( yData, yData + plotDataSize - 1, yData+1 );
    yData[0] = inVal;
    curve->setSamples(xData, yData, plotDataSize);
    plot->replot();

    // set the thermometer value
    thermo->setValue( fabs(inVal) );
}
