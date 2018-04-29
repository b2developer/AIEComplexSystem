#include "AccountManager.h"
#include <iostream>
#include <fstream>

//constructor, loads accounts from text
AccountManager::AccountManager()
{
	ifstream file;
	string path = getExecutableFolder() + "\\accounts.txt";

	file.open(path.c_str());

	//check the file opened
	if (file.is_open())
	{
		string line;

		//read every line
		while (getline(file, line))
		{
			AccountInfo* newAcc = new AccountInfo();
			newAcc->deserialise(line);

			accounts.push_back(newAcc);
		}
		
		file.close();
	}
	else
	{
		throw "AccountManager: failed to read accounts.txt";
	}
}

//destructor, saves account objects using file i/o
AccountManager::~AccountManager()
{
	
}

//gets the root folder that the .exe is located inside
string AccountManager::getExecutableFolder()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	char *pos;
	if (pos = strrchr(buffer, '\\'))
	{
		*pos = 0;
	}

	return buffer;
}

//singleton instance retrieval
AccountManager* AccountManager::getInstance()
{
	static AccountManager* singleton = nullptr;

	//create the singleton if it doesn't exist already
	if (singleton == nullptr)
	{
		singleton = new AccountManager();
	}

	return singleton;
}

//saves and deallocates all accounts
void AccountManager::save()
{
	ofstream file;
	string path = getExecutableFolder() + "\\accounts.txt";

	file.open(path.c_str());

	//check the file opened
	if (file.is_open())
	{
		size_t size = accounts.size();

		//iterate through every account, saving it to memory and deleting it
		for (size_t i = 0; i < size; i++)
		{
			file << accounts[i]->serialise() << '\n';
		}

		file.close();
	}
	else
	{
		throw "AccountManager: failed to save AccountInfo.";
	}
}

//creates a new account
ECreationResponse AccountManager::createAccount(string name, string pass)
{
	size_t size = accounts.size();

	//search through all accounts to make sure there isn't a duplicate name
	for (size_t i = 0; i < size; i++)
	{
		AccountInfo* test = accounts[i];

		//duplicate name test
		if (test->name == name && test->pass == pass)
		{
			return ECreationResponse::NAME_MATCH;
		}
	}

	AccountInfo* newAcc = new AccountInfo();
	newAcc->name = name;
	newAcc->pass = pass;

	accounts.push_back(newAcc);

	return ECreationResponse::OK;
}

//removes an existing account
EDeletionResponse AccountManager::removeAccount(string name, string pass)
{
	size_t size = accounts.size();

	//search through all accounts to find one that matches the desired specifications
	for (size_t i = 0; i < size; i++)
	{
		AccountInfo* test = accounts[i];

		//name and password match test
		if (test->name == name)
		{
			if (test->pass == pass)
			{
				accounts.erase(accounts.begin() + i);
				return EDeletionResponse::OK;
			}
			else
			{
				return EDeletionResponse::BAD_PASSWORD;
			}
		}
	}

	//there was no account with the specific name
	return EDeletionResponse::NO_NAME;
}

//searches for an existing account
AccountInfo* AccountManager::searchAccount(string name, string pass)
{
	size_t size = accounts.size();

	//search through all accounts to find one that matches the desired specifications
	for (size_t i = 0; i < size; i++)
	{
		AccountInfo* test = accounts[i];

		//name and password match test
		if (test->name == name)
		{
			if (test->pass == pass)
			{
				return test;
			}
		}
	}

	//there was no account with the specific name
	return nullptr;
}

//updates an item to the existing account
void AccountManager::updateItem(AccountInfo * info, string dataName, EDataType type, EUpdate updateType, void * data)
{
	if (updateType == EUpdate::OVERWRITE)
	{
		info->overwriteData(dataName, type, data);
	}
	else if (updateType == EUpdate::OFFSET)
	{
		info->offsetData(dataName, type, data);
	}
}
