#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionabout_triggered();

    void on_actionexit_triggered();

    void on_actionreadonly_triggered();

    void on_actionopen_file_triggered();

    void on_actionnew_file_triggered();

    void on_actionsave_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionsaveas_triggered();

    void on_actionselectall_triggered();

    void on_actioncut_triggered();

    void on_actioncopy_triggered();

    void on_actionpaste_triggered();

    // void on_actiondelete_triggered();

    void on_actionundo_triggered();

    void on_actionredo_triggered();

    void on_actionsizeadd_triggered();

    void on_actionsizesub_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
