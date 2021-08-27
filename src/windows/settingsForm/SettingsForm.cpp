#include "settingsForm.h"

#include "../utils/settings/settings.h"
#include "ui_settingsForm.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsForm) 
{
    ui->setupUi(this);
    
    using namespace setm;

    Settings().setValue("theme", "white");
    Settings().setValue("lang", "english");
    Settings().setValue("default_dir", "some_directory");
    Settings().setValue("repos", QStringList({"repo1", "repo2", "repo3"}));
    Settings().setValue("autosync", true);

    auto theme{Settings().value("theme")};
    auto lang{Settings().value("lang")};
    auto defaultDir{Settings().value("default_dir")};
    auto reposList{Settings().value("repos")};
    auto isAutoSync{Settings().value("autosync")};

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
