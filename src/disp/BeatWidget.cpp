//
// Created by pc on 05-12-21.
//

#include "BeatWidget.h"

#include <QTimer>

namespace disp {
    BeatWidget::BeatWidget(QWidget* parent) : QWidget(parent) {
        setFixedHeight(90);
    }

    void BeatWidget::set_beat_score(float beat_score) {
        if (not m_is_blocked) {
            if (beat_score > 0.5) {
                m_intensity  = std::min(0.99f, beat_score);
                m_is_blocked = true;
                QTimer::singleShot(m_beat_cooldown_msec, [this] { m_is_blocked = false; });
            }
        }
        repaint();
    }

    void BeatWidget::paintEvent(QPaintEvent* event) {
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, QColor{static_cast<int>(m_intensity * 255.0f), static_cast<int>(m_intensity * 255.0f), static_cast<int>(m_intensity * 255.0f)});
        setAutoFillBackground(true);
        setPalette(pal);
        m_intensity *= 0.99;
        QWidget::paintEvent(event);
    }
} // namespace disp
