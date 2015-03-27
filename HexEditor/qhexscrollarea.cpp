#include "qhexscrollarea.h"

QHexScrollArea::QHexScrollArea(QWidget *parent) : QScrollArea(parent)
{
    maxDataCount = 0;
    bytesPerRow = 16;
    maxRowsCount = 0;
    selectedByte = -1;
    blinking = true;
    mShowUpperData = false;
    mShowUpperLine = false;

    resize(800, 600);
//    setWindowState(Qt::WindowMaximized);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    viewport()->setBackgroundRole(QPalette::Base);

    QFont font;
#ifdef Q_OS_LINUX
    font.setFamily("Monospace");
#else
    int id = QFontDatabase::addApplicationFont(":/fonts/resources/fonts/consola.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font.setFamily(family);
#endif
    font.setPointSize(12);
//    font.setBold(true);

    setFont(font);
    setMouseTracking(true);
//    startTimer(QApplication::cursorFlashTime()/2);
}

QHexScrollArea::~QHexScrollArea()
{}

void QHexScrollArea::setMaxDataCount(qint64 size)
{
    maxDataCount = size;

    int div = maxDataCount / bytesPerRow;
    int mod = maxDataCount % bytesPerRow;

    maxRowsCount = div;
    if (mod > 0) maxRowsCount++;
}

void QHexScrollArea::setBytesPerRow(qint32)
{

}

void QHexScrollArea::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter;
    painter.begin(viewport());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    painter.fillRect(0,0,width(), height(), QBrush(0xD7D7AF));

    QFont font = this->font();
    QFontMetrics fm = this->fontMetrics();

    painter.setFont(font);

    int ssw = fm.width(" ");                                                // width of space symbol
    int zsw = fm.width("0");                                                // width of zero symbol

    int div = maxDataCount / bytesPerRow;                                   // data size divide to 16. number of maximum rows
    int mod = maxDataCount % bytesPerRow;                                   // data size module to 16. number of bytes at last row

    maxRowsCount = div;
    if (mod > 0) maxRowsCount += 1;

    int rowNumberW = 2 * ssw + fm.width(QString::number(maxRowsCount));     // width of row number column
    int rowNumberH = viewport()->height();                                  // height of row number column

    // painting lines number column background
    painter.fillRect(0, 0, rowNumberW, rowNumberH, QBrush(0xD4D0C8));
    painter.fillRect(getRowNumberWidth(), 0, getByteNumberWidth(), height(), QBrush(QColor(0xAFAF87)));
    painter.fillRect(getRowNumberWidth(), 0, width(), fm.height()+4, QBrush(QColor(0xAFAF87)));

    // number of rows visible on viewport
    int viewportRow = (int) ceil( (double)(viewport()->height() - (double)fm.height() ) / (double)fm.height() );

    // updating verticalScrollBar settings
    verticalScrollBar()->setMinimum(0);

    if (maxRowsCount > viewportRow)
    {
        verticalScrollBar()->setMaximum( (maxRowsCount - viewportRow) + 1);
    }
    else
    {
        verticalScrollBar()->setMaximum(0);
    }

    verticalScrollBar()->setPageStep(10);
    verticalScrollBar()->setSingleStep(1);

    int vsbValue = verticalScrollBar()->value();
    int hsbValue = horizontalScrollBar()->value();
    Q_UNUSED(hsbValue)

    font.setBold(false);
    painter.setFont(font);

    // painting header
    painter.setPen(0x5F5F00);
    int x = rowNumberW+zsw*8 + ssw*2;
    int y = fm.height();
    painter.drawText(x, y, " 00 01 02 03  04 05 06 07   08 09 0A 0B  0C 0D 0E 0F                     ");

    qint64 minLine = vsbValue;                                          // minimum visible line number
    qint64 maxLine = vsbValue + viewportRow;                            // maximum visible line number

    if (maxRowsCount < maxLine)
        maxLine = maxRowsCount;

    qint64 minData = minLine * bytesPerRow;                             // minimum visible byte
    qint64 maxData = maxLine * bytesPerRow;                             // maximum visible data

    if ( maxData > maxDataCount)
    {
        maxData = maxDataCount;
    }

    QByteArray buffer;
    emit fillBuffer(buffer, minData, maxData);

    for (qint64 i = minLine; i < maxLine; i++)
    {
        quint32 x = zsw;
        quint32 y = (i-vsbValue+1)*fm.height() + fm.height();

        QByteArray data = buffer.mid( (int)( i - minLine ) * 16, 16);

        QString line = QString::number(i);
//       int length = 9-line.length();
        int length = QString::number(maxRowsCount).length() - QString::number(i).length();
        for (int j=0; j<length; j++)
            line.prepend(" ");
        if (mShowUpperLine) line = line.toUpper();

        /* bytes number and filling 0 to start*/
        QString bytes = QString::number(i*bytesPerRow,16);
        length = 8-bytes.length();
        for (int j=0; j<length; j++)
            bytes.prepend("0");
        if (mShowUpperData)
            bytes = bytes.toUpper();

        /* data hex string */
        QString h = QString("%1 %2 %3 %4  %5 %6 %7 %8   %9 %10 %11 %12  %13 %14 %15 %16")
                .arg(QString(data.mid(0x00, 1).toHex()))
                .arg(QString(data.mid(0x01, 1).toHex()))
                .arg(QString(data.mid(0x02, 1).toHex()))
                .arg(QString(data.mid(0x03, 1).toHex()))
                .arg(QString(data.mid(0x04, 1).toHex()))
                .arg(QString(data.mid(0x05, 1).toHex()))
                .arg(QString(data.mid(0x06, 1).toHex()))
                .arg(QString(data.mid(0x07, 1).toHex()))
                .arg(QString(data.mid(0x08, 1).toHex()))
                .arg(QString(data.mid(0x09, 1).toHex()))
                .arg(QString(data.mid(0x0A, 1).toHex()))
                .arg(QString(data.mid(0x0B, 1).toHex()))
                .arg(QString(data.mid(0x0C, 1).toHex()))
                .arg(QString(data.mid(0x0D, 1).toHex()))
                .arg(QString(data.mid(0x0E, 1).toHex()))
                .arg(QString(data.mid(0x0F, 1).toHex()));
         h = h.toLower();

        /* data char string */
        QString c;
        for (int j=0; j < data.size(); j++)
        {
            c.append(QChar(data.at(j)).isPrint() ? QChar(data.at(j)) : '.');
        }

        /* drawing row number */
        font.setBold(true);
        painter.setFont(font);
        painter.setPen(0x5F5F00);
        painter.drawText(x, y, line);

        /* drawing data sequence number */
        x = rowNumberW + zsw;
        font.setBold(false);
        painter.setFont(font);
        painter.setPen(0x5F5F00);
        painter.drawText(x, y, bytes);

        /* drawing data */
        x = x + zsw*8 + ssw*2;
        painter.setPen(0x5F5F00);
        painter.drawText(x, y, h);
        x += zsw*32 + ssw*22;
        painter.drawText(x, y, c);
    }

    // paint selection

    painter.setRenderHint(QPainter::Antialiasing, false);

    if (selectedByte != -1)
    {
        quint32 cn = selectedByte % bytesPerRow;                           // column number
        quint32 rn = selectedByte / bytesPerRow;                           // row number

        quint32 sel_x = rowNumberW + zsw * 8 + ssw * 3;
        sel_x -=  ssw / 2;

        if (cn >= 0 && cn <= 3)
            sel_x += cn * zsw * 3;
        if (cn >= 4 && cn <= 7)
            sel_x += cn * zsw * 3 + zsw * 1;
        if (cn >= 8 && cn <= 11)
            sel_x += cn * zsw * 3 + zsw * 3;
        if (cn >= 12 && cn <= 15)
            sel_x += cn * zsw * 3 + zsw * 4;

        quint32 rw = ssw * 3 - 2;                                           // selected rectange width

        quint32 sel_y = 0;
        if (minLine <= rn && rn <= maxLine)
        {
            rn -= minLine;
            sel_y = fm.height() * (rn+1);
        }
        else
        {
            sel_y = -100;
        }

        QBrush brush(QColor(0x00, 0xff, 0xff, 100));
        painter.fillRect(sel_x, sel_y+4, rw, 18, brush);           // painting selected byte
        painter.drawRect(sel_x, sel_y+4, rw, 18);                       // painting selected byte
    }

//    paintSelections(painter);

//    paintSelection(painter);

//    paintBlinking(painter);

    painter.end();
}

void QHexScrollArea::paintBorders(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    //    painter.drawLine(fm.width(" 00000000  00000000 "), fm.height()+4, fm.width(" 00000000  00000000 "), viewport()->height());
    //    painter.drawLine(fm.width(" 00000000  00000000 ")+3, fm.height()+4, fm.width(" 00000000  00000000 ")+3, viewport()->height());
    //    painter.drawLine(fm.width(" 00000000  00000000 00 00 00 00  00 00 00 00   00 00 00 00  00 00 00 00   "),
    //                     fm.height()+4,
    //                     fm.width(" 00000000  00000000 00 00 00 00  00 00 00 00   00 00 00 00  00 00 00 00   "),
    //                     viewport()->height());
    //    painter.drawLine(fm.width(" 00000000  00000000 00 00 00 00  00 00 00 00   00 00 00 00  00 00 00 00   ")+3,
    //                     fm.height()+4,
    //                     fm.width(" 00000000  00000000 00 00 00 00  00 00 00 00   00 00 00 00  00 00 00 00   ")+3,
    //                     viewport()->height());
    //    painter.drawLine(fm.width(" 00000000  00000000 ")+3,
    //                     fm.height()+4,
    //                     fm.width(" 00000000  00000000 00 00 00 00  00 00 00 00   00 00 00 00  00 00 00 00   "),
    //                     fm.height()+4);
    //    painter.drawLine(fm.width(" 00000000 "),
    //                     fm.height()+4,
    //                     fm.width(" 00000000  00000000 "),
    //                     fm.height()+4);
    //    painter.drawLine(fm.width(" 00000000  00000000 00 00 00 00  00 00 00 00   00 00 00 00  00 00 00 00   ")+3,
    //                     fm.height()+4,
    //                     viewport()->width(),
    //                     fm.height()+4);
    painter.setRenderHint(QPainter::Antialiasing, true);
}

void QHexScrollArea::paintRowNumber(QPainter& painter)
{
    Q_UNUSED(painter)
}

void QHexScrollArea::paintSelections(QPainter& painter)
{}

void QHexScrollArea::paintSelection(QPainter& painter)
{}

void QHexScrollArea::paintBlinking(QPainter &painter)
{
    if (blinking) {}
}

void QHexScrollArea::mousePressEvent(QMouseEvent *e)
{
    QScrollArea::mousePressEvent(e);
}

void QHexScrollArea::mouseReleaseEvent(QMouseEvent *e)
{
    QScrollArea::mouseReleaseEvent(e);

    QFont font = this->font();
    QFontMetrics fm = this->fontMetrics();

    int ssw = fm.width(" ");                                            // width of space symbol
//    int zsw = fm.width("0");                                            // width of zero symbol

    qint64 rnw = getRowNumberWidth();       // width of row number panel
    qint64 bnw = getByteNumberWidth();      // width of bytes number panel
    qint64 dpw = getDataPanelWidth();
    qint64 dnw = rnw + bnw;

    int x = e->pos().x();
    int y = e->pos().y();

    qint64 selectedCol = -1;
    if ( dnw < x && x < dnw + dpw + ssw * 0.5)
    {
        if ((dnw + ssw * 0.5)  <= x && x < (dnw + ssw * 3.5))  selectedCol = 0;
        if ((dnw + ssw * 3.5)  <= x && x < (dnw + ssw * 6.5))  selectedCol = 1;
        if ((dnw + ssw * 6.5)  <= x && x < (dnw + ssw * 9.5))  selectedCol = 2;
        if ((dnw + ssw * 9.5)  <= x && x < (dnw + ssw * 12.5)) selectedCol = 3;
        if ((dnw + ssw * 13.5) <= x && x < (dnw + ssw * 16.5)) selectedCol = 4;
        if ((dnw + ssw * 16.5) <= x && x < (dnw + ssw * 19.5)) selectedCol = 5;
        if ((dnw + ssw * 19.5) <= x && x < (dnw + ssw * 22.5)) selectedCol = 6;
        if ((dnw + ssw * 22.5) <= x && x < (dnw + ssw * 25.5)) selectedCol = 7;
        if ((dnw + ssw * 27.5) <= x && x < (dnw + ssw * 30.5)) selectedCol = 8;
        if ((dnw + ssw * 30.5) <= x && x < (dnw + ssw * 33.5)) selectedCol = 9;
        if ((dnw + ssw * 33.5) <= x && x < (dnw + ssw * 36.5)) selectedCol = 10;
        if ((dnw + ssw * 36.5) <= x && x < (dnw + ssw * 39.5)) selectedCol = 11;
        if ((dnw + ssw * 40.5) <= x && x < (dnw + ssw * 43.5)) selectedCol = 12;
        if ((dnw + ssw * 43.5) <= x && x < (dnw + ssw * 46.5)) selectedCol = 13;
        if ((dnw + ssw * 46.5) <= x && x < (dnw + ssw * 49.5)) selectedCol = 14;
        if ((dnw + ssw * 49.5) <= x && x < (dnw + ssw * 52.5)) selectedCol = 15;

        qint64 selectedRow = ((y-4) / fm.height())-1 ;
        qint64 vsbValue = verticalScrollBar()->value();
        selectedRow += vsbValue;
        selectedByte = selectedRow * 16 + selectedCol;
    }

    viewport()->update();
}

void QHexScrollArea::mouseMoveEvent(QMouseEvent *e)
{
    QScrollArea::mouseMoveEvent(e);
    viewport()->update();
}

void QHexScrollArea::resizeEvent(QResizeEvent *e)
{
    QScrollArea::resizeEvent(e);
}

void QHexScrollArea::wheelEvent(QWheelEvent *e)
{
    QScrollArea::wheelEvent(e);

    int value = verticalScrollBar()->value() - e->delta() / 40;
    verticalScrollBar()->setValue(value);
    viewport()->update();
}

int QHexScrollArea::stringWidth(const QString& str) const
{
    QFontMetrics fm = fontMetrics();
    return fm.width(str);
}

bool QHexScrollArea::viewportEvent(QEvent *e)
{
    QTimerEvent* timerEvent = dynamic_cast<QTimerEvent*>(e);
    if (timerEvent) {}

    QResizeEvent* resizeEvent = dynamic_cast<QResizeEvent*>(e);
    if (resizeEvent) { }

    QPaintEvent* pe = dynamic_cast<QPaintEvent*>(e);
    if (pe) { }

    QWheelEvent* wheelEvent = dynamic_cast<QWheelEvent*>(e);
    if (wheelEvent) {}

    QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(e);
    if (mouseEvent) { }

    return QScrollArea::viewportEvent(e);
}

void QHexScrollArea::scrollContentsBy ( int dx, int dy )
{
    Q_UNUSED(dx)
    Q_UNUSED(dy)

    viewport()->update();
}

QRect QHexScrollArea::byteRect(const QPoint& pos) const
{
    Q_UNUSED(pos)

    QRect rec;
    return rec;
}

void QHexScrollArea::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)

    blinking = !blinking;
    viewport()->update();
}

void QHexScrollArea::setFilename(const QString &filename)
{
    this->filename = filename;
}

qint64 QHexScrollArea::getRowNumberWidth() const
{
    QFontMetrics fm = this->fontMetrics();

    int ssw = fm.width(" ");                                            // width of space symbol
//    int zsw = fm.width("0");                                            // width of zero symbol

    int div = maxDataCount / bytesPerRow;                                 // data size divide to 16. number of maximum rows
//    int mod = bytesCount % bytesPerRow;                                 // data size module to 16. number of bytes at last row

//    if (mod > 0) mod += 1;

    int rowNumberW = 2 * ssw + fm.width(QString::number(div));  // width of row number column

    return rowNumberW;
}

qint64 QHexScrollArea::getByteNumberWidth() const
{
    QFontMetrics fm = this->fontMetrics();

    int ssw = fm.width(" ");                                            // width of space symbol
    int zsw = fm.width("0");                                            // width of zero symbol

    return ssw * 2 + zsw * 8;
}

qint64 QHexScrollArea::getDataPanelWidth() const
{
    QFontMetrics fm = this->fontMetrics();
    return fm.width(" 00 01 02 03  04 05 06 07   08 09 0A 0B  0C 0D 0E 0F");
}
