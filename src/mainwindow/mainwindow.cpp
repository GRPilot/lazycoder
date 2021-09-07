#include "common.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "appversion.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{ parent, Qt::Window | Qt::CustomizeWindowHint }, ui(new Ui::MainWindow) {
    // Set UI up.
    ui->setupUi(this);

    // Change text in footer (status bar).
    auto format{ ui->appVersion->text() };
    ui->appVersion->setText(format.arg(AppInfo::Version::qStr()));

    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->maximizeButton, &QPushButton::clicked, this, &MainWindow::onMaximizeButtonClicked);
    connect(ui->minimizeButton, &QPushButton::clicked, this, &MainWindow::onMinimizeButtonClicked);
    connect(ui->menuButton, &QPushButton::toggled, this, &MainWindow::onMenuToggled);
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

void MainWindow::onMenuToggled(bool checked) {
    /// @todo Toggle left bar
}
