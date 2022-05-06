#include "mainwindow.h"
#include "ui_mainwindow.h"

bool isreadonly = false; //记录当前只读状态
QFile *fp;
bool isFileOpen = false;
bool isTextChanged = false;
bool havePointFile = false;
QString filename;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(ui->actionexit,SIGNAL(on_actionexit_triggered())
}

MainWindow::~MainWindow()
{
    delete ui;
}

//关于
void MainWindow::on_actionabout_triggered()
{
    QMessageBox::information(this, tr("关于"), tr("简易文本编辑器\nBy 通晓宇宙"));
}

//关闭
void MainWindow::on_actionexit_triggered()
{
    if (isFileOpen)
    {
        if (isTextChanged)
        {
            ui->statusbar->showMessage("当前文件未保存.");
            return;
        }
        isFileOpen = false;
        ui->statusbar->showMessage("关闭文件：" + filename);
    }
    ui->plainTextEdit->setPlainText("");
}

//设置只读模式
void MainWindow::on_actionreadonly_triggered()
{
    ui->plainTextEdit->setReadOnly(isreadonly = !isreadonly);
    ui->actionreadonly->setText(isreadonly ? "√只读" : "只读");
}

//打开文件
void MainWindow::on_actionopen_file_triggered()
{
    //如果当前编辑的文件未关闭,强制处理当前文件
    if (isFileOpen)
    {
        ui->statusbar->showMessage("当前文件未关闭,请先关闭.");
        return;
    }

    //创建文件打开窗口，打开文件
    QFileDialog *fileDialog = new QFileDialog(this);
    filename = "";
    if (!(filename = fileDialog->getOpenFileName()).isEmpty())
    {
        fp = new QFile(filename);
        if (!fp->open(QIODevice::ReadOnly | QIODevice::Text)) //打开文件
        {
            QMessageBox::information(this, tr("错误"), tr("以读取方式打开文件出错"));
        }
        isFileOpen = true;
        ui->plainTextEdit->setPlainText(fp->readAll()); //读出文件内容显示在编辑器上
        fp->close();
        delete fp;
        ui->statusbar->showMessage("打开文件：" + filename);
    }
}

//新建文件
void MainWindow::on_actionnew_file_triggered()
{
    //如果当前编辑的文件未关闭,强制处理当前文件
    if (isFileOpen)
    {
        ui->statusbar->showMessage("当前文件未关闭,请先关闭.");
        return;
    }

    //创建文件打开窗口，新建文件
    QFileDialog *fileDialog = new QFileDialog(this);
    filename = "";
    if (!(filename = fileDialog->getSaveFileName()).isEmpty())
    {
        fp = new QFile(filename);
        if (!fp->open(QIODevice::WriteOnly | QIODevice::Text)) //打开文件
        {
            QMessageBox::information(this, tr("错误"), tr("以写入方式打开文件出错"));
        }
        isFileOpen = true;
        ui->plainTextEdit->setPlainText("");
        fp->close();
        delete fp;
        ui->statusbar->showMessage("新建文件：" + filename);
    }
}

//保存文件
void MainWindow::on_actionsave_triggered()
{
    if (isFileOpen)
    {
        fp = new QFile(filename);
        if (!fp->open(QIODevice::WriteOnly | QIODevice::Text)) //打开文件
        {
            QMessageBox::information(this, tr("错误"), tr("以写入方式打开文件出错"));
        }
        QString text = ui->plainTextEdit->toPlainText();
        QByteArray strBytes = text.toUtf8(); //转换为字节数组
        fp->write(strBytes, strBytes.length());
    }
    //当前没有文件打开,用户点击保存
    else
    {
        //创建文件打开窗口，保存文件
        QFileDialog *fileDialog = new QFileDialog(this);
        filename = "";
        if (!(filename = fileDialog->getSaveFileName()).isEmpty())
        {
            fp = new QFile(filename);
            if (!fp->open(QIODevice::WriteOnly | QIODevice::Text)) //打开文件
            {
                QMessageBox::information(this, tr("错误"), tr("以写入方式打开文件出错"));
            }
            isFileOpen = true;
        }
    }
    //写入文件
    QString text = ui->plainTextEdit->toPlainText();
    QByteArray strBytes = text.toUtf8(); //转换为字节数组
    fp->write(strBytes, strBytes.length());
    //改变的文本已保存
    isTextChanged = false;
    fp->close();
    ui->statusbar->showMessage("保存文件：" + filename);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    isTextChanged = true;
}

void MainWindow::on_actionsaveas_triggered()
{
    //创建文件打开窗口，保存文件
    QFileDialog *fileDialog = new QFileDialog(this);
    filename = "";
    if (!(filename = fileDialog->getSaveFileName()).isEmpty())
    {
        fp = new QFile(filename);
        if (!fp->open(QIODevice::WriteOnly | QIODevice::Text)) //打开文件
        {
            QMessageBox::information(this, tr("错误"), tr("以写入方式打开文件出错"));
        }
        isFileOpen = true;
    }
    //写入文件
    QString text = ui->plainTextEdit->toPlainText();
    QByteArray strBytes = text.toUtf8(); //转换为字节数组
    fp->write(strBytes, strBytes.length());
    //改变的文本已保存
    isTextChanged = false;
    fp->close();
    ui->statusbar->showMessage("保存文件：" + filename);
}

void MainWindow::on_actionselectall_triggered()
{
    ui->plainTextEdit->selectAll();
}

void MainWindow::on_actioncut_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actioncopy_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_actionundo_triggered()
{
    ui->plainTextEdit->undo();
}

void MainWindow::on_actionredo_triggered()
{
    ui->plainTextEdit->redo();
}

void MainWindow::on_actionsizeadd_triggered()
{
    QFont qf = ui->plainTextEdit->font();
    qf.setPointSize(qf.pointSize() + 1);
    ui->plainTextEdit->setFont(qf);
}

void MainWindow::on_actionsizesub_triggered()
{
    QFont qf = ui->plainTextEdit->font();
    qf.setPointSize(qf.pointSize() - 1);
    ui->plainTextEdit->setFont(qf);
}
