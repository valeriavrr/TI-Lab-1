//
// Created by LERA on 2/11/2026.
//

#include "mainwindow.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent) {
    plainTextEdit = new QTextEdit(this);
    keyLineEdit = new QLineEdit(this);
    (cipherTextEdit = new QTextEdit(this))->setReadOnly(true);
    (playfairButton = new QRadioButton("Шифр Плейфейра", this))->setChecked(true);
    vigenerButton = new QRadioButton("Шифр Виженера (прямой ключ)", this);
    auto *cipherGroup = new QGroupBox(this);
    auto *cipherLayout = new QVBoxLayout;
    cipherLayout->addWidget(playfairButton);
    cipherLayout->addWidget(vigenerButton);
    cipherGroup->setLayout(cipherLayout);
    encryptionButton = new QRadioButton("Шифрование", this);
    decryptionButton = new QRadioButton("Дешифрование", this);
    encryptionButton->setChecked(true);
    auto *modeGroup = new QGroupBox(this);
    auto *modeLayout = new QVBoxLayout;
    modeLayout->addWidget(encryptionButton);
    modeLayout->addWidget(decryptionButton);
    modeGroup->setLayout(modeLayout);
    auto *radioLayout = new QHBoxLayout;
    radioLayout->addWidget(cipherGroup);
    radioLayout->addWidget(modeGroup);
    calculateButton = new QPushButton("Рассчитать", this);
    auto *formLayout = new QFormLayout;
    formLayout->addRow("Исходный текст:", plainTextEdit);
    formLayout->addRow("Ключ:", keyLineEdit);
    formLayout->addRow("Результат:", cipherTextEdit);
    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(radioLayout);
    mainLayout->addWidget(calculateButton, 0, Qt::AlignCenter);
    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    createMenus();
    setWindowTitle("TI Lab 1");
    resize(400, 300);
}

void MainWindow::createMenus()
{
    openAction = new QAction("Считать", this);
    saveAction = new QAction("Сохранить", this);
    clearFieldsAction = new QAction("Очистить поля", this);

    auto menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu *fileMenu = menuBar->addMenu("Файл");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    menuBar->addAction(clearFieldsAction);
}