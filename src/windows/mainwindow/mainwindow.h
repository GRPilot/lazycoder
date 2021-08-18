#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onCloseButtonClicked();
    void onMaximizeButtonClicked();
    void onMinimizeButtonClicked();
    void onMenuToggled(bool checked);

private:
    Ui::MainWindow *ui;

    // Current cursor position.
    QPointF mousePoint;
};
#endif // MAINWINDOW_H
