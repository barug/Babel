#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QFile>

MainWindow::MainWindow()
  : QMainWindow(0),
    _contactIsSelected(false),
    _ui(new Ui::MainWindow),
    _eventQueue(new std::list<Event *>)
{
  this->_ui->setupUi(this);
  this->_ui->uiPages->setCurrentIndex(0);
  this->resetLabelVisibility();
  this->setWindowTitle("Babel");
  this->setStyleSheet("background-color: grey ; color : white");
  this->show();
  this->_mainwindow_not_activate = false;
  this->_ui->buttonLeaveCall->setVisible(false);
  this->_ui->labelFirstPage->setPixmap(QPixmap("./assets/logo.png"));
  this->_ui->labelLogo->setPixmap(QPixmap("./assets/logo.png"));
  this->_ui->labelContactAvatar->setPixmap(QPixmap("./assets/contact.png"));
  this->_ui->buttonConnect->setStyleSheet(HOVER_STYLE_SHEET);
  this->_ui->buttonCall->setStyleSheet(HOVER_STYLE_SHEET);
  this->_ui->buttonLogOut->setStyleSheet(HOVER_STYLE_SHEET);
  this->_ui->buttonLogin->setStyleSheet(HOVER_STYLE_SHEET);
  this->_ui->buttonAddContact->setStyleSheet(HOVER_STYLE_SHEET);
  this->_ui->buttonRegister->setStyleSheet(HOVER_STYLE_SHEET);
  this->_ui->tableContactList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  this->_ui->tableContactList->setEditTriggers(QAbstractItemView::NoEditTriggers);
  connect(this->_ui->tableContactList, SIGNAL(cellClicked(int, int )), this, SLOT(cellClicked(int, int)));
}

MainWindow::~MainWindow()
{
  delete (this->_ui);
}

void		MainWindow::requestExit()
{
  this->_mainwindow_not_activate = true;
}

bool		MainWindow::mainwindowNotActivate()
{
  return (this->_mainwindow_not_activate);
}

void            MainWindow::cellClicked(int row, int column)
{
  if (this->_ui->uiPages->currentIndex() == 2 && column == 0)
    {
      this->_ui->labelContactSelected->setText(QString::fromStdString(this->_contacts_name[row]));
      this->_contactIsSelected = true;
      this->_ui->buttonCall->setMinimumSize(180, 0);
  }
}

std::list<Event *>	*MainWindow::getPendingEvents()
{
  std::list<Event *>	*pendingEvents = this->_eventQueue;

  this->_eventQueue = new std::list<Event *>;
  return pendingEvents;
}

void            MainWindow::setContactList(const std::list<Contact> &contacts)
{
  this->_ui->tableContactList->setRowCount(0);
  if (!contacts.empty())
    {
      this->_ui->tableContactList->setRowCount(contacts.size());
      for (int row = 0;
	   row < this->_ui->tableContactList->rowCount();
	   row++)
        {
	  std::list<Contact>::const_iterator it = std::next(contacts.begin(), row);
	  Contact n = *it;
	  for (int column = 0;
	       column < this->_ui->tableContactList->columnCount();
	       column++)
            {
	      if (!this->_ui->tableContactList->item(row, column))
                {
		  QTableWidgetItem *insideCell = new QTableWidgetItem;
		  this->_ui->tableContactList->setItem(row, column, insideCell);
		  if (column == CONTACT_NAME)
                    {
		      insideCell->setText(QString::fromStdString(n.getUserName()));
		      this->_contacts_name.push_back(n.getUserName());
                    }
		  else if (column == CONTACT_IS_CONNECTED)
                    {
		      QIcon online("./assets/online-icon.png");
		      QIcon offline("./assets/offline-icon.png");
		      qDebug() << online.isNull();
		      if (n.getIfConnected())
			(!QFile::exists("./assets/online-icon.png")) ?
			  insideCell->setText(QString::fromStdString("Online")) :
			  insideCell->setIcon(online);
		      else
			(!QFile::exists("./assets/offline-icon.png")) ?
			  insideCell->setText(QString::fromStdString("Offline")) :
			  insideCell->setIcon(offline);
                    }
		  this->_ui->tableContactList->model()->setData(this->_ui->tableContactList->model()->index(row, column),
								Qt::AlignCenter, Qt::TextAlignmentRole);
                }
            }
        }
      this->_ui->tableContactList->verticalHeader()->setVisible(false);
    }
}

void            MainWindow::resetLabelVisibility(void)
{
  this->_ui->labelUserDoesntExist->setVisible(false);
  this->_ui->labelUserIsAlreadyExist->setVisible(false);
  this->_ui->labelUserIsAlreadyOn->setVisible(false);
  this->_ui->labelUserWrongPassword->setVisible(false);
}

void		MainWindow::on_buttonConnect_clicked(void)
{
  std::string	ip = this->_ui->lineIp->text().toStdString();
  std::string	port = this->_ui->linePort->text().toStdString();

  _eventQueue->push_front(new Event(Event::CLIENT_CONNECTION));
  _eventQueue->front()->addData("ip", ip);
  _eventQueue->front()->addData("port", port);
}

void            MainWindow::on_buttonLogin_clicked()
{
  std::string userName;
  std::string password;

  userName = this->_ui->lineUsername->text().toStdString();
  password = this->_ui->linePassword->text().toStdString();
  _eventQueue->push_front(new Event(Event::CLIENT_AUTHENTIFICATION));
  _eventQueue->front()->addData("userName", userName);
  _eventQueue->front()->addData("password", password);
}

void            MainWindow::on_buttonRegister_clicked()
{
  std::string userName;
  std::string password;

  userName = this->_ui->lineUsername->text().toStdString();
  password = this->_ui->linePassword->text().toStdString();
  _eventQueue->push_front(new Event(Event::CLIENT_REGISTER));
  _eventQueue->front()->addData("userName", userName);
  _eventQueue->front()->addData("password", password);
}

void		MainWindow::on_buttonLogOut_clicked()
{
  _eventQueue->push_front(new Event(Event::CLIENT_LOGOUT));
}

void            MainWindow::on_radioButtonShowPassword_clicked()
{
  if (this->_ui->radioButtonShowPassword->isChecked())
    this->_ui->linePassword->setEchoMode(QLineEdit::Normal);
  else
    this->_ui->linePassword->setEchoMode(QLineEdit::Password);
}

void		MainWindow::setVisibilityButtonLeaveCall(const bool isVisible)
{
  this->_ui->buttonLeaveCall->setVisible(isVisible);
}

void		MainWindow::on_buttonLeaveCall_clicked()
{
  _eventQueue->push_front(new Event(Event::CLIENT_HANGUP));
}

void		MainWindow::on_buttonAddContact_clicked()
{
  std::string	contactName;

  contactName = this->_ui->lineAddContact->text().toStdString();
  _eventQueue->push_front(new Event(Event::CLIENT_ADD_CONTACT));
  _eventQueue->front()->addData("contactName", contactName);
}

void		MainWindow::on_buttonCall_clicked()
{
  std::string	contactName;

  if (_contactIsSelected)
    {
      contactName = this->_ui->labelContactSelected->text().toStdString();
      _eventQueue->push_front(new Event(Event::CLIENT_CALL));
      _eventQueue->front()->addData("contactName", contactName);
    }
}

void		MainWindow::changeActualWindow(const MainWindow::Pages &page)
{
  _ui->uiPages->setCurrentIndex(page);
}

void		MainWindow::setVisibilityLabelUserDoesntExist(const bool isVisible)
{
  this->_ui->labelUserDoesntExist->setVisible(isVisible);
}

void		MainWindow::setVisibilityLabelUserAlreadyExist(const bool isVisible)
{
  this->_ui->labelUserIsAlreadyExist->setVisible(isVisible);
}

void		MainWindow::setVisibilityLabelUserAlreadyOn(const bool isVisible)
{
  this->_ui->labelUserIsAlreadyOn->setVisible(isVisible);
}

void		MainWindow::setVisibilityLabelUserWrongPassword(const bool isVisible)
{
  this->_ui->labelUserWrongPassword->setVisible(isVisible);
}
