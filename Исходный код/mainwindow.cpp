//
// Created by LERA on 2/11/2026.
//

#include "mainwindow.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), playfair_(nullptr), vigenere_(nullptr)
{
    plainTextEdit = new QTextEdit(this);
    cipherTextEdit = new QTextEdit(this);
    cipherTextEdit->setReadOnly(true);

    keyLineEdit = new QLineEdit(this);
    key2LineEdit = new QLineEdit(this);
    key3LineEdit = new QLineEdit(this);
    key4LineEdit = new QLineEdit(this);

    playfairButton = new QRadioButton("Шифр Плейфейра (4 таблицы)", this);
    vigenerButton = new QRadioButton("Шифр Виженера (прямой ключ)", this);

    encryptionButton = new QRadioButton("Шифрование", this);
    decryptionButton = new QRadioButton("Дешифрование", this);

    auto *cipherGroup = new QGroupBox( this);
    auto *cipherLayout = new QVBoxLayout;
    cipherLayout->addWidget(playfairButton);
    playfairButton->setChecked(true);
    cipherLayout->addWidget(vigenerButton);
    cipherGroup->setLayout(cipherLayout);

    auto *modeGroup = new QGroupBox( this);
    auto *modeLayout = new QVBoxLayout;
    modeLayout->addWidget(encryptionButton);
    encryptionButton->setChecked(true);
    modeLayout->addWidget(decryptionButton);
    modeGroup->setLayout(modeLayout);

    auto *radioLayout = new QHBoxLayout;
    radioLayout->addWidget(cipherGroup);
    radioLayout->addWidget(modeGroup);

    calculateButton = new QPushButton("Рассчитать", this);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);

    auto *formLayout = new QFormLayout;
    formLayout->addRow("Исходный текст:", plainTextEdit);
    key1Label = new QLabel("Ключ 1:", this);
    key2Label = new QLabel("Ключевое слово 2:", this);
    key3Label = new QLabel("Ключевое слово 3:", this);
    key4Label = new QLabel("Ключевое слово 4:", this);
    formLayout->addRow(key1Label, keyLineEdit);
    formLayout->addRow(key2Label, key2LineEdit);
    formLayout->addRow(key3Label, key3LineEdit);
    formLayout->addRow(key4Label, key4LineEdit);
    formLayout->addRow("Результат:", cipherTextEdit);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(radioLayout);
    mainLayout->addWidget(calculateButton, 0, Qt::AlignCenter);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    createMenus();
    connect(playfairButton, &QRadioButton::toggled, this, &MainWindow::onPlayfairToggled);

    setWindowTitle("TI Lab 1");
    resize(500, 300);
}

void MainWindow::createMenus()
{
    openAction = new QAction("Считать", this);
    saveAction = new QAction("Сохранить", this);
    clearFieldsAction = new QAction("Очистить поля", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenTriggered);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveTriggered);
    connect(clearFieldsAction, &QAction::triggered, this, &MainWindow::onClearFieldsTriggered);
    auto menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu *fileMenu = menuBar->addMenu("Файл");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    menuBar->addAction(clearFieldsAction);
}

MainWindow::~MainWindow() {
    delete playfair_;
    delete vigenere_;
}

void MainWindow::onPlayfairToggled(bool checked)
{
    key2Label->setVisible(checked);
    key2LineEdit->setVisible(checked);
    key3Label->setVisible(checked);
    key3LineEdit->setVisible(checked);
    key4Label->setVisible(checked);
    key4LineEdit->setVisible(checked);
}

void MainWindow::onCalculateClicked()
{
    QString plain = plainTextEdit->toPlainText();
    QString result;
    if (playfairButton->isChecked()) {
        QString k1 = keyLineEdit->text();
        QString k2 = key2LineEdit->text();
        QString k3 = key3LineEdit->text();
        QString k4 = key4LineEdit->text();
        if (k1.isEmpty() || k2.isEmpty() || k3.isEmpty() || k4.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Для шифра Плейфейра требуются все 4 ключа.");
            return;
        }
        delete playfair_;
        playfair_ = new Playfair(k1, k2, k3, k4);
        if (encryptionButton->isChecked())
            result = playfair_->encrypt(plain);
        else
            result = playfair_->decrypt(plain);
    } else if (vigenerButton->isChecked()) {
        QString key = keyLineEdit->text();
        if (key.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Требуется ключ для шифра Виженера.");
            return;
        }
        Vigener cipher(key);
        if (encryptionButton->isChecked())
            result = cipher.encrypt(plain);
        else
            result = cipher.decrypt(plain);
    }
    cipherTextEdit->setPlainText(result);
}

void MainWindow::onOpenTriggered()
{
    QString fileName = QFileDialog::getOpenFileName( this, "Открыть файл с исходным текстом", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll();
    file.close();
    plainTextEdit->setPlainText(content);
}

void MainWindow::onSaveTriggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить результат", "result.txt", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) return;
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName += ".txt"; }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл для записи.");
        return;
    }
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << cipherTextEdit->toPlainText();
    file.close();
    QMessageBox::information(this, "Успешно", "Результат успешно сохранен.");
}

void MainWindow::onClearFieldsTriggered()
{
    plainTextEdit->clear();
    keyLineEdit->clear();
    key2LineEdit->clear();
    key3LineEdit->clear();
    key4LineEdit->clear();
    cipherTextEdit->clear();
}