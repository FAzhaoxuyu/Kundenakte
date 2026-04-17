#include "Customer.h"
#include "CustomerManager.h"
#include "CustomerManagerUI.h"
using namespace std;

std::vector<Customer>::iterator CustomerManager::FindCustomerById(const int& searchId)
{
   auto it = find_if(customers.begin(), customers.end(), [searchId](const Customer& customer) {return customer.GetId() == searchId; });
   return it;
}

int CustomerManager::GenerateCustomerId()
{
   if (customers.size() == 0) {
      return 1;
   }
   else {
      int currentMaxId = customers[0].GetId();
      for (Customer& customer : customers) {
         if (customer.GetId() > currentMaxId) {
            currentMaxId = customer.GetId();
         }
         
      }
      return currentMaxId + 1;
   }

}

void CustomerManager::Add(Customer& newCustomer)
{
   customers.push_back(newCustomer);
}

void CustomerManager::Update()
{
   if (customers.empty()) {
      cout << endl;
      cout << "No customer is available, please add new customer first" <<endl;
   }

   else {
      int id = ui->ReadInt("Please enter customer id: ");
      for (int i = 0; i < customers.size(); i++)
      {
         if (customers[i].GetId() == id) {
            int choice = ui->ReadInt("What do you want to update?\n"
               "1. First name\n"
               "2. Last name\n"
               "3. Date of Birth\n"
               "4. Gender\n"
               "5. Customer status\n"
               "6. Member Level\n"
               "7. Email\n"
               "8. Adress\n");
            switch (choice)
            {
            case 1:
            {
               string newFirstName = ui->ReadText("Please enter new first name: ");
               customers[i].SetFirstName(newFirstName);
               std::cout << "First name updated.\n";
               break;
            }
            case 2:
            {
               string newLastName = ui->ReadText("Please enter new last name: ");
               customers[i].SetLastName(newLastName);
               std::cout << "Last name updated.\n";
               break;
            }
            case 3:
            {
               Date newDateOfBirth = ui->ReadDate("Please enter new date of birth: ");
               customers[i].SetDateOfBirth(newDateOfBirth);
               std::cout << "Date of birth updated.\n";
               break;
            }
            case 4:
            {
               Gender newGender = ui->ReadGender("Please enter new gender: ");
               customers[i].SetGender(newGender);
               std::cout << "Gender updated.\n";
               break;
            }
            case 5:
            {
               CustomerStatus newCustomerStatus = ui->ReadCustomerStatus("Please enter new customer status: ");
               customers[i].SetCustomerStatus(newCustomerStatus);
               std::cout << "Customer status updated.\n";
               break;
            }
            case 6:
            {
               MemberLevel newMemberLevel = ui->ReadMemberLevel("Please enter new member level: ");
               customers[i].SetMemberLevel(newMemberLevel);
               std::cout << "Member level updated.\n";
               break;
            }
            case 7:
            {
               string newEmail = ui->ReadText("Please enter new email: ");
               customers[i].SetEmail(newEmail);
               std::cout << "Email updated.\n";
               break;
            }
            case 8:
            {
               string newAddress = ui->ReadText("Please enter new address: ");
               customers[i].SetAddress(newAddress);
               std::cout << "Address updated.\n";
               break;
            }
            default:
            {
               cout << "Invalid choice." << endl;
               break;
            }

            }
         }
      }
   }
   
}
void CustomerManager::Remove()
{
   if (customers.empty()) {
      cout << endl;
      cout << "No customer is available, please add new customer first" <<endl;
   }

   else {
      int id = ui->ReadInt("Please enter customer id: ");
      auto it = FindCustomerById(id);
      if (it == customers.end()) {
         cout << "Customer not found.";
      }
      else {
         customers.erase(it);
         cout << "Customer removed successfully.";
      }   
   }
}

void CustomerManager::Show()
{
   if (customers.empty()) {
      cout << endl;
      cout << "No customer is available, please add new customer first" << endl;
   }
   else {
      for (const Customer& customer : customers) {
         customer.Print();
      }
   }

}
