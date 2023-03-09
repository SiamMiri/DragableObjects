#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(800, 400);
    setMouseTracking(true); // Enable mouse move events
    QPushButton *addBoxButton = new QPushButton("Add Box", this);
    addBoxButton->setGeometry(10, 10, 80, 30);

    m_pane = new Pane(0, 0, this);
    qDebug() << this->width() << "   " << this->height();
    m_pane->setGeometry(this->width()/3, 10, (this->width()/3)*2, this->height() - 40);


    connect(addBoxButton, &QPushButton::clicked, [=]() {
        bool ok;
        QString name = QInputDialog::getText(this, "Add Box", "Name:", QLineEdit::Normal, "", &ok);

        BoxWidget *object = m_pane->findChild<BoxWidget *>(name);

        if (object){
            QMessageBox::information(this, "Error", "The given name exist.");

        }else{
            if (ok && !name.isEmpty()) {
                BoxWidget *box = new BoxWidget(m_pane);
                box->setName(name);
                box->setPosition(QPoint(100, 200));
                box->setObjectName(name);
                box->show();
            }
        }
    });
}

void MainWindow::resizeEvent(QResizeEvent *event){
    m_pane->setGeometry(this->width()/3, 10, (this->width()/3)*2, this->height() - 20);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Check if mouse is pressed over a box widget
        BoxWidget *pressedBox = qobject_cast<BoxWidget *>(childAt(event->pos()));
        if (pressedBox) {
            // Connect the line widget to the mouse release event to check if it is connected to another box
            connect(this, &MainWindow::mouseReleaseEvent, [=](QMouseEvent *event) {
                if (event->button() == Qt::LeftButton) {
                    // Check if the line intersects with any other box
                    BoxWidget *intersectedBox = qobject_cast<BoxWidget *>(childAt(event->pos()));
                    if (intersectedBox && intersectedBox != pressedBox) {

                    } else {
                        // Delete the line widget if it doesn't connect to any other box
                        qDebug() << "Passed";
                    }

                    // Disconnect the line widget from the mouse move and mouse release events
                    disconnect(this, &MainWindow::mouseMoveEvent, nullptr, nullptr);
                    disconnect(this, &MainWindow::mouseReleaseEvent, nullptr, nullptr);
                }
            });
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // Call the base class implementation
    QMainWindow::mouseReleaseEvent(event);

    // Do your custom mouse release event handling here
    // ...
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Implementation code for the mouseMoveEvent function
}


MainWindow::~MainWindow()
{
    delete ui;
}
