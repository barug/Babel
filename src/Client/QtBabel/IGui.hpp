#ifndef BABELIGUI_H
#define BABELIGUI_H

# include <queue>
# include <list>
# include "Event.hpp"
# include "Contact.h"
class IGui
{
public:
    enum State
    {
      DISCONNECTED,
      CONNECTED,
      AUTHENTIFIED,
      IN_CALL,
      USER_HANGUP,
      USER_DOESNT_EXIST,
      USER_ALREADY_EXIST,
      USER_ALREADY_LOGGED,
      USER_BAD_PASS
    };

  virtual ~IGui() {}
  virtual std::list<Event *>		*getGuiEvents() = 0;
  virtual void				setContactList(const std::list<Contact> &contacts) = 0;
  virtual void				setGuiState(const IGui::State &state) = 0;
  virtual void				setLabelVisibility(const IGui::State &state) = 0;
  virtual bool				windowNotActivate() = 0;
};

#endif // BABELIGUI_H
