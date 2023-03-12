#ifndef PANE_H
#define PANE_H

#include <QWidget>
#include <QGridLayout>
#include <QWheelEvent>
#include <QScrollBar>

class Pane : public QWidget
{
    Q_OBJECT

public:
    explicit Pane(int x, int y, QWidget *parent = nullptr);
    void setScrollBar(QScrollBar *scrollBar);

signals:
    void zoomIn();
    void zoomOut();

protected:
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void scrollValueChanged(int value);

private:
    QScrollBar *m_scrollBar = nullptr;
    QPalette m_palette;
};

#endif // PANE_H
