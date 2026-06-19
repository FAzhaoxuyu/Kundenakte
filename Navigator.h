#pragma once
#include<vector>

template <typename T>
class Navigator
{
public:
   Navigator(std::vector<T> itmes) : items(std::move(items)), index(0) {};
   
   T Current()
   {
      return items[index];
   }

   bool Back()
   {
      if (index == 0) {
         return false;
      }

      index--;
      return true;
   }

   bool Next()
   {
      if (index + 1 >= items.size())
      {
         return false;
      }

      ++index;
      return true;
   }

private:
   std::vector<T> items;
   size_t index;
   
};
