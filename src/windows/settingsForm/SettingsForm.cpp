#include "common.h"
#include "settings.h"

#include "settingsForm.h"
#include "ui_settingsForm.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsForm) 
{
    ui->setupUi(this);

    auto app{ Utils::getSettings("app") };
    if(nullptr == app) {
        throw int(-1);
    }
    app->setValue("theme", "white");
    app->setValue("lang", "english");
    app->setValue("default_dir", "some_directory");
    app->setValue("repos", QStringList({"repo1", "repo2", "repo3"}));
    app->setValue("autosync", true);

    auto theme{ app->value("theme") };
    auto lang{ app->value("lang") };
    auto defaultDir{ app->value("default_dir") };
    auto reposList{ app->value("repos") };
    auto isAutoSync{ app->value("autosync") };

    qDebug() << theme.typeName() << " "
             << lang.typeName() << " "
             << defaultDir.typeName() << " "
             << reposList.typeName() << " "
             << isAutoSync.typeName();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
