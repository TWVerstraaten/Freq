//
// Created by pc on 05-12-21.
//

#ifndef H_SRC_DISP_WIDGETBASE_H
#define H_SRC_DISP_WIDGETBASE_H

#include <QWidget>

namespace disp {

    class WidgetBase : public QWidget {
        Q_OBJECT

      public:
        enum class TYPE { NON_NEGATIVE, POSITIVE_AND_NEGATIVE };

        explicit WidgetBase(QWidget* parent);

        void set_type(TYPE type);

      protected:
        TYPE m_type = TYPE::NON_NEGATIVE;
    };

} // namespace disp

#endif // H_SRC_DISP_WIDGETBASE_H
