#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>

#include "boxwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pane.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class BoxWidget;
class Pane;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    Pane *m_pane;
    BoxWidget *m_selectedBox = nullptr;
    QPoint m_dragStartPosition;
    bool m_isDragging = false;

    QList<BoxWidget*> m_boxes;

    void addBox();
};
#endif // MAINWINDOW_H
