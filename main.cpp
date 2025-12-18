#include <QApplication>
#include <QStyleFactory>
#include "headers/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setStyle(QStyleFactory::create("Fusion"));
    
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    app.setPalette(darkPalette);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}