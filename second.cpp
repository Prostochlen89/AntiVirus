#ifndef _AVBFILE_H__INCLUDED_
#define _AVBFILE_H__INCLUDED_

#include
#include
#include "avrecord.h"

using namespace std;

/* ������ ����� ������������ ����

[AVB] // - ���������
[RecordCount * 4 ] // - ����� �������
[Records... ]

Record:
[Offset * 4 ] // - ��������
[Lenght * 4 ] // - ������
[Hash * 16 ] // - ����������� �����
[NameLen * 1 ] // - ������ �����
[Name... ] // - ��� ��������

*/

//! ����� ����� ������������ ����
typedef class CAVBFile {
protected:
    fstream hFile; // - ������ ������ �����
    DWORD RecordCount; // - ����� �������

public:
    CAVBFile();

    //! �������� �����
    virtual void close();

    //! �������� ��������� �����
    virtual bool is_open();

    //! ��������� ����� �������
    virtual DWORD getRecordCount();
} * PCAVBFile;

//! ����� ��� ������ �����
typedef class CAVBFileWriter : public CAVBFile {
public:
    CAVBFileWriter() : CAVBFile() {}

    //! �������� �����
    bool open(PCSTR FileName);

    //! ���������� ������ � ����
    bool addRecord(PSAVRecord Record);
} * PCAVBFileWriter;

//! ����� ��� ������ �����
typedef class CAVBFileReader : public CAVBFile {
public:
    CAVBFileReader() : CAVBFile() {}

    //! �������� �����
    bool open(PCSTR FileName);

    //! ������ ������
    bool readNextRecord(PSAVRecord Record);
} * PCAVBFileReader;

#endif
