#include "startscreen.h"
#include "ui_startscreen.h"

#include "email/protocol_adapters/pop3/pop3adapter.h"

#include <iostream>
StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);


    Pop3Adapter *pop3 = new Pop3Adapter();
    try
    {
        pop3->login("pop.mail.yahoo.com","995","","");
    }
    catch (QString exc)
    {
        std::cout << exc.toStdString() << std::endl;
    }
}

StartScreen::~StartScreen()
{
    delete ui;
}
