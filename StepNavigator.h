#pragma once
#include<vector>

template <typename T>
class StepNavigator
{
public:
   StepNavigator (const std::vector<T>& steps) : steps (steps), index (0) {};

   T Current ()
   {
      return steps[index];
   }

   bool Back ()
   {
      if (index == 0) {
         return false;
      }

      index--;
      return true;
   }

   bool Next ()
   {
      if (index + 1 >= steps.size())
      {
         return false;
      }

      ++index;
      return true;
   }

private:
   std::vector<T> steps;
   size_t index;

};