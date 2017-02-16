#include        <regex>
#include        "QtGui.h"
#include        "Contact.h"

QtGui::QtGui(int &ac, char *av[])
    : _app(ac, av),
      _mainWindow()
{}

QtGui::~QtGui()
{

}

std::list<Event *>	*QtGui::getGuiEvents()
{
    _app.processEvents(QEventLoop::AllEvents, 10);
    return _mainWindow.getPendingEvents();
}

bool			QtGui::windowNotActivate()
{
  return this->_mainWindow.mainwindowNotActivate();
}

void			QtGui::setContactList(const std::list<Contact> &contacts)
{
  _mainWindow.setContactList(contacts);
}

void			QtGui::setGuiState(const IGui::State &state)
{
  switch (state)
    {
    case IGui::DISCONNECTED:
      _mainWindow.changeActualWindow(MainWindow::CONNECTION_PAGE);
      break;
    case IGui::CONNECTED:
      _mainWindow.changeActualWindow(MainWindow::LOGIN_PAGE);
      break;
    case IGui::AUTHENTIFIED:
      _mainWindow.changeActualWindow(MainWindow::CONNECTED_PAGE);
      break;
    default:
      break;
    }
}

void			QtGui::setLabelVisibility(const IGui::State &state)
{
  switch (state)
    {
    case IGui::USER_DOESNT_EXIST:
      _mainWindow.resetLabelVisibility();
      _mainWindow.setVisibilityLabelUserDoesntExist(true);
      break;
    case IGui::USER_ALREADY_EXIST:
      _mainWindow.resetLabelVisibility();
      _mainWindow.setVisibilityLabelUserAlreadyExist(true);
      break;
    case IGui::USER_ALREADY_LOGGED:
      _mainWindow.resetLabelVisibility();
      _mainWindow.setVisibilityLabelUserAlreadyExist(true);
      break;
    case IGui::USER_BAD_PASS:
      _mainWindow.resetLabelVisibility();
      _mainWindow.setVisibilityLabelUserWrongPassword(true);
      break;
    case IGui::IN_CALL:
      _mainWindow.setVisibilityButtonLeaveCall(true);
      break;
    case IGui::USER_HANGUP:
      _mainWindow.setVisibilityButtonLeaveCall(false);
      break;
    default:
      break;
    }
}
