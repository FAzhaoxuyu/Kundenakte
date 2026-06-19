#include "Action.h"

std::string ActionToString (Action action)
{
   switch (action)
   {
   case Action::Add:
      return "Add";

   case Action::Select:
      return "Select";

   //case Action::Remove:
   //   return "Remove";

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