#ifndef DOCKMAINWINDOW_H
#define DOCKMAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QDockWidget>
#include <QtGui/QApplication>
#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtGui/QTabWidget>
#include <QtGui/QAction>
#include <QtGui/QListWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QTextFrame>
#include <QtGui/QStatusBar>
#include <QtGui/QFileDialog>
#include <QtGui/QPrintDialog>
#include <QtGui/QPrinter>
#include <QtGui/QMessageBox>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDate>

#include "qhexscrollarea.h"

class DockMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DockMainWindow(QWidget *parent = 0);

signals:

public slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void quit();
    void print();
    void undo();
    void about();
    void insertCustomer(const QString &customer);
    void addParagraph(const QString &paragraph);

    int fillBufferHandler(QByteArray& buffer, qint64 min, qint64 max);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();

    QTabWidget* mTabWidget;

    QListWidget *customerList;
    QListWidget *paragraphsList;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveAsFileAction;
    QAction *printAction;
    QAction *quitAction;
    QAction *undoAction;
    QAction *aboutAction;
};

#endif // DOCKMAINWINDOW_H
