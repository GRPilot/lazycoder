#include "common.h"
#include "settings.h"

#include "settingsForm.h"
#include "ui_settingsForm.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsForm) 
{
    ui->setupUi(this);

/*
    auto app{ Utils::getSettings("app") };
    if(nullptr == app) {
        throw int(-1);
    }
*/
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
