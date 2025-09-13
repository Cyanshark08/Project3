#include "Disk.h"

Disk::Disk(size_t p_DiskNum)
    : m_DiskNum(p_DiskNum)
{}

size_t Disk::GetDiskNumber() const
{
    return m_DiskNum;
}

bool Disk::operator>(Disk& p_Other) const
{
    return this->m_DiskNum > p_Other.m_DiskNum;
}
