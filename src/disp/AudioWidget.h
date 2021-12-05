#ifndef H_APP_DISP_MAINWINDOW_H
#define H_APP_DISP_MAINWINDOW_H

#include "../audio/Player.h"
#include "../audio/SoundWindow.h"
#include "BeatWidget.h"
#include "HistoryWidget.h"
#include "SpectrumWidget.h"

#include <QBasicTimer>
#include <QFormLayout>
#include <QWidget>

namespace disp {

    class AudioWidget : public QWidget {
        Q_OBJECT

      public:
        AudioWidget();

        void keyPressEvent(QKeyEvent* e) override;
        void timerEvent(QTimerEvent* e) override;

      private:
        audio::SoundWindow m_sound_window;
        audio::Player      m_player;
        QBasicTimer        m_timer;
        SpectrumWidget*    m_spectrum_widget;
        HistoryWidget*     m_wave_form_widget;
        HistoryWidget*     m_energy_widget;
        HistoryWidget*     m_energy_dif_widget;
        HistoryWidget*     m_energy_dif_dif_widget;
        BeatWidget*        m_energy_beat_widget;
        QFormLayout*       m_layout;
    };

} // namespace disp

#endif // H_APP_DISP_MAINWINDOW_H
