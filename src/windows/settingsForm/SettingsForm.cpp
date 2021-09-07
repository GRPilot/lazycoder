#include "common.h"
#include "settings.h"

#include "settingsForm.h"
#include "ui_settingsForm.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget{ parent }
    , ui{ new Ui::SettingsForm }
    , mTranslator{} {
    ui->setupUi(this);

    connect(ui->langButton, &QPushButton::clicked, this, &SettingsForm::onLangButtonClicked);

    // auto app{ Utils::getSettings("app") };
    // if(nullptr == app) {
    //     throw int(-1);
    // }
}

SettingsForm::~SettingsForm() {
    delete ui;
}

// TODO:
// 1. Fix language being resetted when clicked on settings button again.
// 2. Change icon based on language (QLocale() or mTranslator that installed).
//  Иконка изменяется только после повторного нажатия на кнопку настроек.
//  Да и сам язык сбрасывается при повторном нажатии на эту кнопку.
//  Необходимо базовый язык доставать из Settings при старте программы
//   и, видимо, делать QLocale::setDefault(settings->locale()) (спорно).
void SettingsForm::onLangButtonClicked() {
    // Removes previous translator.
    qApp->removeTranslator(&mTranslator);

    // Locale variables.
    QLocale ruLocale{ QLocale::Russian, QLocale::CyrillicScript, QLocale::Russia };
    QLocale enLocale{ QLocale::English, QLocale::LatinScript, QLocale::UnitedStates };

    // Changes the default app locale depending on the current locale.
    if(QLocale() == ruLocale) {
        QLocale::setDefault(enLocale);
    } else {
        QLocale::setDefault(ruLocale);
    }

    // Installs new translator to the app.
    QString translatorFilename = QString{ "lazycoder_%1.qm" }.arg(QLocale().name());
    if(mTranslator.load(translatorFilename)) {
        qApp->installTranslator(&mTranslator);
    }
}

void SettingsForm::changeEvent(QEvent *event) {
    if(event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    } else {
        QWidget::changeEvent(event);  // Questionable.
    }
}
