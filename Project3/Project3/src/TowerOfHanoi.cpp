#include "TowerOfHanoi.h"
#include <sstream>
#include <algorithm>
#include "Input.h"
#include <iomanip>

TowerOfHanoi::TowerOfHanoi()
	: SubApp(AppID::TowerOfHanoi),
	m_CurrentState(TOHState::Introduction),
	m_NumberOfDisks(3),
	m_MoveCount(0)
{}

void TowerOfHanoi::MoveDisk(size_t p_OldTower, size_t p_NewTower)
{

	if (m_StackList[p_OldTower - 1].size() == 0)
		throw E_EmptyStack(p_OldTower);

	Disk newTopDisk = m_StackList[p_OldTower - 1].top();

	if (m_StackList[p_NewTower - 1].size() == 0)
	{
		m_StackList[p_OldTower - 1].pop();
		m_StackList[p_NewTower - 1].push(newTopDisk);
		m_MoveCount++;
		return;
	}

	Disk oldTopDisk = m_StackList[p_NewTower - 1].top();

	if (newTopDisk > oldTopDisk)
		throw E_IllegalMove(
			p_OldTower, 
			p_NewTower, 
			m_StackList[p_OldTower - 1].top().GetDiskNumber(), 
			m_StackList[p_NewTower - 1].top().GetDiskNumber());

	
	m_StackList[p_OldTower - 1].pop();
	m_StackList[p_NewTower - 1].push(newTopDisk);

	m_MoveCount++;
}

void TowerOfHanoi::SetNumberOfDisks(size_t p_NumOfDisks)
{
	m_NumberOfDisks = p_NumOfDisks;
}

TOHState TowerOfHanoi::GetState() const
{
	return m_CurrentState;
}

void TowerOfHanoi::DisplayGame() const
{
	std::stringstream ss;

	if(m_NumberOfDisks <= 9)
	{
		for (int64_t i = m_NumberOfDisks - 1; i >= 0; i--)
		{
			ss << "\n\t";
			for (size_t j = 0; j < s_NumberOfTowers; j++)
			{
				if (m_StackList[j].size() <= i)
				{
					ss << std::string(m_NumberOfDisks + (j == 1 || j == 2 ? std::ceil(m_NumberOfDisks / 3) : 0), ' ');
					ss << std::string(1, 186);
					ss << std::string(m_NumberOfDisks + (j == 0 || j == 1 ? std::ceil(m_NumberOfDisks / 3) : 0), ' ');
				}
				else
				{	
					size_t diskSize = m_StackList[j]._Get_container()[i].GetDiskNumber();
					ss << std::string(m_NumberOfDisks + (j == 1 || j == 2 ? std::ceil(m_NumberOfDisks / 3) : 0) - diskSize, ' ');
					ss << std::string(diskSize, 254);
					ss << diskSize;
					ss << std::string(diskSize, 254);
					ss << std::string(m_NumberOfDisks + (j == 0 || j == 1 ? std::ceil(m_NumberOfDisks / 3) : 0) - diskSize, ' ');
				}

			}
			
		}

		ss << "\n\t";
		for (size_t j = 0; j < s_NumberOfTowers; j++)
		{
			ss << std::string((j == 1 || j == 2 ? std::ceil(m_NumberOfDisks / 3) : 0), ' ');
			ss << std::string(m_NumberOfDisks, 205);
			ss << std::string(1, 202);
			ss << std::string(m_NumberOfDisks, 205);
			ss << std::string((j == 0 || j == 1 ? std::ceil(m_NumberOfDisks / 3) : 0), ' ');
		}
	}
	else
	{
		for (int64_t i = m_NumberOfDisks - 1; i >= 0; i--)
		{
			ss << "\n\t";
			for (size_t j = 0; j < s_NumberOfTowers; j++)
			{
				if (i == 0)
				{
					int a = 0;
				}


				if (m_StackList[j].size() <= i)
				{
					ss << std::string(3 + (j == 1 || j == 2 ? 1 : 0), ' ');
					ss << std::string(1, 186);
					ss << std::string(3 + (j == 0 || j == 1 ? 1 : 0), ' ');
				}
				else
				{
					size_t diskSize = m_StackList[j]._Get_container()[i].GetDiskNumber();
					size_t digitSize = std::floor(std::log10(diskSize)) + 1;
					ss << std::string(4 - digitSize + (j == 1 || j == 2 ? 1 : 0), ' ');
					ss << diskSize;
					ss << std::string(3 + (j == 0 || j == 1 ? 1 : 0), ' ');
				}

			}
		}

		ss << "\n\t";
		for (size_t j = 0; j < s_NumberOfTowers; j++)
		{
			ss << std::string((j == 1 || j == 2 ? 1 : 0), ' ');
			ss << std::string(3, 205);
			ss << std::string(1, 202);
			ss << std::string(3, 205);
			ss << std::string((j == 0 || j == 1 ? 1 : 0), ' ');
		}
	}

	printf("%s", ss.str().c_str());
}

void TowerOfHanoi::Run()
{

	while (m_CurrentState != TOHState::Exited)
	{
		switch (m_CurrentState)
		{
		case TOHState::Introduction:
			puts("\n\tThe Tower of Hanoi also called the Tower of Brahma or Lucas' Tower is a mathematical game.");
			puts("\tIt consists of three pegs and a number of rings of different sizes, which can slide onto");
			puts("\tany peg.The game starts with the rings in a neat stack in ascending order of size on one");
			puts("\tpeg, the smallest at the top, thus making a conical shape.");
			puts("");
			puts("\tThe objective of the game is to move the entire stack from the starting peg - A to ending peg - B,");
			puts("\tobeying the following simple rules :");
			puts("");
			puts("\t1. Only one disk can be moved at a time.");
			puts("\t2. Each move consists of taking the upper disk from one of the stacks and");
			puts("\tplacing it on top of another stack or on an empty peg.");
			puts("\t3. No larger disk may be placed on top of a smaller disk.");
			puts("");
			SetNumberOfDisks(Input::inputInteger("\n\tEnter the number of rings(1..64) to begin : ", 1, 64));
			InitializeDisks();
			m_CurrentState = TOHState::InProgress;
			std::system("cls");
			this->BeginTimer();
			break;
		case TOHState::InProgress:
			DisplayGame();
			try
			{
				HandleInput(Input::inputChar("\n\tSelect the top disk from the start peg (A, B, C, or Q-quit): ", "ABCQ"));
				UpdateState();
				std::system("cls");
			}
			catch (const ExceptionInterface& e)
			{
				puts(e.Message().c_str());
			}
			break;
		case TOHState::Won:
			printf("\n\tCongratulations! You have solved the game in %d moves. ", m_MoveCount);
			this->EndTimer(m_MoveCount);
			switch (Input::inputChar("Play again? (Y-yes, N-no)", "YN"))
			{
			case 'Y':
				this->Restart();
				this->BeginTimer();
				m_CurrentState = TOHState::InProgress;
				break;
			case 'N':
				printf(this->GetUserStats().GetNumOfGamesPlayed() != 1 ? 
					  "\n\t%d Games of Tower Of Hanoi with %d disk(s) were played"
					: "\n\t%d Game of Tower Of Hanoi with %d disk(s) was played", this->GetUserStats().GetNumOfGamesPlayed(), this->m_NumberOfDisks);
				printf("\n\t\tThe fastest time was %.2f second(s) in %d moves", this->GetUserStats().GetShortestTime(), this->GetUserStats().GetShortestMoves());
				printf("\n\t\tThe slowest time was %.2f second(s) in %d moves", this->GetUserStats().GetLongestTime(), this->GetUserStats().GetLongestMoves());
				printf("\n\t\tThe average time was %.2f second(s)", this->GetUserStats().GetAverageTime());
				puts("\t");
				std::system("pause");
				m_CurrentState = TOHState::Exited;
				break;
			}
			
			break;
		}
	}

	this->Clean();
	m_CurrentState = TOHState::Introduction;
	std::system("cls");
}

void TowerOfHanoi::Restart()
{
	for (auto& stack : m_StackList)
	{
		while (!stack.empty())
			stack.pop();
	}

	m_MoveCount = 0;

	InitializeDisks();
}

void TowerOfHanoi::Clean()
{
	for (auto& stack : m_StackList)
	{
		while (!stack.empty())
			stack.pop();
	}

	m_NumberOfDisks = 0;
	m_MoveCount = 0;
}

void TowerOfHanoi::HandleInput(char p_Input)
{
	size_t origin, destination;
	switch (p_Input)
	{
	case 'A':
		origin = 1;
		break;
	case 'B':
		origin = 2;
		break;
	case 'C':
		origin = 3;
		break;
	case 'Q':
		m_CurrentState = TOHState::Exited;
		return;
	}

	switch (Input::inputChar("\tSelect the top disk from the end peg (A, B, or C):", "ABC"))
	{
	case 'A':
		destination = 1;
		break;
	case 'B':
		destination = 2;
		break;
	case 'C':
		destination = 3;
		break;
	}

	MoveDisk(origin, destination);
}

void TowerOfHanoi::InitializeDisks()
{
	for (size_t i = 0; i < m_NumberOfDisks; i++)
		m_StackList[0].emplace(m_NumberOfDisks - i);
}

void TowerOfHanoi::UpdateState()
{
	if (m_StackList[s_NumberOfTowers - 1].size() == m_NumberOfDisks)
		m_CurrentState = TOHState::Won;
}

TowerOfHanoi::E_IllegalMove::E_IllegalMove(size_t p_InitialTower, size_t p_FinalTower, size_t p_InitialTowerDisk, size_t p_FinalTowerDisk)
	: m_InitialTower(p_InitialTower),
	m_FinalTower(p_FinalTower),
	m_InitialTowerDisk(p_InitialTowerDisk),
	m_FinalTowerDisk(p_InitialTowerDisk)
{}

std::string TowerOfHanoi::E_IllegalMove::GetExceptionName() const
{
	return "Illegal Move";
}

std::string TowerOfHanoi::E_IllegalMove::GetExceptionMessage() const
{
	std::stringstream ss;
	ss << "Cannot move disk #" << m_InitialTowerDisk << " from Tower #" << m_InitialTower << " to Tower #" << m_FinalTower;
	return ss.str();
}

TowerOfHanoi::E_EmptyStack::E_EmptyStack(size_t p_StackNum)
	: m_StackNum(p_StackNum)
{}

std::string TowerOfHanoi::E_EmptyStack::GetExceptionName() const
{
	return "Empty Stack";
}

std::string TowerOfHanoi::E_EmptyStack::GetExceptionMessage() const
{
	std::stringstream ss;
	ss << "Cannot Select Empty Stack (" << m_StackNum << ") as start peg";
	return ss.str();
}
