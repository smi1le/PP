#include "CBank.h"


CRITICAL_SECTION cs;

CBank::CBank()
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
}


CBankClient* CBank::CreateClient()
{
	unsigned int clientId = static_cast<unsigned>(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}



void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	//InitializeCriticalSection(&cs);
	//EnterCriticalSection(&cs);
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}
	else
	{
		SetTotalBalance(totalBalance);
	}
	//LeaveCriticalSection(&cs);
	//DeleteCriticalSection(&cs);
	
}



size_t CBank::GetNumberClients() const
{
	return m_clients.size();
}

HANDLE * CBank::GetHandles() const
{
	std::vector<HANDLE> handles;

	for (auto const& client : m_clients)
	{
		handles.push_back(client.m_handle);
	}

	return handles.data();
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	size_t number = rand() % 2001;
	//std::cout << "rand() % 2001 " << number << std::endl;
	for (size_t i = 0; i != number; ++i) {}
}