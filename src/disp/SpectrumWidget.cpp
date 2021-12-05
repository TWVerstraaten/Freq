//
// Created by pc on 05-12-21.
//

#include "SpectrumWidget.h"

#include <QDebug>
#include <QLine>
#include <QPainter>

namespace disp {

    SpectrumWidget::SpectrumWidget(QWidget* parent) : WidgetBase(parent) {
    }

    void SpectrumWidget::set_buffer(const audio::DftBuffer& buffer) {
        m_dft_buffer = buffer;
        repaint();
    }

    void SpectrumWidget::paintEvent(QPaintEvent* event) {
        const size_t width = QWidget::width();
        const size_t buffer_length = audio::DftBuffer::size;
        const size_t rectangle_width = (width + buffer_length - 1) / buffer_length;
        QPainter     painter(this);

        for (size_t i = 0; i != buffer_length; ++i) {
            painter.fillRect(i * width / (buffer_length + 1), QWidget::height() - m_dft_buffer[i], rectangle_width, m_dft_buffer[i], QBrush{QColor{0, 32, 128}});
        }
        QWidget::paintEvent(event);
    }

} // namespace disp
