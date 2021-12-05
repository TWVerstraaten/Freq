//
// Created by pc on 05-12-21.
//

#ifndef H_SRC_DISP_HISTORYWIDGET_H
#define H_SRC_DISP_HISTORYWIDGET_H

#include "../audio/Types.h"
#include "WidgetBase.h"

#include <QWidget>

namespace disp {

    class HistoryWidget : public WidgetBase {
        Q_OBJECT

      public:
        explicit HistoryWidget(QWidget* parent, float scale, QString name);

        void set_buffer(const audio::HistoryBuffer& buffer);

      protected:
        void paintEvent(QPaintEvent* event) override;

      private:
        float                m_scale;
        QString              m_name;
        audio::HistoryBuffer m_history_buffer;
    };

} // namespace disp

#endif // H_SRC_DISP_HISTORYWIDGET_H
