#ifndef _AVRECORD_H__INCLUDED_
#define _AVRECORD_H__INCLUDED_

#include

//! ��������� ���������
typedef struct SAVSignature {
    SAVSignature() {
        this->Offset = 0;
        this->Length = 0;
        memset(this->Hash, 0, sizeof(this->Hash));
    }
    DWORD Offset; // - �������� � �����
    DWORD Hash[4]; // - MD5 ���
    DWORD Length; // - ������ ������
} *PSAVSignature;

//! ��������� ������ � ��������
typedef struct SAVRecord {
    SAVRecord() {
        this->Name = NULL;
        this->NameLen = 0;
    }

    ~SAVRecord() {
        if (this->Name!= NULL) delete[] this->Name;
    }

    //! ��������� ������ ��� ���
    void allocName(BYTE NameLen) {
        if (this->Name == NULL) {
            this->NameLen = NameLen;
            this->Name = new CHAR[this->NameLen + 1];
            memset(this->Name, 0, this->NameLen + 1);
        }
    }

    PSTR Name; // - ���
    BYTE NameLen; // - ������ �����
    SAVSignature Signature; // - ���������
} *PSAVRecord;

#endif
