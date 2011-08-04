#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup menu
    menu = new QMenu(this);
    grp = new QActionGroup(this);
    for (int i = 0; i < 4; i++) {
        QAction *a = new QAction(QString("%1/4").arg(i + 1), this);
        a->setCheckable(true);
        a->setActionGroup(grp);
        menu->addAction(a);
    }
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menutriggerAction(QAction*)));
    grp->actions()[0]->setChecked(true);

    // Setup buttons
    EventListener *filter = new EventListener(this);
    ui->downButton->setMouseTracking(true);
    ui->downButton->installEventFilter(filter);
    ui->upButton->setMouseTracking(true);
    ui->upButton->installEventFilter(filter);
    ui->menuButton->setMouseTracking(true);
    ui->menuButton->installEventFilter(filter);
    connect(filter, SIGNAL(buttonClicked(QString)), this, SLOT(clickAction(QString)));
    connect(filter, SIGNAL(buttonHover(QString)), this, SLOT(hoverAction(QString)));
    connect(filter, SIGNAL(buttonLeave(QString)), this, SLOT(leaveAction(QString)));

    this->installEventFilter(filter);
    connect(filter, SIGNAL(rightClicked(int, int)), this, SLOT(formclickAction(int, int)));

    currentBpm = 120;

    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setStyleSheet("* { background-color:rgb(170,170,180);}");
    ui->lcdNumber->display(currentBpm);

    //Volume control
    vol = new VolumeWindow();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setBpm() {
    bool ok;
    currentBpm = QInputDialog::getInteger(this, tr("Set BPM"), tr("Beats Per Minute:"), currentBpm, 0, 300, 1, &ok);

    if (ok) {
        ui->lcdNumber->display(currentBpm);
        JackOutput::getInstance()->setBPM(currentBpm);
    }
}


void MainWindow::clickAction(QString b) {
    if (b == "upButton") currentBpm += 10;
    if (b == "downButton") currentBpm -= 10;
    if (b == "menuButton") {
        menu->popup(mapToParent(ui->menuButton->geometry().center()), new QAction(this));
        return;
    }

    ui->lcdNumber->display(currentBpm);
    JackOutput::getInstance()->setBPM(currentBpm);
}


void MainWindow::hoverAction(QString b) {
    if (b == "upButton") ui->upButton->setPixmap(QPixmap(":/pics/button3.png"));
    if (b == "downButton") ui->downButton->setPixmap(QPixmap(":/pics/button1.png"));
    if (b == "menuButton") ui->menuButton->setPixmap(QPixmap(":/pics/button2.png"));
}


void MainWindow::leaveAction(QString b) {
    if (b == "upButton") ui->upButton->setPixmap(NULL);
    if (b == "downButton") ui->downButton->setPixmap(NULL);
    if (b == "menuButton") ui->menuButton->setPixmap(NULL);
}


void MainWindow::menutriggerAction(QAction *act) {
    JackOutput::getInstance()->setMeasure(act->text().section('/',0,0).toInt());
}


void MainWindow::formclickAction(int x, int y) {
    int locX = this->geometry().x() + x;
    int locY = this->geometry().y() + y;
    vol->setGeometry(locX, locY, vol->geometry().width(), vol->geometry().height());
    vol->show();
}
