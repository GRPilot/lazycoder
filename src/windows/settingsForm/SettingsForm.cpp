#include "settingsForm.h"

#include "ui_settingsForm.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsForm) {
    ui->setupUi(this);
}

SettingsForm::~SettingsForm() {
    delete ui;
}
