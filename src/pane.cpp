#include "pane.h"

Pane::Pane(int x, int y, QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground(true);
    m_palette.setColor(QPalette::Window, Qt::white);
    setPalette(m_palette);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    // Add zoom label and buttons
    m_zoomLabel = new QLabel("Zoom: 100%", this);
    m_zoomInButton = new QPushButton("+", this);
    m_zoomOutButton = new QPushButton("-", this);

    m_layout->addWidget(m_zoomLabel, 0, 0);
    m_layout->addWidget(m_zoomInButton, 0, 1);
    m_layout->addWidget(m_zoomOutButton, 0, 2);

    m_scrollBar = new QScrollBar(Qt::Horizontal, this);
    m_animation = new QPropertyAnimation(this, "geometry");

    // Connect signals and slots for zooming
    connect(m_scrollBar, &QScrollBar::valueChanged, this, &Pane::scrollValueChanged);
    connect(m_animation, &QPropertyAnimation::finished, this, &Pane::updateWidgetSize);
    connect(m_zoomInButton, &QPushButton::clicked, this, &Pane::zoomInButtonClicked);
    connect(m_zoomOutButton, &QPushButton::clicked, this, &Pane::zoomOutButtonClicked);

    move(x,y);
}

void Pane::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if (event->modifiers() & Qt::ControlModifier) {
        m_scaleFactor += numSteps / 10.0;

        if (m_scaleFactor < 0.1) {
            m_scaleFactor = 0.1;
        }

        if (m_scaleFactor > 10.0) {
            m_scaleFactor = 10.0;
        }

        updateWidgetSize();
        update();
    } else {
        QWidget::wheelEvent(event);
    }
}

void Pane::scrollValueChanged(int value)
{
    m_layout->setSpacing(value);
    updateWidgetSize();
}

void Pane::zoomInButtonClicked()
{
    m_scaleFactor += 0.1;
    updateWidgetSize();
}

void Pane::updateWidgetSize()
{
    // Calculate the new size of the widget based on the current scale factor
    QSize newSize = QSize(width() * m_scaleFactor, height() * m_scaleFactor);

    // Set the new size of the widget
    setFixedSize(newSize);

    // Update the size of all child widgets
    QList<QWidget *> childWidgets = findChildren<QWidget *>();
    for (QWidget *widget : childWidgets) {
        QSize oldSize = widget->size();
        QSize newSize = QSize(oldSize.width() * m_scaleFactor, oldSize.height() * m_scaleFactor);
        widget->resize(newSize);
    }
}

void Pane::updateZoomLabel()
{
    int percentage = static_cast<int>(m_scaleFactor * 100);
    m_zoomLabel->setText(QString("Zoom: %1%").arg(percentage));
}

void Pane::zoomOutButtonClicked()
{
    if (m_scaleFactor > 0.1)
    {
        m_scaleFactor -= 0.1;
        updateZoomLabel();

        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(250);
        animation->setStartValue(geometry());
        animation->setEndValue(QRect(0, 0, width() / m_scaleFactor, height() / m_scaleFactor));
        animation->start();
    }
}

Pane::~Pane()
{
    delete m_scrollBar;
    delete m_layout;
    delete m_scrollBar;
    delete m_animation;
    qDebug() << "Pane Destructed\n" ;
}
