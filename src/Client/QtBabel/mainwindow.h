#ifndef MAINWINDOW_H
#define MAINWINDOW_H

# include <iostream>
# include <QtWidgets/QMainWindow>
# include <queue>
# include "Contact.h"
# include "Event.hpp"

namespace           Ui
{
    class           MainWindow;
}

# define            CONTACT_NAME            0
# define            CONTACT_IS_CONNECTED    1
# define	    HOVER_STYLE_SHEET "QPushButton:hover {border-style:solid ;border-width:2px; border-color : rgb(0, 159, 255);}"

//QPushButton:!hover {border-style:solid; border-radius:5px}"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

  enum Pages
    {
      CONNECTION_PAGE = 0,
      LOGIN_PAGE = 1,
      CONNECTED_PAGE = 2
    };

  explicit MainWindow();
  ~MainWindow();
  std::list<Event *>     *getPendingEvents();
  void                    setContactList(const std::list<Contact> &contacts);
  void                  changeActualWindow(const MainWindow::Pages &page);
  void			setVisibilityLabelUserDoesntExist(const bool isVisible);
  void			setVisibilityLabelUserAlreadyExist(const bool isVisible);
  void			setVisibilityLabelUserAlreadyOn(const bool isVisible);
  void			setVisibilityLabelUserWrongPassword(const bool isVisible);
  void			resetLabelVisibility(void);
  bool			mainwindowNotActivate();
  void	        setVisibilityButtonLeaveCall(const bool isVisible);
  void		setButtonLeaveCall(const bool leavecall);
  bool		getButtonLeaveCall() const;

private slots:
  void		on_buttonConnect_clicked();
  void		on_buttonLogin_clicked();
  void		on_buttonRegister_clicked();
  void		on_buttonLogOut_clicked();
  void		on_radioButtonShowPassword_clicked();
  void		on_buttonAddContact_clicked();
  void		on_buttonCall_clicked();
  void		on_buttonLeaveCall_clicked();
  void		cellClicked(int row, int column);
  void		requestExit();

private:
  std::vector<std::string>	_contacts_name;
  bool				_contactIsSelected;
  Ui::MainWindow		*_ui;
  std::list<Event *>		*_eventQueue;
  bool				_mainwindow_not_activate;
  bool				_buttonLeaveCall;
};

#endif // MAINWINDOW_H
