#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMenuBar>
#include <QMenu>
#include <QString>
#include <QSettings>
#include <QTextEdit>

#include "KindleNoteParse/KindleBookList.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DispalyBookName();
    void DispalyBookNotes(const QString &bookName);

private slots:
    void FileOpenActionSlot();
    void BookSelectActionSlot(QListWidgetItem *item);

private:
    void CreateMenuBar();
    void CreateBookListWidget();
    void CreateNoteTextEdit();
    void SelectFile();
    void ParseKindleClippings(const QString &path);
    Ui::MainWindow *ui;
    QListWidget *bookListWidget;
    QTextEdit *noteTextEdit;
    KindleBookList *bookList;
    QString clippingsFileName;
    QSettings *settings;
};

#endif // MAINWINDOW_H
