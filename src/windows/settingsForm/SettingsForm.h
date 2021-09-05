#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QTranslator>

namespace Ui { class SettingsForm; }

class SettingsForm : public QWidget {
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

private slots:
    void onLangButtonClicked();

protected slots:
    void changeEvent(QEvent *event) override;

private:
    Ui::SettingsForm *ui;
    QTranslator mTranslator;
};

#endif  // SETTINGSFORM_H
