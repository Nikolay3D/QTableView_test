#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ctablemodel.h"
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_data();

private slots:
    void on_pb_random_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_clearCellData();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    CTableModel *table_model = nullptr;
};
#endif // MAINWINDOW_H
