#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctest.h"
#include "cdelegate.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_data();
}

MainWindow::~MainWindow()
{
    delete table_model;
    delete ui;
}

void MainWindow::init_data()
{
    // модель данных
    table_model = new CTableModel(this);
    ui->tableView->setModel(table_model);
    ui->tableView->horizontalHeader()->show();
    ui->tableView->verticalHeader()->show();

    // view
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    // controller - custom делегат для редактирования данных
    CDelegate* delegate = new CDelegate(ui->tableView);
    ui->tableView->setItemDelegate(delegate);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 0);
}


void MainWindow::on_pb_random_clicked()
{
    table_model->random_fill();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(table_model->get_obj_info(index.column()));
}

void MainWindow::on_clearCellData()
{
    table_model->clearData(ui->tableView->selectionModel()->currentIndex());
    on_tableView_clicked(ui->tableView->selectionModel()->currentIndex());    // TODO привязать к к.. событию обновления данных
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu = new QMenu( this);
    QAction *clearCellData= new QAction("clear", table_model);
    connect(clearCellData, SIGNAL(triggered()), this, SLOT(on_clearCellData()));     // Call Handler dialog editing

    menu->addAction(clearCellData);

    // тут нужно брать именно позицию клика, т.к. некоторые ячейки могут быть неактивные и через selectionModel не выбираются
    if(qvariant_cast<CUserData>(ui->tableView->indexAt(pos).data(Qt::EditRole)).user_type() == TCell::TCELL_NONE){
        clearCellData->setDisabled(true);
    }
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}
