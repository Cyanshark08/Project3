#pragma once
#include <stdint.h>
#include <unordered_map>
#include "ExceptionInterface.h"

class Disk
{
public:
	Disk(size_t p_DiskNum);

	size_t GetDiskNumber() const;

	bool operator>(Disk& p_Other) const;

	operator size_t() const;

	~Disk();

public:
	class E_DuplicateDiskNumber : public ExceptionInterface
	{
	public:
		E_DuplicateDiskNumber(size_t p_DuplicatedDiskNum);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_DuplicatedDiskNum;

	};

	class E_InvalidDiskNumber : public ExceptionInterface
	{
	public:
		E_InvalidDiskNumber(size_t p_InvalidDiskNum);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_InvalidDiskNum;

	};

private:
	size_t m_DiskNum;

private:
	static std::unordered_map<size_t, int> s_TakenDiskNums;

};

