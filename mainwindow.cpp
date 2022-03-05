#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutme.h"

QFont mFont;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,"Open a file");

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text))
        {
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();

            ui->textEdit->setPlainText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    //Test for filename
    if(mFilename=="")
    {
        on_actionSave_As_triggered();
        return;
    }
    QFile sFile(mFilename);
    if(sFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file = QFileDialog::getSaveFileName(this,"Open a file");

    if(!file.isEmpty())
    {
        mFilename = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionBold_triggered()
{
    if(mFont.bold())
    {
        ui->textEdit->setFontWeight(QFont::Normal);
        mFont.setBold(false);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Bold);
        mFont.setBold(true);
    }
/*
    //void TextEditor::setEditorFont(const QFont &font)
    //{
    QFont f = QFont(font.family(), configManager->getEditorFontSize());
    QPlainTextEdit::setFont(f);
    configManager->setEditorFontFamily(font.family());
    lineNumberArea->setFont(f);
    //}
*/
}
bool subscript_state=false;
bool superscript_state=false;
void MainWindow::on_actionSubscript_2_triggered()
{
    if(!subscript_state)
    {
        if(mFont.bold()){
            ui->textEdit->insertHtml("<sub><b>~<b></sub>");
        }
        else
        {
            ui->textEdit->insertHtml("<sub>~</sub>");
        }
        subscript_state = true;
    }
    else
    {
        if(mFont.bold()){
            ui->textEdit->insertHtml("<b>~</b>");
        }
        else
        {
            ui->textEdit->insertHtml("~");
        }
        subscript_state = false;
    }
    superscript_state = false;
}

void MainWindow::on_actionSuperScript_triggered()
{
    if(!superscript_state)
    {
        if(mFont.bold())
        {
            ui->textEdit->insertHtml("<sup><b>~</b></sup>");
        } else
        {
            ui->textEdit->insertHtml("<sup>~</sup>");
        }
        superscript_state = true;
    }
    else
    {
        if(mFont.bold())
        {
            ui->textEdit->insertHtml("<b>~</b>");
        } else {
            ui->textEdit->insertHtml("~");
        }
        superscript_state = false;
    }
    subscript_state = false;
}


void MainWindow::on_actionAbout_Me_triggered()
{
    aboutme = new AboutMe(this);
    aboutme->show();
}
