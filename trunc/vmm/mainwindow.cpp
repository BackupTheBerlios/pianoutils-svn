#include "mainwindow.h"

MainWindow::MainWindow(AudioOutput *ao, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    output = ao;

    // Setup menu
    menu = new QMenu(this);
    QActionGroup *grp = new QActionGroup(this);
    for (int i = 0; i < 4; i++) {
        QAction *a = new QAction(QString("%1/4").arg(i + 1), this);
        a->setCheckable(true);
        a->setActionGroup(grp);
        a->setData(QVariant(i));
        menu->addAction(a);
    }
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menutriggerAction(QAction*)));
    grp->actions()[0]->setChecked(true);

    menu->addSeparator();
    devices = new QMenu("Output", menu);
    menu->addMenu(devices);
    devicesGrp = new QActionGroup(this);
    connect(devices, SIGNAL(triggered(QAction*)), this, SLOT(devicemenuTriggerAction(QAction*)));

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
    vol = new VolumeWindow(ao);
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
        output->setBPM(currentBpm);
    }
}


void MainWindow::clickAction(QString b) {
    if (b == "upButton") currentBpm += 10;
    if (b == "downButton") currentBpm -= 10;
    if (b == "menuButton") {
        QVector <QString> ret = output->getDevices();
        devices->clear();
        for (int i = 0; i < ret.count(); i++) {
            QAction *a = new QAction(ret[i], this);
            a->setCheckable(true);
            if (ret[i] == currentDevice) a->setChecked(true);
            a->setData(QVariant(i));
            a->setActionGroup(devicesGrp);
            devices->addAction(a);
        }
        menu->popup(mapToParent(ui->menuButton->geometry().center()), new QAction(this));
        return;
    }

    ui->lcdNumber->display(currentBpm);
    output->setBPM(currentBpm);
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
    output->setMeasure(act->data().toInt());
}


void MainWindow::formclickAction(int x, int y) {
    int locX = this->geometry().x() + x;
    int locY = this->geometry().y() + y;
    vol->setGeometry(locX, locY, vol->geometry().width(), vol->geometry().height());
    vol->show();
}


void MainWindow::devicemenuTriggerAction(QAction *act) {
    currentDevice = act->text();
    QString result = output->setOutputDevice(act->data().toInt());
    if (result != "") {
        QMessageBox::critical(this, tr("Error"), result);
    }
}
