#include "disp/AudioWidget.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("smoke");
    disp::AudioWidget widget;
    widget.show();
    return app.exec();
}
