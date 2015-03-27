#include "dockmainwindow.h"

DockMainWindow::DockMainWindow(QWidget *parent) : QMainWindow(parent)
{
    mTabWidget = new QTabWidget();
    setCentralWidget(mTabWidget);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setUnifiedTitleAndToolBarOnMac(true);

    setWindowTitle(tr("Dock Widgets"));
    resize(800, 600);
    setWindowState(Qt::WindowMaximized);
}

void DockMainWindow::openFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("All Files (*.*)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    for (int i=0; i < fileNames.size(); i++)
    {
        QFileInfo fileInfo(fileNames.at(i));

        QHexScrollArea* w = new QHexScrollArea();

        connect(w, SIGNAL(fillBuffer(QByteArray&, qint64, qint64)), this, SLOT(fillBufferHandler(QByteArray&, qint64, qint64)));

        QFile file(fileNames.at(i));
        file.open(QFile::ReadOnly);
        w->setMaxDataCount(file.size());
        file.close();

        w->setFilename(fileNames.at(i));
        mTabWidget->addTab(w, fileInfo.fileName());
    }
}

int DockMainWindow::fillBufferHandler(QByteArray& buffer, qint64 min, qint64 max)
{
    QHexScrollArea* hsa = qobject_cast<QHexScrollArea*>(sender());
    if (hsa == NULL) return 0;

    if (min > max)
        return 0;

    QFile file(hsa->filename);
    file.open(QFile::ReadOnly);
    file.seek(min);
    char* d = new char[max - min];
    file.read(d, (max - min));
    buffer = QByteArray(d, max-min);
    delete [] d;

    return 0;
}

void DockMainWindow::saveFile()
{
    //QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a file name"), ".", tr("HTML (*.html *.htm)"));
    //QString filename = QFileDialog::getOpenFileName(this, tr("Caption"), ".", "filter");
    //if (fileName.isEmpty())
    //    return;
    //QFile file(fileName);
    //if (!file.open(QFile::WriteOnly | QFile::Text)) {
    //    QMessageBox::warning(this, tr("Dock Widgets"),
    //                         tr("Cannot write file %1:\n%2.")
    //                         .arg(fileName)
    //                         .arg(file.errorString()));
    //    return;
    //}

    //QTextStream out(&file);
    //QApplication::setOverrideCursor(Qt::WaitCursor);
    //out << textEdit->toHtml();
    //QApplication::restoreOverrideCursor();

    //statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}

void DockMainWindow::saveAsFile()
{}

void DockMainWindow::print()
{
#ifndef QT_NO_PRINTDIALOG
    //QTextDocument *document = textEdit->document();
    //QPrinter printer;

    //QPrintDialog *dlg = new QPrintDialog(&printer, this);
    //if (dlg->exec() != QDialog::Accepted)
    //    return;

    //document->print(&printer);

    //statusBar()->showMessage(tr("Ready"), 2000);
#endif
}

void DockMainWindow::quit()
{}

void DockMainWindow::undo()
{}

void DockMainWindow::about()
{}

void DockMainWindow::insertCustomer(const QString &customer)
{}

void DockMainWindow::addParagraph(const QString &paragraph)
{}

void DockMainWindow::createActions()
{
    openFileAction = new QAction(QIcon(":/images/resources/images/open_file.png"), tr("&Open file"), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Create a new form letter"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveFileAction = new QAction(QIcon(":/images/save.png"), tr("&Save..."), this);
    saveFileAction->setShortcuts(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save the current form letter"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsFileAction = new QAction(QIcon(":/images/save.png"), tr("&Save as..."), this);
    saveAsFileAction->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsFileAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    printAction = new QAction(QIcon(":/images/print.png"), tr("&Print..."), this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(tr("Print the current form letter"));
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcuts(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit the application"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    undoAction = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setStatusTip(tr("Undo the last editing action"));
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutAction = new QAction(tr("About &Qt"), this);
    aboutAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void DockMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutAction);
}

void DockMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openFileAction);
    fileToolBar->addAction(saveFileAction);
    fileToolBar->addAction(saveAsFileAction);
    fileToolBar->addAction(printAction);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAction);
}

void DockMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void DockMainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);
    customerList->addItems(QStringList()
                           << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
                           << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
                           << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
                           << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
                           << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
                           << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Paragraphs"), this);
    paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList()
                             << "Thank you for your payment which we have received today."
                             << "Your order has been dispatched and should be with you "
                             "within 28 days."
                             << "We have dispatched those items that were in stock. The "
                             "rest of your order will be dispatched once all the "
                             "remaining items have arrived at our warehouse. No "
                             "additional shipping charges will be made."
                             << "You made a small overpayment (less than $5) which we "
                             "will keep on account for you, or return at your request."
                             << "You made a small underpayment (less than $1), but we have "
                             "sent your order anyway. We'll add this underpayment to "
                             "your next bill."
                             << "Unfortunately you did not send enough money. Please remit "
                             "an additional $. Your order will be dispatched as soon as "
                             "the complete amount has been received."
                             << "You made an overpayment (more than $5). Do you wish to "
                             "buy more items, or should we return the excess to you?");
    dock->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(customerList, SIGNAL(currentTextChanged(QString)), this, SLOT(insertCustomer(QString)));
    connect(paragraphsList, SIGNAL(currentTextChanged(QString)), this, SLOT(addParagraph(QString)));

    dock = new QDockWidget(tr("Customers1"), this);
    dock->setWidget(new QListWidget );
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

