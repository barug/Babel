#ifndef             QT_GUI_H
# define            QT_GUI_H

#include            <queue>
#include            <QApplication>
#include            <QDebug>
#include            "mainwindow.h"
#include            "IGui.hpp"

class               QtGui : public IGui
{
public:
  explicit QtGui(int &ac, char *av[]);
  virtual ~QtGui();
  virtual std::list<Event *>	*getGuiEvents();
  virtual void			setContactList(const std::list<Contact> &contacts);
  virtual void			setGuiState(const IGui::State &state);
  virtual void			setLabelVisibility(const IGui::State &state);
  virtual bool			windowNotActivate();
private:
    QApplication                    _app;
    MainWindow                      _mainWindow;
    std::queue<Event *>             _eventQueue;
    std::string                     _username;
    std::string                     _password;
};

#endif              // QT_GUI_H
