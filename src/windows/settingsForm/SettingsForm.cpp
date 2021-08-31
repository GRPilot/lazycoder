#include "common.h"
#include "settings.h"

#include "settingsForm.h"
#include "ui_settingsForm.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsForm) {

    ui->setupUi(this);

    connect(ui->langButton, &QPushButton::clicked, this, &SettingsForm::onLangButtonClicked);

/*
    auto app{ Utils::getSettings("app") };
    if(nullptr == app) {
        throw int(-1);
    }
*/
}

SettingsForm::~SettingsForm() {
    delete ui;
}

// TODO:
// 1. Update ui of this form and main window form.
// 2. Change icon based on language (QLocale()).
void SettingsForm::onLangButtonClicked() {
    QLocale ruLocale{ QLocale::Russian, QLocale::Russia };
    QLocale enLocale{ QLocale::English, QLocale::UnitedStates };

    if (QLocale() == ruLocale) {
        QLocale::setDefault(enLocale);
    } else {
        QLocale::setDefault(ruLocale);
    }

    QString translatorFilename = QString{ "lazycoder_%1.qm" }.arg(QLocale().name());
    QTranslator translator;
    if (translator.load(translatorFilename)) {
        QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this); // FIXME: Retranslates only settings form ui.
        this->update(); // QUESTIONABLE.
    }
}
