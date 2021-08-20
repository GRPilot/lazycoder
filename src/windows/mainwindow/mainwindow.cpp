#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "appversion.h"
#include "common.h"
#include "settingsForm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{ parent, Qt::Window | Qt::CustomizeWindowHint }, ui(new Ui::MainWindow) {

    // Configures the UI of the app.
    ui->setupUi(this);

    // Changes the text in the footer (status bar).
    auto format{ ui->appVersion->text() };
    ui->appVersion->setText(format.arg(AppInfo::Version::qStr()));

    // Connects signals and slots.
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->maximizeButton, &QPushButton::clicked, this, &MainWindow::onMaximizeButtonClicked);
    connect(ui->minimizeButton, &QPushButton::clicked, this, &MainWindow::onMinimizeButtonClicked);
    connect(ui->menuButton, &QPushButton::toggled, this, &MainWindow::onMenuToggled);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCloseButtonClicked() {
    close();
}

void MainWindow::onMaximizeButtonClicked() {
    if (isMaximized()) {
        showNormal();
    } else {
        showMaximized();
    }
}

void MainWindow::onMinimizeButtonClicked() {
    showMinimized();
}

void MainWindow::onMenuToggled(bool checked) {
    /// @todo Toggle left bar.
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Gets the current cursor position.
    mousePoint = event->globalPosition().toPoint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    // Moves the window only if it's not maximized.
    if (isMaximized()) {
        return;
    }

    // If left mouse button clicked.
    if (event->buttons() == Qt::LeftButton) {
        // Moves window.
        move(pos() + event->globalPosition().toPoint() - mousePoint);
        mousePoint = event->globalPosition().toPoint();
    }
}

void MainWindow::setMainWidget(QWidget *widget) {
    // Deletes the previous widget in the layout.
    if (!ui->contentLayout->isEmpty())
        delete ui->contentLayout->takeAt(0);

    // Adds the settings widget to the layout.
    ui->contentLayout->addWidget(widget);
}

void MainWindow::onSettingsButtonClicked() {
    setMainWidget(new SettingsForm);
}
