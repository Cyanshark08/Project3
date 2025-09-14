#include "Disk.h"
#include <sstream>;

std::unordered_map<size_t, int> Disk::s_TakenDiskNums;

Disk::Disk(size_t p_DiskNum)
    : m_DiskNum(p_DiskNum)
{
    if (s_TakenDiskNums.find(p_DiskNum) != s_TakenDiskNums.end())
        throw E_DuplicateDiskNumber(p_DiskNum);

    if (p_DiskNum < 1)
        throw E_InvalidDiskNumber(p_DiskNum);

    s_TakenDiskNums[p_DiskNum] = NULL;
}

size_t Disk::GetDiskNumber() const
{
    return m_DiskNum;
}

bool Disk::operator>(Disk& p_Other) const
{
    return this->m_DiskNum > p_Other.m_DiskNum;
}

Disk::E_DuplicateDiskNumber::E_DuplicateDiskNumber(size_t p_DuplicatedDiskNum)
    : m_DuplicatedDiskNum(p_DuplicatedDiskNum)
{}

std::string Disk::E_DuplicateDiskNumber::GetExceptionName() const
{
    return "Duplicated Disk Number";
}

std::string Disk::E_DuplicateDiskNumber::GetExceptionMessage() const
{
    std::stringstream ss;
    ss << "Disk #" << m_DuplicatedDiskNum << " cannot have duplicate instances";
    return ss.str();
}

Disk::E_InvalidDiskNumber::E_InvalidDiskNumber(size_t p_InvalidDiskNum)
    : m_InvalidDiskNum(p_InvalidDiskNum)
{}

std::string Disk::E_InvalidDiskNumber::GetExceptionName() const
{
    return "Invalid Disk Number";
}

std::string Disk::E_InvalidDiskNumber::GetExceptionMessage() const
{
    std::stringstream ss;
    ss << "Disk #" << m_InvalidDiskNum << " is an invalid Disk Number (Must be above 0)";
    return ss.str();
}
