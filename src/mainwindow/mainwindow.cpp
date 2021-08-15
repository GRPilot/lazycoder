#include "common.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "appversion.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{ parent, Qt::Window | Qt::CustomizeWindowHint }, ui(new Ui::MainWindow) {
    
    // Set UI up.
    ui->setupUi(this);

    // Change text in footer (status bar).
    ui->appVersion->setText("Version " + AppInfo::Version::qStr() +
                            " | Copyright: seigtm x gollan | "
                            "From 2021 with love 🥰");

    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->maximizeButton, &QPushButton::clicked, this, &MainWindow::onMaximizeButtonClicked);
    connect(ui->minimizeButton, &QPushButton::clicked, this, &MainWindow::onMinimizeButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCloseButtonClicked() {
    close();
}

void MainWindow::onMaximizeButtonClicked() {
    if(isMaximized()) {
        showNormal();
    } else {
        showMaximized();
    }
}

void MainWindow::onMinimizeButtonClicked() {
    showMinimized();
}
