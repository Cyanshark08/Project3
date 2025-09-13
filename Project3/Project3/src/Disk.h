#pragma once
#include <stdint.h>

class Disk
{
public:
	Disk(size_t p_DiskNum);

	size_t GetDiskNumber() const;

	bool operator>(Disk& p_Other) const;


private:
	size_t m_DiskNum;

};

