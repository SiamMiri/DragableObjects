#include "pane.h"

Pane::Pane(int x, int y, QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground(true);
    m_palette.setColor(QPalette::Window, Qt::white);
    setPalette(m_palette);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    move(x,y);
}

void Pane::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        int delta = event->angleDelta().y();
        if (delta > 0) {
            emit zoomIn();
        } else if (delta < 0) {
            emit zoomOut();
        }
        event->accept();
    } else {
        QWidget::wheelEvent(event);
    }
}

void Pane::setScrollBar(QScrollBar *scrollBar)
{
    m_scrollBar = scrollBar;
    connect(m_scrollBar, &QScrollBar::valueChanged, this, &Pane::scrollValueChanged);
}

void Pane::scrollValueChanged(int value)
{
    Q_UNUSED(value);
    update();
}
