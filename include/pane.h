#ifndef PANE_H
#define PANE_H

#include <QWidget>
#include <QGridLayout>
#include <QWheelEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

class Pane : public QWidget
{
    Q_OBJECT

public:
    explicit Pane(int x, int y, QWidget *parent = nullptr);
    ~Pane();

signals:
    void zoomIn();
    void zoomOut();

protected:
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void scrollValueChanged(int value);
    void zoomInButtonClicked();
    void zoomOutButtonClicked();
    void updateWidgetSize();


private:
    QScrollBar *m_scrollBar = nullptr;
    QPalette m_palette;
    double m_scaleFactor = 1.0;
    QLabel *m_zoomLabel;
    QPushButton *m_zoomInButton;
    QPushButton *m_zoomOutButton;
    QPropertyAnimation *m_animation;
    QGridLayout *m_layout;
    void updateZoomLabel();
};

#endif // PANE_H
