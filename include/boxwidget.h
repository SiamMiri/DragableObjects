#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>

class BoxWidget : public QWidget
{
    Q_OBJECT

public:
    BoxWidget(QWidget *parent = nullptr);
    ~BoxWidget();

    QString name() const;
    void setName(const QString &name);

    QPoint position() const;
    void setPosition(const QPoint &position);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel *label;
    QPoint m_dragStart; // declare m_dragStart as a member variable
    QString m_name;
    QPoint m_position;
    QPoint m_dragStartPosition;
    bool m_dragging = false;

signals:
    void positionChanged(const QPoint &position);
    void boxClicked(BoxWidget *box);
};


#endif // BOXWIDGET_H
