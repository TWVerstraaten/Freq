//
// Created by pc on 05-12-21.
//

#include "WidgetBase.h"

namespace disp {

    WidgetBase::WidgetBase(QWidget* parent) : QWidget(parent) {
        setFixedHeight(140);
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, QColor{158, 153, 175});
        setAutoFillBackground(true);
        setPalette(pal);
    }

    void WidgetBase::set_type(WidgetBase::TYPE type) {
        m_type = type;
    }
} // namespace disp