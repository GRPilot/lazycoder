#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    
    // Set UI up.
    ui->setupUi(this);

    // Specify window properties (get rid of title bar and default buttons).
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

    // Change text in footer (status bar).
    ui->appVersion->setText("Version " + AppInfo::Version::qStr() +
                            " | Copyright: seigtm x gollan | "
                            "From 2021 with love 🥰");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_closeButton_clicked() {
    close();
}

void MainWindow::on_maximizeButton_clicked() {
    isMaximized() ? showNormal() : showMaximized();
}

void MainWindow::on_minimizeButton_clicked() {
    showMinimized();
}
