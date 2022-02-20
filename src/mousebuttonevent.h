#ifndef MOUSEBUTTONEVENT_H
#define MOUSEBUTTONEVENT_H

#include <QtCore/QObject>
#include <QtGui/QMouseEvent>


class MouseButtonEvent : public QObject
{
    Q_OBJECT
protected:
    bool eventFilter(QObject* object, QEvent* event)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            OnMouseButtonRelease();

            QMouseEvent* moustEvent = static_cast<QMouseEvent*>(event);
            switch (moustEvent->button())
            {
                case Qt::LeftButton:
                {
                    OnLMBRelease();
                    break;
                }
                case Qt::MidButton:
                {
                    OnMMBRelease();
                    break;
                }
                case Qt::RightButton:
                {
                    OnRMBReleas();
                    break;
                }   
            }
        }
        return false; // mark as unhandled to proprapate the event.
    }
public:
    static void OnMouseButtonRelease();
    static void OnRMBRelease();
    static void OnMMBRelease();
    static void OnLMBRelease();
};

#endif
