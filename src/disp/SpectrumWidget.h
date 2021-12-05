//
// Created by pc on 05-12-21.
//

#ifndef H_SRC_DISP_SPECTRUMWIDGET_H
#define H_SRC_DISP_SPECTRUMWIDGET_H

#include "../audio/Types.h"
#include "WidgetBase.h"

#include <QWidget>

namespace disp {
    class SpectrumWidget : public WidgetBase {
        Q_OBJECT

      public:
        explicit SpectrumWidget(QWidget* parent);

        void set_buffer(const audio::DftBuffer& buffer);

      protected:
        void paintEvent(QPaintEvent* event) override;

      private:
        audio::DftBuffer m_dft_buffer;
    };

} // namespace disp

#endif // H_SRC_DISP_SPECTRUMWIDGET_H
