#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include<mainpage/mainpage.h>
#include<models/cookie.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,loginWidget(nullptr)
{

    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout*mainLayout=new QVBoxLayout(centralWidget);

    loginButton=new QPushButton("Login",this);
    loginButton->setFixedSize(150,40);
    loginButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #C20C0C;"
        "    color: white;"
        "    border-radius: 20px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #D81E06;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #A00;"
        "}"
    );
    // QString cookie=RecommendAPI::getLastLoginCookie();
    QString musicU = Cookie::getMusicU();
    qDebug() << "length!!!" << musicU;
    if (!musicU.isEmpty()) {
        loginButton->hide();
        MainPage* mainPage = new MainPage(this);
        setCentralWidget(mainPage);
    }else{
        mainLayout->addWidget(loginButton,0,Qt::AlignCenter);
        setCentralWidget(centralWidget);
    }



    connect(loginButton,&QPushButton::clicked,this,&MainWindow::onLoginButtonClicked);
    setFixedSize(400,300);
    setWindowTitle("AAAAA");
}

void MainWindow::onLoginButtonClicked()
{

    loginButton->hide();
    loginWidget=new LoginWidget(this);
    setCentralWidget(loginWidget);
    connect(loginWidget, &LoginWidget::backRequested, this, [this]() {
        delete loginWidget;
        loginWidget = nullptr;
        loginButton->show();
        setFixedSize(400, 300);
    });
    setFixedSize(300,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}
