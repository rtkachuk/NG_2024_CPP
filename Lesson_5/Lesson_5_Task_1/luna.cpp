#include "luna.h"
#include "ui_luna.h"

Luna::Luna(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Luna)
{
    ui->setupUi(this);

    QString buttonStyle = "QPushButton { background-color: lightblue; border-style: solid; border-width: 2px; border-radius: 15px; border-color: beige; padding: 6px; } QPushButton:pressed { background-color: #a0d8ef; }";

    m_homepage = "https://google.com";

    m_fileMenu = new QMenu("File", this);
    m_settingsMenu = new QMenu("Settings", this);

    m_quit = new QAction("Quit", this);
    m_quit->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    m_addTab = new QAction("New tab", this);
    m_addTab->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    m_updateHomepage = new QAction("Update Homepage", this);

    m_fileMenu->addAction(m_addTab);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_quit);

    m_settingsMenu->addAction(m_updateHomepage);

    ui->menubar->addMenu(m_fileMenu);
    ui->menubar->addMenu(m_settingsMenu);
    ui->menubar->show();

    ui->b_back->setStyleSheet(buttonStyle);
    ui->b_forward->setStyleSheet(buttonStyle);
    ui->b_go->setStyleSheet(buttonStyle);
    ui->b_reload->setStyleSheet(buttonStyle);

    ui->b_reload->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));

    ui->p_progress->hide();

    ui->t_tabs->clear();
    ui->t_tabs->setTabsClosable(true);

    addTab();

    connect (ui->b_go, &QPushButton::clicked, this, &Luna::openLink);
    connect (m_quit, &QAction::triggered, this, &Luna::close);
    connect (m_addTab, &QAction::triggered, this, &Luna::addTab);
    connect (ui->t_tabs, &QTabWidget::tabCloseRequested, this, &Luna::removeTab);
    connect (ui->t_tabs, &QTabWidget::currentChanged, this, &Luna::tabChanged);
    connect (ui->l_url, &QLineEdit::returnPressed, this, &Luna::openLink);
    connect (m_updateHomepage, &QAction::triggered, this, &Luna::updateHomepage);

    tabChanged(0);
}

Luna::~Luna()
{
    delete ui;
}

void Luna::openLink()
{
    m_tabs[ui->t_tabs->currentWidget()]->setUrl(QUrl(ui->l_url->text()));
}

void Luna::updateURL(QUrl url)
{
    ui->l_url->setText(url.toString());
}

void Luna::addTab()
{
    int index = ui->t_tabs->addTab(new QTabWidget(), "New tab");
    debug (QString("Tab with index %1 created!").arg(index));
    QWidget *tab = ui->t_tabs->widget(index);
    tab->setLayout(new QHBoxLayout(tab));

    QWebEngineView *view = new QWebEngineView(this);
    tab->layout()->addWidget(view);
    view->show();
    view->setUrl(QUrl(m_homepage));

    m_tabs[tab] = view;
    ui->t_tabs->setCurrentIndex(index);
}

void Luna::removeTab(int index)
{
    QWidget *tab = ui->t_tabs->widget(index);
    m_tabs.remove(tab);
    ui->t_tabs->removeTab(index);
}

void Luna::tabChanged(int index)
{
    debug(QString("Called tabChanged with %1 index").arg(index));
    if (ui->t_tabs->count() < 1) {
        return;
    }
    QWebEngineView *view = m_tabs[ui->t_tabs->widget(index)];
    if (view != nullptr) {
        ui->l_url->setText(view->url().toString());
        for (QMetaObject::Connection connection : m_tabDynamicConnections) {
            disconnect ( connection);
        }
        m_tabDynamicConnections.clear();
        ui->p_progress->hide();
        m_tabDynamicConnections.push_back(connect (view, &QWebEngineView::loadStarted, ui->p_progress, &QProgressBar::show));
        m_tabDynamicConnections.push_back(connect (view, &QWebEngineView::loadFinished, ui->p_progress, &QProgressBar::hide));
        m_tabDynamicConnections.push_back(connect (view, &QWebEngineView::loadProgress, ui->p_progress, &QProgressBar::setValue));
        m_tabDynamicConnections.push_back(connect (view, &QWebEngineView::urlChanged, this, &Luna::updateURL));
        m_tabDynamicConnections.push_back(connect (view, &QWebEngineView::titleChanged, this, &Luna::titleChanged));
        m_tabDynamicConnections.push_back(connect (ui->b_reload, &QPushButton::clicked, view, &QWebEngineView::reload));
        m_tabDynamicConnections.push_back(connect (ui->b_back, &QPushButton::clicked, view, &QWebEngineView::back));
        m_tabDynamicConnections.push_back(connect (ui->b_forward, &QPushButton::clicked, view, &QWebEngineView::forward));
    } else {
        debug("No webEngine object provided in tabChanged slot!");
    }
}

void Luna::titleChanged(QString title)
{
    int index = ui->t_tabs->currentIndex();
    ui->t_tabs->setTabText(index, title);
}

void Luna::updateHomepage()
{
    SetHomePage *homePageWindow = new SetHomePage(m_homepage);
    if (homePageWindow->exec() == QDialog::Accepted)
        m_homepage = homePageWindow->getHomepage();
    delete homePageWindow;
}

void Luna::debug(QString message)
{
    qDebug() << "[ Core ]: " << message;
}
