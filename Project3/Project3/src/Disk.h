#pragma once
#include <stdint.h>

class Disk
{
public:
	Disk();

	size_t GetDiskNumber() const;

	~Disk();


private:
	size_t m_DiskNum;

private:
	static size_t s_DiskCount;

};

