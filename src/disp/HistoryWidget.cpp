//
// Created by pc on 05-12-21.
//

#include "HistoryWidget.h"

#include <QPainter>

namespace disp {
    HistoryWidget::HistoryWidget(QWidget* parent, float scale, QString name) : WidgetBase(parent), m_scale(scale), m_name(std::move(name)) {
    }

    void HistoryWidget::set_buffer(const audio::HistoryBuffer& buffer) {
        m_history_buffer = buffer;
        for (size_t i = 0; i != audio::HistoryBuffer::size; ++i)
            m_history_buffer[i] *= m_scale;

        repaint();
    }

    void HistoryWidget::paintEvent([[maybe_unused]] QPaintEvent* event) {
        const size_t width = QWidget::width();
        const size_t buffer_length = audio::HistoryBuffer ::size;
        const size_t rectangle_width = (width + buffer_length - 1) / buffer_length;
        QPainter     painter(this);
        painter.setPen(QPen{QColor{100, 100, 100}});
        painter.drawLine(0, QWidget::height() / 2, QWidget::width(), QWidget::height() / 2);
        for (size_t i = 0; i != buffer_length; ++i) {
            if (m_type == TYPE::NON_NEGATIVE)
                painter.fillRect(i * width / (buffer_length + 1), QWidget::height() - m_history_buffer[i], rectangle_width, m_history_buffer[i], QBrush{QColor{0, 32, 128}});
            else
                painter.fillRect(i * width / (buffer_length + 1), QWidget::height() / 2 - m_history_buffer[i], rectangle_width, m_history_buffer[i], QBrush{QColor{0, 32, 128}});
        }
        if (m_type == WidgetBase::TYPE::NON_NEGATIVE) {
            painter.drawText(0, QWidget::height(), "0");
            painter.drawText(0, 20, QString::number(QWidget::height() / m_scale));
        }
        painter.setPen(QPen{QColor{255, 255, 255}});
        painter.drawText(QWidget::width() - 150, 20, m_name);
        QWidget::paintEvent(event);
    }
} // namespace disp