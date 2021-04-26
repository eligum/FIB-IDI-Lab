#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    connect(this, SIGNAL(returnPressed()), this, SLOT(tractaReturn()));
    // Inicialitzacio d'atributs si cal
}

// Implementacio slots
void MyLineEdit::tractaReturn()
{
    emit returnPressed(text());
}
