#include "Action.h"

std::string ActionToString(Action action)
{
   switch (action)
   {
   case Action::Add:
      return "Add";

   case Action::Update:
      return "Update";

   case Action::Remove:
      return "Remove";

   case Action::Show:
      return "Show";

   case Action::Help:
      return "Help";

   case Action::Exit:
      return "Exit";

   default:
      return "Unknown";
   }
}