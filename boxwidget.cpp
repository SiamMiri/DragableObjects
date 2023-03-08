#include "boxwidget.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

BoxWidget::BoxWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(50, 50);
    QLabel *label = new QLabel(this);
    label->setText(m_name);
    label->setAlignment(Qt::AlignCenter);
    label->move(10, 10);
}

QString BoxWidget::name() const
{
    return m_name;
}

void BoxWidget::setName(const QString &name)
{
    m_name = name;
    QLabel *label = findChild<QLabel *>();
    if (label)
        label->setText(name);
}

QPoint BoxWidget::position() const
{
    return m_position;
}

void BoxWidget::setPosition(const QPoint &position)
{
    m_position = position;
    move(position);
    update();
}

void BoxWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void BoxWidget::mousePressEvent(QMouseEvent *event)
{
    m_dragStartPosition = event->pos();

    if (event->button() == Qt::LeftButton) {
            emit boxClicked(this);
            m_dragging = true;
            m_dragStart = event->pos();
            event->accept();
        }
}

void BoxWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - m_dragStartPosition;
        setPosition(m_position + delta);
    }
}

void BoxWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        emit positionChanged(pos());
    }
}
