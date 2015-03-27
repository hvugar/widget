#ifndef QHEXSCROLLAREA_H
#define QHEXSCROLLAREA_H

#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtCore/QTimer>
#include <QtCore/QRect>


#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QFontDatabase>
#include <QtGui/QFont>

#include <math.h>
#include <time.h>

class QHexScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit QHexScrollArea(QWidget *parent = 0);
    virtual ~QHexScrollArea();

    void setMaxDataCount(qint64);
    void setBytesPerRow(qint32);

    void setFilename(const QString& filename);

    QString filename;
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void wheelEvent(QWheelEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

    virtual bool viewportEvent(QEvent *);
    virtual void scrollContentsBy ( int dx, int dy );
    virtual void timerEvent(QTimerEvent *);

private:
    qint64 maxDataCount;
    qint64 maxRowsCount;
    qint64 bytesPerRow;
    qint64 selectedByte;
    bool mShowUpperData;
    bool mShowUpperLine;
    bool blinking;

    void paintRowNumber(QPainter& painter);
    void paintBorders(QPainter& painter);
    void paintSelections(QPainter& painter);
    void paintSelection(QPainter& painter);
    void paintBlinking(QPainter& painter);

    int stringWidth(const QString&) const;
    QRect byteRect(const QPoint& pos) const;

    qint64 getRowNumberWidth() const;
    qint64 getByteNumberWidth() const;
    qint64 getDataPanelWidth() const;

signals:
    qint32 fillBuffer(QByteArray& buffer, qint64 min, qint64 max);
    
public slots:
    
};

#endif // QHEXSCROLLAREA_H
