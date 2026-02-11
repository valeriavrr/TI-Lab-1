//
// Created by LERA on 2/11/2026.
//

#ifndef TI_LAB_1_MAINWINDOW_H
#define TI_LAB_1_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QTextEdit;
class QRadioButton;
class QPushButton;
class QAction;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
    explicit MainWindow(QWidget *parent = nullptr);

    private:
    void createMenus();
    QTextEdit *plainTextEdit;
    QLineEdit *keyLineEdit;
    QTextEdit *cipherTextEdit;
    QRadioButton *playfairButton;
    QRadioButton *vigenerButton;
    QRadioButton *encryptionButton;
    QRadioButton *decryptionButton;
    QPushButton *calculateButton;
    QAction *openAction;
    QAction *saveAction;
    QAction *clearFieldsAction;
};

#endif //TI_LAB_1_MAINWINDOW_H