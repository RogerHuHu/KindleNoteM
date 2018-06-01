#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include <list>
#include <string>

using std::list;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    settings = new QSettings("./Setting.ini", QSettings::IniFormat);
    CreateMenuBar();
    CreateBookListWidget();
    CreateNoteTextEdit();
}

MainWindow::~MainWindow() {
    delete bookListWidget;
    delete noteTextEdit;
    delete bookList;
    delete settings;
    delete ui;
}

void MainWindow::CreateMenuBar() {
    QMenu *menuFile = ui->menuBar->addMenu("文件");
    QAction *actionOpen = menuFile->addAction(QString("打开文件"));
    actionOpen->setShortcut(QKeySequence("Ctrl+O"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(FileOpenActionSlot()));
}

void MainWindow::CreateBookListWidget() {
    bookListWidget = new QListWidget(ui->centralWidget);
    bookListWidget->setGeometry(1, 1, 200, 495);
}

void MainWindow::CreateNoteTextEdit() {
    noteTextEdit = new QTextEdit(ui->centralWidget);
    noteTextEdit->setGeometry(202, 1, 600, 495);
}

void MainWindow::FileOpenActionSlot() {
    SelectFile();
    ParseKindleClippings(clippingsFileName);
    DispalyBookName();
}

void MainWindow::BookSelectActionSlot(QListWidgetItem *item) {
    DispalyBookNotes(item->text());
}

void MainWindow::SelectFile() {
    clippingsFileName = QFileDialog::getOpenFileName(this,
            tr("Open File"),
            settings->value("LastFilePath").toString(),
            tr("Text(*.txt)"),
            0);
    settings->setValue("LastFilePath", clippingsFileName);
}

void MainWindow::DispalyBookName() {
    std::list<std::string> bookNames;
    bookList->GetBookNames(bookNames);

    std::list<std::string>::iterator iter = bookNames.begin();
    for(; iter != bookNames.end(); ++iter) {
        bookListWidget->addItem(QString::fromStdString(*iter));
    }
    connect(bookListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(BookSelectActionSlot(QListWidgetItem*)));
    bookNames.clear();
}

void MainWindow::DispalyBookNotes(const QString &bookName) {
    noteTextEdit->clear();
    std::list<std::string> bookNotes;
    bookList->GetBookNotes(bookName.toStdString(), bookNotes);
    int count = 0;
    std::list<std::string>::iterator iter = bookNotes.begin();
    for(; iter != bookNotes.end(); ++iter) {
        noteTextEdit->append(QString::number(++count, 10) + ": " + QString::fromStdString(*iter));
        noteTextEdit->append("");
    }
    bookNotes.clear();
}

void MainWindow::ParseKindleClippings(const QString &path) {
    bookList = new KindleBookList(path.toStdString());
    bookList->LoadClippings();
}
