//
// Created by pc on 05-12-21.
//

#ifndef H_SRC_DISP_BEATWIDGET_H
#define H_SRC_DISP_BEATWIDGET_H

#include <QWidget>

namespace disp {

    class BeatWidget : public QWidget {
        Q_OBJECT

      public:
        explicit BeatWidget(QWidget* parent);

        void set_beat_score(float beat_score);

      protected:
        void paintEvent(QPaintEvent* event) override;

      private:
        bool   m_is_blocked         = false;
        float  m_intensity          = 0.0f;
        size_t m_beat_cooldown_msec = 120;
    };

} // namespace disp

#endif // H_SRC_DISP_BEATWIDGET_H
