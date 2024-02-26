#include "luna.h"
#include "ui_luna.h"

Luna::Luna(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Luna)
{
    ui->setupUi(this);

    QString buttonStyle = "QPushButton { background-color: lightblue; border-style: solid; border-width: 2px; border-radius: 15px; border-color: beige; padding: 6px; } QPushButton:pressed { background-color: #a0d8ef; }";

    m_fileMenu = new QMenu("File", this);

    m_quit = new QAction("Quit", this);
    m_addWidget = new QAction("New tab");

    m_fileMenu->addAction(m_addWidget);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_quit);

    ui->menubar->addMenu(m_fileMenu);
    ui->menubar->show();

    ui->b_back->setStyleSheet(buttonStyle);
    ui->b_forward->setStyleSheet(buttonStyle);
    ui->b_go->setStyleSheet(buttonStyle);

    ui->p_progress->hide();

    ui->t_tabs->clear();
    addTab();

    connect (ui->b_go, &QPushButton::clicked, this, &Luna::openLink);
    connect (m_quit, &QAction::triggered, this, &Luna::close);
    connect (m_addWidget, &QAction::triggered, this, &Luna::addTab);
}

Luna::~Luna()
{
    delete ui;
}

void Luna::openLink()
{
    tabs[ui->t_tabs->currentIndex()]->setUrl(QUrl(ui->l_url->text()));
}

void Luna::updateURL(QUrl url)
{
    ui->l_url->setText(url.toString());
}

void Luna::addTab()
{
    int index = ui->t_tabs->addTab(new QTabWidget(), "New tab");
    ui->t_tabs->setCurrentIndex(index);
    QWidget *tab = ui->t_tabs->currentWidget();
    tab->setLayout(new QHBoxLayout());

    QWebEngineView *view = new QWebEngineView();
    tab->layout()->addWidget(view);
    view->show();
    view->setUrl(QUrl("https://google.com"));

    tabs[index] = view;

    connect (view, &QWebEngineView::loadStarted, ui->p_progress, &QProgressBar::show);
    connect (view, &QWebEngineView::loadFinished, ui->p_progress, &QProgressBar::hide);
    connect (view, &QWebEngineView::loadProgress, ui->p_progress, &QProgressBar::setValue);
    connect (view, &QWebEngineView::urlChanged, this, &Luna::updateURL);
    connect (view, &QWebEngineView::titleChanged, this, &Luna::titleChanged);
}

void Luna::tabChanged()
{
    int index = ui->t_tabs->currentIndex();
    QWebEngineView *view = tabs[index];
    ui->l_url->setText(view->url().toString());
}

void Luna::titleChanged(QString title)
{
    int index = ui->t_tabs->currentIndex();
    ui->t_tabs->setTabText(index, title);
}
