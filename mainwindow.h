//
// Created by LERA on 2/11/2026.
//

#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QWidget>
#include "playfair.h"
#include "vigener.h"

class Playfair;
class Vigener;

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
    explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
    private:
    void createMenus();
    void onPlayfairToggled(bool checked);
    void onCalculateClicked();
    void onOpenTriggered();
    void onSaveTriggered();
    void onClearFieldsTriggered();

    QTextEdit *plainTextEdit;
    QLineEdit *keyLineEdit;
    QLineEdit *key2LineEdit;
    QLineEdit *key3LineEdit;
    QLineEdit *key4LineEdit;
    QLabel *key1Label;
    QLabel *key2Label;
    QLabel *key3Label;
    QLabel *key4Label;
    QTextEdit *cipherTextEdit;
    QRadioButton *playfairButton;
    QRadioButton *vigenerButton;
    QRadioButton *encryptionButton;
    QRadioButton *decryptionButton;
    QPushButton *calculateButton;
    QAction *openAction;
    QAction *saveAction;
    QAction *clearFieldsAction;
    Playfair *playfair_;
    Vigener *vigenere_;
    QWidget *keyWidget;
};