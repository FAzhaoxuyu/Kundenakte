#pragma once
#include<string>

enum Action
{
   Add,
   Update,
   Remove,
   Show,
   Help,
   Exit
};

std::string ActionToString(Action action);
