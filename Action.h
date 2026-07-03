#pragma once
#include<string>

enum class Action
{
   Add,
   Select,
   Show,
   Help,
   Exit
};

std::string ActionToString (Action action);
